#ifndef DEF_LCD
#define DEF_LCD 

#include <iostream>

#include "Memory.h"

#define DOTS_NUMBER_X 256
#define DOTS_NUMBER_Y 256

#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144


class Ppu
{
private:
	Memory* memory = nullptr;

public:
	Ppu(Memory* memory);
	void drawLine(int cycles);
};

#endif