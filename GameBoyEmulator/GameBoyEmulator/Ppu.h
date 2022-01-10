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


class Ppu
{
private:
	Memory* memory = nullptr;

	struct Screen {
		uint8 colorRGB;
		bool backgroundTransparent;
	}
	lcdScreen[DOTS_DISPLAY_X][DOTS_DISPLAY_Y];

	int scanLineCounter;

public:
	Ppu(Memory* memory);
	void reset();
	void draw(const int& cycles);


private:
	void updateStatRegister();
	void drawLine();
	void drawBackgroundLine(uint8 lcdc);
	void drawSpritesLine(uint8 lcdc);

	uint8 transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress);
	uint8 colorToRGB(uint8 colorGameBoy);

	void requestInterrupt(const uint8& intertuptCode);

public:
	uint8 getLcdScreenPixel(int indexX, int indexY)const;
};

#endif