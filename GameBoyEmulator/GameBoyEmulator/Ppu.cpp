#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;

	for (int j = 0; j < DOTS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < DOTS_DISPLAY_X; i++)
		{
			lcdScreen[i][j] = 0;
		}
	}
}

void Ppu::draw(const int& cycles)//Not working
{
	for (int i = 0; i < cycles; i++)
	{
		drawLine();
		drawBackgroundLine();
	}

	if (memory->read(LY_ADDRESS) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LY_ADDRESS, 0);
}

void Ppu::drawLine()
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
	//bool bank = memory->read(VBK_ADDRESS);//In DGB always zero

	uint8_t lcdc = memory->read(LCDC_ADDRESS);
	//uint8_t stat = memory->read(STAT_ADDRESS);
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

		//Get color num code (dot data)
		uint8_t colorNum = getBit(tileDataLine1, xPosLcd % 8) + (getBit(tileDataLine2, xPosLcd % 8) << 1);

		//Attribute the color value corresponding to the color num
		uint8_t color = transformDotDataToColor(colorNum, BG_PALETTE_DATA);

		//Draw pixel on screen
		lcdScreen[xPosLcd][yPosLcd] = color;
	}
}

uint8_t Ppu::transformDotDataToColor(uint8_t dotData, uint16_t dataPaletteAddress)
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


uint8_t Ppu::getBit(uint8_t byte, int bitIndex)
{
	return ((byte & (0b00000001 << bitIndex)) >> bitIndex);
}

//RESUME HERE
	//uint16_t lineWritten = memory->read(LY_ADDRESS);//Line being written by the ppu/lcd
	//for (int i = 0; i < BLOCKS_DISPLAY_X; i++)//Get all character codes
	//{
	//	uint16_t characAddress = (scx + codeAreaSelection + i * 0xF) % BLOCKS_DISPLAY_X + ((scy + lineWritten) * BLOCKS_DISPLAY_X);//Address of charac
	//	uint8_t characLine1 = memory->read(characAddress);//Line1 of character
	//	uint8_t characLine2 = memory->read(characAddress + 1);//Line2 of character
	//	for (int j = 0; j < 8; j++)//Attribute the bit 1, 2, 3, etc... of charac1 + charac2 to the pixels of the screen
	//	{
	//		lcdScreen[j][lineWritten] = (characLine1 > j) & 0x1 + (((characLine2 > j) & 0x1) << 1);
	//	}
	//}



	/*
	//Read all blocks code
	for (int j = 0; j < BLOCKS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < BLOCKS_DISPLAY_X; i++)
		{
			//Calcul the dots to get
			uint8_t offsetX = (i + scx / 8);
			uint8_t offsetY = ((j + scy / 8) * BLOCKS_MEMORY_X);

			//If scx and scy are hight and the selection screen is out take the first values
			if (offsetX >= BLOCKS_MEMORY_X)
				offsetX -= BLOCKS_MEMORY_X;
			if (offsetY >= BLOCKS_MEMORY_Y)
				offsetY -= BLOCKS_MEMORY_Y;

			//Get character code address
			uint8_t chrCode = memory->read(bGCodeAreaSelection + offsetX + offsetY);//X00, X01, X02, X03 etc...

			//Use character code to find character data to write on screen
			uint16_t dataCharacAddress = bgCharacterDataSelection + chrCode * 0x10;//Address of first 8 bits of character data

			//Write character to screen (RESUME HERE)
			drawCharacScreen(i * 8, j * 8, dataCharacAddress);
		}
	}
	*/

	//void Ppu::drawCharacScreen(int x, int y, uint16_t dataCharacAddress)
//{
//	for (int j = 0; j < 16; j += 2)
//	{
//		//Draw line of charac on screen depending on line 1 and 2 we get color
//		uint8_t line1 = memory->read(dataCharacAddress + j);
//		uint8_t line2 = memory->read(dataCharacAddress + j + 1);
//
//		for (int i = 0; i < 8; i++)
//		{
//			lcdScreen[i][j] = ((line1 >> i) & 0x1) + ((line2 >> i) & 0x1);
//		}
//	}
//}


void drawSprites();




uint8_t Ppu::getLcdScreenPixel(int indexX, int indexY)
{
	return lcdScreen[indexX][indexY];
}

bool Ppu::testBit(int value, int bitNumber)
{
	return ((value >> bitNumber) == 1);
}