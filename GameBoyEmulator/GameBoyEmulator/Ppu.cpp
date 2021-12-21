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

//void Ppu::draw(const int& cycles)//Working
//{
//	drawLine(cycles);
//	//drawBackground();
//	cout << hex<<(int)memory->read(LY_ADDRESS) << endl;
//}

void Ppu::draw(const int& cycles)//Not working
{
	for (int i = 0; i < cycles; i++)
	{
		drawLine(1);
		//rawBackground();
	}
	cout << hex<<(int)memory->read(LY_ADDRESS) << endl;
}

void Ppu::drawLine(const int& cycles)
{
	/// <summary>
	/// Function that simulate the drawing of a line each cycle of the CPU (in pixel not block) 
	/// </summary>
	/// <param name="cycles"></param>
	if ((memory->read(LCDC_ADDRESS) >> 7) == 1)
		memory->write(LY_ADDRESS, (memory->read(LY_ADDRESS) + cycles));
	else
		memory->write(LY_ADDRESS, 0);

	if (memory->read(LY_ADDRESS) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LY_ADDRESS, 0);
}

void Ppu::drawBackground()
{
	//bool bank = memory->read(VBK_ADDRESS);//In DGB always zero

	uint8_t lcdc = memory->read(LCDC_ADDRESS);
	uint8_t stat = memory->read(STAT_ADDRESS);
	uint8_t scx = memory->read(SCX_ADDRESS);
	uint8_t scy = memory->read(SCY_ADDRESS);
	uint8_t wx = memory->read(WX_ADDRESS);
	uint8_t wy = memory->read(WY_ADDRESS);

	bool windowing = testBit(lcdc, 5);

	uint16_t bGCodeAreaSelection;
	if (!testBit(lcdc, 3))
		bGCodeAreaSelection = BG_DISPLAY_DATA_1;//Bit 3 equals 0
	else
		bGCodeAreaSelection = BG_DISPLAY_DATA_2;//Bit 3 equals 1


	uint16_t bgCharacterDataSelection;
	if (!testBit(lcdc, 4))
		bgCharacterDataSelection = BG_CHARACTER_DATA_SELECTION_0;//Bit 4 equals 0
	else
		bgCharacterDataSelection = BG_CHARACTER_DATA_SELECTION_1;//Bit 4 equals 1

	uint16_t windowCodeAreaSelection;
	if (!testBit(lcdc, 6))
		windowCodeAreaSelection = WINDOW_CODE_AREA_SELECTION_0;
	else
		windowCodeAreaSelection = WINDOW_CODE_AREA_SELECTION_1;


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
		//lcdScreen[i][memory->read(LY_ADDRESS)] = pixelValue;
	}

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
}

void drawWindows();
void drawSprites();



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

uint8_t Ppu::getDot(int indexX, int indexY)
{
	//if (memory->read(LCDC_ADDRESS))
	//{
	//}
	return 0;
}

bool Ppu::testBit(int value, int bitNumber)
{
	return ((value >> bitNumber) == 1);
}