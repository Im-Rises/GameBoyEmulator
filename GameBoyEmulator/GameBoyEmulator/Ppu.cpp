#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;
	reset();
}

void Ppu::reset()
{
	for (int j = 0; j < DOTS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < DOTS_DISPLAY_X; i++)
		{
			lcdScreen[i][j] = 0;
		}
	}
}



uint8 Ppu::getLcdScreenPixel(int indexX, int indexY)
{
	return lcdScreen[indexX][indexY];
}


void Ppu::draw(const int& cycles)//Not working
{
	for (int i = 0; i < cycles; i++)
	{
		drawLineSimulation();
		drawBackgroundLine();
		drawSpritesLine();
		setRegisters();
	}
	if (memory->read(LY_ADDRESS) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LY_ADDRESS, 0);
}

void Ppu::drawLineSimulation()
{
	/// <summary>
	/// Function that simulate the drawing of a line each cycle of the CPU (in pixel not block) 
	/// </summary>

	if (testBit(memory->read(LCDC_ADDRESS), 7))
		memory->increment(LY_ADDRESS);
	else
		memory->write(LY_ADDRESS, 0);
}

void Ppu::drawBackgroundLine()
{

	uint8 lcdc = memory->read(LCDC_ADDRESS);

	if (testBit(lcdc, 0))
	{
		uint8 scx = memory->read(SCX_ADDRESS);
		uint8 scy = memory->read(SCY_ADDRESS);
		uint8 wx = memory->read(WX_ADDRESS) - 7;//Why 7 because : With WX = 7, the window is displayed from the left edge of the LCD screen. Values of 0-6 should not be specified for WX.
		uint8 wy = memory->read(WY_ADDRESS);

		uint8 ly = memory->read(LY_ADDRESS);

		bool windowing = false;

		uint16 tileDataArea;
		bool unsignedValue = true;

		uint16 backgroundMemoryCode;


		if (testBit(lcdc, 5) && wy <= ly)
			windowing = true;

		if (testBit(lcdc, 4))//Get tile data address
		{
			tileDataArea = 0x8000;
			unsignedValue = true;
		}
		else
		{
			tileDataArea = 0x8800;
			unsignedValue = false;
		}

		if (windowing)//Get tile code address
		{
			if (testBit(lcdc, 6))
				backgroundMemoryCode = 0x9C00;
			else
				backgroundMemoryCode = 0x9800;
		}
		else
		{
			if (testBit(lcdc, 3))
				backgroundMemoryCode = 0x9C00;
			else
				backgroundMemoryCode = 0x9800;
		}

		uint8 yPos;
		if (windowing)
			yPos = ly - wy;//WHY THAT ?
		else
			yPos = scy + ly;

		uint16 tileRow = (yPos / 8) * 32;//Contains all precedents row 

		for (int pixel = 0; pixel < DOTS_DISPLAY_X; pixel++)
		{
			uint8 xPos = pixel + scx;

			if (windowing && pixel >= wx)
				xPos = pixel - wx;//Why that

			uint8 tileColumn = xPos / 8;

			int16_t tileNum;//Can be signed or unsigend depending of the tileDataArea

			if (unsignedValue)
				tileNum = (uint8)memory->read(backgroundMemoryCode + tileRow + tileColumn);
			else
				tileNum = (int8_t)memory->read(backgroundMemoryCode + tileRow + tileColumn);

			uint16 tileLocation;
			if (unsignedValue)
				tileLocation = tileDataArea + tileNum * 16;
			else
				tileLocation = tileDataArea + (tileNum + 128) * 16;

			uint8 line = (yPos % 8) * 2;
			uint8 dataLine1 = memory->read(tileLocation + line);
			uint8 dataLine2 = memory->read(tileLocation + line + 1);

			uint8 bitIndex = (((xPos % 8) - 7) * -1);
			uint8 colorCode = getBit(dataLine1, bitIndex) + (getBit(dataLine2, (bitIndex)) << 1);

			uint8 color = transformDotDataToColor(colorCode, BG_PALETTE_DATA);

			if (ly < DOTS_DISPLAY_Y)
				lcdScreen[pixel][ly] = colorToRGB(color);
		}
	}
}

