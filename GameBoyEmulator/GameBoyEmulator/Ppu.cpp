#include "Ppu.h"

Ppu::Ppu(Memory* memory)
{
	this->memory = memory;
}

void Ppu::drawLine(int cycles)
{
	//int lineWritten = memory->read(LCD_LY);
	//for (int i = lineWritten; i < (lineWritten + cycles); i++)
	//{
	//	memory->write(LCD_LY, i);
	//}
}

