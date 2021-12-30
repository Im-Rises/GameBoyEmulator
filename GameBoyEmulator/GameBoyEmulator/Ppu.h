#ifndef DEF_LCD
#define DEF_LCD 

#include "Memory.h"

#include <iostream>
#include "binaryLib.h"


#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144

#define VERTICAL_BLANKING_LINES_NUMBER 154

#define BLOCKS_DISPLAY_X 20
#define BLOCKS_DISPLAY_Y 18

#define BLOCKS_MEMORY_X 32
#define BLOCKS_MEMORY_Y 32

#define SPRITES_NUMBER 40
#define SPRITES_NUMBER_PER_LINE 10


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
	void draw(const int& cycles);

	uint8 getLcdScreenPixel(int indexX, int indexY);

private:
	void drawLineSimulation();
	void drawBackgroundLine();
	void drawSpritesLine();
	void setRegisters();

	uint8 transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress);
	uint8 colorToRGB(uint8 colorGameBoy);

};

#endif