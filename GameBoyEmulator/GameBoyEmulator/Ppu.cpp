#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;

	for (int j = 0; j < DOTS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < DOTS_DISPLAY_X; i++)
		{
			lcdScreen[i][j] = 255;
		}
	}
}

uint8_t Ppu::getLcdScreenPixel(int indexX, int indexY)
{
	return lcdScreen[indexX][indexY];
}


void Ppu::draw(const int& cycles)//Not working
{
	for (int i = 0; i < cycles; i++)
	{
		drawLineSimulation();
		drawBackgroundLine();
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

	uint8_t lcdc = memory->read(LCDC_ADDRESS);

	if (testBit(lcdc, 0))
	{
		uint8_t scx = memory->read(SCX_ADDRESS);
		uint8_t scy = memory->read(SCY_ADDRESS);
		uint8_t wx = memory->read(WX_ADDRESS) - 7;//Why 7 because : With WX = 7, the window is displayed from the left edge of the LCD screen. Values of 0-6 should not be specified for WX.
		uint8_t wy = memory->read(WY_ADDRESS);

		uint8_t ly = memory->read(LY_ADDRESS);

		bool windowing = false;

		uint16_t tileDataArea;
		bool unsignedValue = true;

		uint16_t backgroundMemoryCode;


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

		uint8_t yPos;
		if (windowing)
			yPos = ly - wy;//WHY THAT ?
		else
			yPos = scy + ly;

		/// <summary>
		/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// </summary>
		uint16_t tileRow = (yPos / 8) * 32;
		/// <summary>
		/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// </summary>

		for (int pixel = 0; pixel < DOTS_DISPLAY_X; pixel++)
		{
			uint8_t xPos = pixel + scx;

			if (windowing && pixel >= wx)
				xPos = pixel - wx;//Why that

			uint8_t tileColumn = xPos / 8;

			/// <summary>
			/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// </summary>
			int16_t tileNum;//Can be signed or unsigend depending of the tileDataArea

			if (unsignedValue)
				tileNum = (uint8_t)memory->read(backgroundMemoryCode + tileRow + tileColumn);
			else
				tileNum = (int8_t)memory->read(backgroundMemoryCode + tileRow + tileColumn);
			/// <summary>
			/// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/// </summary>

			uint16_t tileLocation;
			if (unsignedValue)
				tileLocation = tileDataArea + tileNum * 16;
			else
				tileLocation = tileDataArea + (tileNum + 128) * 16;

			//cout << hex << (int)tileLocation << endl;

			uint8_t line = (yPos % 8) * 2;
			uint8_t dataLine1 = memory->read(tileLocation + line);
			uint8_t dataLine2 = memory->read(tileLocation + line + 1);

			uint8_t bitIndex = (((xPos % 8) - 7) * -1);
			uint8_t colorCode = getBit(dataLine1, bitIndex) + (getBit(dataLine2, (bitIndex)) << 1);

			uint8_t color = transformDotDataToColor(colorCode, BG_PALETTE_DATA);

			if (ly < DOTS_DISPLAY_Y)
				lcdScreen[pixel][ly] = color;
			//else
			//	cout << "issue" << endl;
		}
	}



	/*
			uint8_t lcdc = memory->read(LCDC_ADDRESS);

			//if (testBit(lcdc, 0))
			//{
			uint8_t scx = memory->read(SCX_ADDRESS);
			uint8_t scy = memory->read(SCY_ADDRESS);
			uint8_t wx = memory->read(WX_ADDRESS);
			uint8_t wy = memory->read(WY_ADDRESS);

			uint8_t yPosLcd = memory->read(LY_ADDRESS);//Line being written by the ppu/lcd

			bool windowing = false;

			//if (testBit(lcdc, 5))
			//{
			//	if (wy <= yPosLcd)
			//		windowing = true;
			//}

			uint16_t bGCodeAreaSelection;
			if (!testBit(lcdc, 3))
				bGCodeAreaSelection = BG_DISPLAY_DATA_1;//Bit 3 equals 0
			else
				bGCodeAreaSelection = BG_DISPLAY_DATA_2;//Bit 3 equals 1

			uint16_t windowCodeAreaSelection;
			if (!testBit(lcdc, 6))
				windowCodeAreaSelection = WINDOW_CODE_AREA_SELECTION_0;
			else
				windowCodeAreaSelection = WINDOW_CODE_AREA_SELECTION_1;

			uint16_t bgCharacterDataSelection;
			if (!testBit(lcdc, 4))
				bgCharacterDataSelection = BG_CHARACTER_DATA_SELECTION_0;//Bit 4 equals 0
			else
				bgCharacterDataSelection = BG_CHARACTER_DATA_SELECTION_1;//Bit 4 equals 1



			uint16_t codeAreaSelection;

			if (windowing)
			{
				codeAreaSelection = windowCodeAreaSelection;
			}
			else
			{
				codeAreaSelection = bGCodeAreaSelection;
			}

			for (int i = 0; i < DOTS_DISPLAY_X; i++)
			{
				//Get x position of pixel to write to screen
				uint8_t xPosLcd = i;

				//If windowing and pixel been drawed is greater equals than wx
				//if (windowing && i >= wx)
				//{
				//	xPosLcd -= wx;
				//}

				//Get tile
				uint8_t tileNumber = memory->read(codeAreaSelection + ((scx + xPosLcd) / 8) + (((scy + yPosLcd) / 8) * 32));
				uint8_t tileAddress = bgCharacterDataSelection + tileNumber * 16;

				//Get data line 1 and 2 of tile to know pixel color
				uint8_t tileDataLine1 = memory->read(tileAddress + (((yPosLcd + scy) % 8) * 2));
				uint8_t tileDataLine2 = memory->read(tileAddress + (((yPosLcd + scy) % 8) * 2) + 1);

				if (tileAddress == 0x8190 || (tileAddress + 1) == 0x8190)
					cout << "Working!" << endl;

				//Get color num code (dot data)
				uint8_t colorNum = getBit(tileDataLine1, xPosLcd % 8) + (getBit(tileDataLine2, xPosLcd % 8) << 1);

				//Attribute the color value corresponding to the color num
				uint8_t color = transformDotDataToColor(colorNum, BG_PALETTE_DATA);

				//Draw pixel on screen
				lcdScreen[xPosLcd][yPosLcd] = color;
			}
	*/
}

void Ppu::drawSpritesLine()
{

}

uint8_t Ppu::transformDotDataToColor(const uint8_t& dotData, const uint16_t& dataPaletteAddress)
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

uint8_t Ppu::colorToRGB(uint8_t colorGameBoy)
{
	switch (colorGameBoy)
	{
	case(0b00):
	{
		return 0xFF;
		break;
	}
	case(0b01):
	{
		return 0xCC;
		break;
	}
	case(0b10):
	{
		return 0x77;
		break;
	}
	case(0b11):
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


uint8_t Ppu::getBit(uint8_t byte, int bitIndex)
{
	//return ((byte & (0b00000001 << bitIndex)) >> bitIndex);
	return (byte >> bitIndex) & 0x1;
}

bool Ppu::testBit(int value, int bitNumber)
{
	return (((value >> bitNumber) & 0x1) == 1);
}