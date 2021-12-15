#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;
}

void Ppu::draw(int cycles)
{
	if ((memory->read(LCD_LCDC) >> 7) == 1)
		memory->write(LCD_LY, memory->read(LCD_LY) + cycles);
	else
		memory->write(LCD_LY, 0);

	if (memory->read(LCD_LY) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LCD_LY, 0);

	//cout << "Value of LCD_LY = " << hex << (int)memory->read(LCD_LY) << endl;
}

void Ppu::drawLine(int cycles)
{
	memory->increment(LCD_LY);
}

