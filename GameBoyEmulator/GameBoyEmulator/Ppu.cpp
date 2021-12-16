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
	if ((memory->read(LCD_LCDC) >> 7) == 1)
		memory->write(LCD_LY, memory->read(LCD_LY) + cycles);
	else
		memory->write(LCD_LY, 0);

	if (memory->read(LCD_LY) >= VERTICAL_BLANKING_LINES_NUMBER)
		memory->write(LCD_LY, 0);
}

