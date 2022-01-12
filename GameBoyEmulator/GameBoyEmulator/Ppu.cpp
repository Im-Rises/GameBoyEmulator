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
			lcdScreen[i][j].colorRGB = 0xFF;
			lcdScreen[i][j].backgroundTransparent = false;
		}
	}
	scanLineCounter = 456;//Number of clock cycles to draw one scanline
}


void Ppu::draw(const int& cycles)
{
	updateStatRegister();
	uint8 lcdc = memory->read(LCDC_ADDRESS);

	if (testBit(lcdc, 7))
	{
		scanLineCounter -= cycles;

		if (scanLineCounter <= 0)
		{
			memory->write(LY_ADDRESS, memory->read(LY_ADDRESS) + 1);
			uint8 scanLine = memory->read(LY_ADDRESS);
			scanLineCounter = 456;

			if (scanLine == 144)
				requestInterrupt(0);
			else if (scanLine >= 154)
				memory->directWrite(LY_ADDRESS, 0);
			else if (scanLine < 144)
				drawLine();
		}
	}
}

void Ppu::updateStatRegister()//Thanks to http://www.codeslinger.co.uk/pages/projects/gameboy/lcd.html
{
	uint8 lcdc = memory->read(LCDC_ADDRESS);
	uint8 stat = memory->read(STAT_ADDRESS);

	if (!testBit(lcdc, 7))//If LCD is disable reset it
	{
		scanLineCounter = 456;
		memory->directWrite(LY_ADDRESS, 0);
		stat &= 0b11111000;
		stat = testBit(stat, 0);
		memory->directWrite(STAT_ADDRESS, stat);
	}
	else
	{
		uint8 scanLine = memory->read(LY_ADDRESS);
		uint8 currentMode = stat & 0b00000111;
		uint8 mode = 0;
		bool interruptSelection = 0;

		if (scanLine >= 144)
		{
			mode = 1;
			stat = setBit(stat, 0);
			stat = resetBit(stat, 1);
			interruptSelection = testBit(stat, 4);
		}
		else
		{
			int mode2bounds = 456 - 80;
			int mode3bounds = mode2bounds - 172;

			if (scanLine >= mode2bounds)
			{
				mode = 2;
				stat = setBit(stat, 1);
				stat = resetBit(stat, 0);
				interruptSelection = testBit(stat, 5);
			}
			else if (scanLine >= mode3bounds)
			{
				mode = 3;
				stat = setBit(stat, 1);
				stat = setBit(stat, 0);
			}
			else
			{
				mode = 0;
				stat = resetBit(stat, 1);
				stat = resetBit(stat, 0);
				interruptSelection = testBit(stat, 3);
			}
		}

		if (interruptSelection && (mode != currentMode))
		{
			requestInterrupt(1);
		}

		if (scanLine == memory->read(LYC_ADDRESS))
		{
			stat = setBit(stat, 2);
			if (testBit(stat, 6))
			{
				requestInterrupt(1);
			}
		}
		else
		{
			stat = resetBit(stat, 2);
		}
		memory->write(STAT_ADDRESS, stat);
	}
}

void Ppu::drawLine()
{
	uint8 lcdc = memory->read(LCDC_ADDRESS);
	drawBackgroundLine(lcdc);
	drawSpritesLine(lcdc);
}

void Ppu::drawBackgroundLine(uint8 lcdc)
{
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

			lcdScreen[pixel][ly].colorRGB = colorToRGB(color);
			lcdScreen[pixel][ly].backgroundTransparent = (colorCode == 0);
		}
	}
}

void Ppu::drawSpritesLine(uint8 lcdc)
{
	if (testBit(lcdc, 1))//if OBJ FLAG is ON
	{
		bool sprite8x16Dots = getBit(lcdc, 2); //0: 8 x 8 dots		1 : 8 x 16 dots

		for (int i = 0; i < SPRITES_NUMBER; i++)
		{
			int index = i * 4;//Sprites data are composed of 4 bytes of data

			uint8 yCoordinate = memory->read(OAM_Y_COODINATE + index) - 16;//In the official documentation it is written 10 because it is in hexa 0x10 so 16 in decimal
			uint8 xCoordinate = memory->read(OAM_X_COODINATE + index) - 8;
			uint8 chrCode = memory->read(OAM_CHR_CODE + index);
			uint8 attributeFlag = memory->read(OAM_ATTRIBUTE_FLAG + index);

			bool horizontalFlip = testBit(attributeFlag, 5);//xFlip
			bool verticalFlip = testBit(attributeFlag, 6);//yFlip
			bool displayPriorityBG = testBit(attributeFlag, 7);//Display priority


			uint8 ly = memory->read(LY_ADDRESS);

			uint8 spriteSize = sprite8x16Dots ? 16 : 8;

			if ((ly >= yCoordinate) && (ly < (yCoordinate + spriteSize)))//Before drawing sprite, we verify if it is not out of screen
			{
				uint8 lineSprite = ly - yCoordinate;//Get line to draw depending if the sprite is flipped horizontally or vertically

				if (verticalFlip)
					lineSprite = (lineSprite - spriteSize) * -1;

				lineSprite *= 2;
				uint8 dataLine1 = memory->read(0x8000 + chrCode * 16 + lineSprite);//Data line 1
				uint8 dataLine2 = memory->read(0x8000 + chrCode * 16 + lineSprite + 1);//Data line 2

				for (int pixel = 0; pixel < 8; pixel++)
				{
					int pixelIndex = pixel;

					if (!horizontalFlip)
						pixelIndex = (pixelIndex - 7) * -1;

					uint8 colorCode = getBit(dataLine1, pixelIndex) + (getBit(dataLine2, (pixelIndex)) << 1);

					bool transparent = (colorCode == 0);




					//if (colorCode == 0)//If color code is 0 than displaying background's pixel !displayPriorityBG && colorCode == 0
					//{
					//	//Do nothing (display pixel of background)
					//}
					//else
					//{
					//	int x = xCoordinate + pixel;
					//	if (0 <= x && x < 160)// Verify if pixel is not out of screen
					//		lcdScreen[x][ly] = colorToRGB(color);
					//}

					//Another way would be to stock in the lcdScreen the colorCode
					int x = xCoordinate + pixel;
					if (0 <= x && x < 160)
					{
						if ((!displayPriorityBG && !transparent) || (displayPriorityBG && !transparent && lcdScreen[x][ly].backgroundTransparent))//Display OBJ's pixel
						{
							uint8 color;
							if (!testBit(attributeFlag, 4))
								color = transformDotDataToColor(colorCode, OPB0_PALETTE_DATA);
							else
								color = transformDotDataToColor(colorCode, OPB1_PALETTE_DATA);

							lcdScreen[x][ly].colorRGB = colorToRGB(color);
						}
						else//Display BG' pixel
						{

						}
					}
				}
			}
		}
	}
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

void Ppu::requestInterrupt(const uint8& interruptCode)
{
	uint8 ifRegister = memory->read(INTERRUPT_FLAG_IF_ADDRESS);
	ifRegister = setBit(ifRegister, interruptCode);
	memory->write(INTERRUPT_FLAG_IF_ADDRESS, ifRegister);
}

uint8 Ppu::getLcdScreenPixel(int indexX, int indexY)const
{
	return lcdScreen[indexX][indexY].colorRGB;
}