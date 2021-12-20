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

void Ppu::draw(const int& cycles)
{
	drawLine(cycles);
	drawBackground();
}

void Ppu::drawLine(const int& cycles)
{
	/// <summary>
	/// Function that simulate the drawing of a line (in pixel not block) each cycle of the CPU
	/// </summary>
	/// <param name="cycles"></param>
	if ((memory->read(LCDC_ADDRESS) >> 7) == 1)
		memory->write(LY_ADDRESS, memory->read(LY_ADDRESS) + cycles);
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

	//Read all blocks code
	for (int j = 0; j < BLOCKS_DISPLAY_Y; j++)
	{
		for (int i = 0; i < DOTS_DISPLAY_X; i++)
		{
			memory->read(bGCodeAreaSelection + (i + scx) + ((j + scy) * BLOCKS_MEMORY_X));//Get character code (p55)

			//If scx and scy are hight and the selection screen is out take the first values
			//if (scx+)

			//Use character code to find character data to write on screen
			//memory->read(bgCharacterDataSelection+characterCode);

			//Write character to screen
			//lcdScreen
		}
	}
}

void darwWindows();
void drawSprites();

uint8_t Ppu::getDot(int indexX, int indexY)
{
	//if (memory->read(LCDC_ADDRESS))
	//{
	//}
}

bool Ppu::testBit(int value, int bitNumber)
{
	return ((value >> bitNumber) == 1);
}