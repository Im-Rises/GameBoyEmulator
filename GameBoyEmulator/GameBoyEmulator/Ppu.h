#ifndef DEF_LCD
#define DEF_LCD 

#include <iostream>

#include "Memory.h"

#include "binaryLib.h"

//#define DOTS_NUMBER_X 256
//#define DOTS_NUMBER_Y 256

#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144

#define VERTICAL_BLANKING_LINES_NUMBER 154

#define BLOCKS_DISPLAY_X 20
#define BLOCKS_DISPLAY_Y 18

#define BLOCKS_MEMORY_X 32
#define BLOCKS_MEMORY_Y 32

#define SPRITES_NUMBER 40

struct Block {

};

class Ppu
{
private:
	Memory* memory = nullptr;
	uint8 lcdScreen[DOTS_DISPLAY_X][DOTS_DISPLAY_Y];

public:
	Ppu(Memory* memory);
	void reset();
	uint8 getLcdScreenPixel(int indexX, int indexY);
	void draw(const int& cycles);

private:
	void drawLineSimulation();
	void drawBackgroundLine();
	void drawSpritesLine();
	void setRegisters();

	uint8 transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress);

};

#endif