void Ppu::drawSpritesLine()
{
	uint8 lcdc = memory->read(LCDC_ADDRESS);

	if (testBit(lcdc, 1))//if OBJ FLAG is ON
	{
		bool sprite8x16Dots = getBit(lcdc, 2); //0: 8 x 8 dots		1 : 8 x 16 dots

		for (int i = 0; i < SPRITES_NUMBER; i++)
		{
			int index = i * 4;//Sprites data are composed of 4 bytes of data

			uint8 yCoordinate = memory->read(OAM_Y_COODINATE + index) - 16;//From the Developper guide it is supposed to be 10 but that doesn't make sense
			uint8 xCoordinate = memory->read(OAM_X_COODINATE + index) - 8;
			uint8 chrCode = memory->read(OAM_CHR_CODE + index);
			uint8 attributeFlag = memory->read(OAM_ATTRIBUTE_FLAG + index);

			bool horizontalFlip = testBit(lcdc, 5);
			bool verticalFlip = testBit(lcdc, 6);
			bool displayPriority = testBit(lcdc, 7);

			uint8 ly = memory->read(LY_ADDRESS);

			uint8 spriteSize = (sprite8x16Dots ? 16 : 8);

			if ((ly >= yCoordinate) && (ly < (yCoordinate + spriteSize)))//Before drawing sprite, we verify if it is not out of screen
			{
				uint8 lineSprite = ly - yCoordinate;//Get line to draw depending if the sprite is flipped horizontally or vertically

				if (horizontalFlip)
					lineSprite = (lineSprite - spriteSize) * -1;

				lineSprite *= 2;
				uint8 dataLine1 = memory->read(0x8000 + chrCode * 16 + lineSprite);//Data line 1
				uint8 dataLine2 = memory->read(0x8000 + chrCode * 16 + lineSprite + 1);//Data line 2

				for (int pixel = 0; pixel < 8; pixel++)
				{
					int pixelIndex = pixel;

					if (verticalFlip)
						pixelIndex = (pixelIndex - 7) * -1;

					uint8 colorCode = getBit(dataLine1, pixelIndex) + (getBit(dataLine2, (pixelIndex)) << 1);

					uint8 color;
					if (testBit(lcdc, 4))
						color = transformDotDataToColor(colorCode, OPB0_PALETTE_DATA);
					else
						color = transformDotDataToColor(colorCode, OPB1_PALETTE_DATA);

					if (testBit(lcdc, 7))//Priority to background
					{
						//Do nothing (display pixel of background)
					}
					else//Priority to sprite
					{
						if (ly < DOTS_DISPLAY_Y)
							lcdScreen[xCoordinate + pixel][ly] = colorToRGB(color);
					}
				}
			}
		}
	}
}

void Ppu::setRegisters()
{
	uint8 ly = memory->read(LY_ADDRESS);
	uint8 lyc = memory->read(LYC_ADDRESS);
	memory->setResetBitMemory(STAT_ADDRESS, (ly == lyc), 2);
}

uint8 Ppu::transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress)
{
	switch (dotData)
	{
	case(0b00):
	{
		return ((memory->read(dataPaletteAddress) & 0b00000011));
		break;
	}
	case(0b01):
	{
		return ((memory->read(dataPaletteAddress) & 0b00001100) >> 2);
		break;
	}
	case(0b10):
	{
		return ((memory->read(dataPaletteAddress) & 0b00110000) >> 4);
		break;
	}
	case(0b11):
	{
		return ((memory->read(dataPaletteAddress) & 0b11000000) >> 6);
		break;
	}
	default:
		cerr << "Error wrong data color code";
		exit(1);
		break;
	}
}

uint8 Ppu::colorToRGB(uint8 colorGameBoy)
{
	switch (colorGameBoy)
	{
	case (0b00):
	{
		return 0xFF;
		break;
	}
	case (0b01):
	{
		return 0xCC;
		break;
	}
	case (0b10):
	{
		return 0x77;
		break;
	}
	case (0b11):
	{
		return 0x00;
		break;
	}
	default:
		cerr << "Error wrong data color";
		exit(1);
		break;
	}
}

