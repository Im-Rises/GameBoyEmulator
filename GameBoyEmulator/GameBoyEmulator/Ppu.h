#ifndef DEF_LCD
#define DEF_LCD 

#include <iostream>
#include "Memory.h"

#define DOTS_NUMBER_X 256
#define DOTS_NUMBER_Y 256

#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144

#define VERTICAL_BLANKING_LINES_NUMBER 154

class Ppu
{
private:
	Memory* memory = nullptr;
	uint8_t lcdScreen[DOTS_DISPLAY_X][DOTS_DISPLAY_Y];

public:
	Ppu(Memory* memory);
	void draw(const int& cycles);
	void drawLine(const int& cycles);

	void drawBackground();
	void darwWindows();
	void drawSprites();

	uint8_t getBlock(int indexX, int indexY);

	bool testBit(int value, int bitNumber);
};

#endif