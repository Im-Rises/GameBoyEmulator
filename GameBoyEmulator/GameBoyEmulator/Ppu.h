#ifndef DEF_LCD
#define DEF_LCD 

#include <iostream>
#include "Memory.h"

#define DOTS_NUMBER_X 256
#define DOTS_NUMBER_Y 256

#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144

#define VERTICAL_BLANKING_LINES_NUMBER 154

#define BLOCKS_DISPLAY_X 20
#define BLOCKS_DISPLAY_Y 18

#define BLOCKS_MEMORY_X 32
#define BLOCKS_MEMORY_Y 32

struct Block {

};

class Ppu
{
private:
	Memory* memory = nullptr;
	uint8_t lcdScreen[DOTS_DISPLAY_X][DOTS_DISPLAY_Y];

public:
	Ppu(Memory* memory);
	void draw(const int& cycles);
	uint8_t getLcdScreenPixel(int indexX, int indexY);

private:
	void drawLine();
	void drawBackgroundLine();
	void drawSprites();

	void drawCharacScreen(int x, int y, uint16_t dataCharacAddress);

	uint8_t transformDotDataToColor(uint8_t dotData, uint16_t dataPaletteAddress);


	uint8_t getBit(uint8_t byte, int bitIndex);

	bool testBit(int value, int bitNumber);
};

#endif