#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;
}

void Ppu::draw(const int& cycles)
{
	drawLine(cycles);
}

void Ppu::drawLine(const int& cycles)
{
	/// <summary>
	/// Function that simulate the drawing of a line each cycle of the CPU
	/// </summary>
	/// <param name="cycles"></param>
	if ((memory->read(LCD_LCDC) >> 7) == 1)
		memory->write(LCD_LY, memory->read(LCD_LY) + cycles);
	else
		memory->write(LCD_LY, 0);

	if (memory->read(LCD_LY) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LCD_LY, 0);
}

void Ppu::drawBackground()
{
	bool bank = memory->read(VBK_ADDRESS);//In DGB always zero

	//uint8_t scx = memory->read(SCX_ADDRESS);
	//uint8_t scy = memory->read(SCY_ADDRESS);


	////BG Code Area Selection Flag
	////	0: 9800h - 9BFFh
	////	1: 9C00h - 9FFFh
	//uint16_t chrCodeAddress =
	//	if ()
	//	{

	//	}
	//	else
	//	{

	//	}




}

void darwWindows();
void drawSprites();

uint8_t Ppu::getBlock(int indexX, int indexY)
{
	//if (memory->read(LCDC_ADDRESS))
	//{
	//}
}

bool Ppu::testBit(int value, int bitNumber)
{
	return ((value >> bitNumber) == 1);
}