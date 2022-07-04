#ifndef DEF_LCD
#define DEF_LCD 

#include "binaryLib.h"
#include "Memory.h"
#include "SDL2/include/SDL.h"
// #include "GameBoy.h"

#define DOTS_DISPLAY_X 160
#define DOTS_DISPLAY_Y 144

#define VERTICAL_BLANKING_LINES_NUMBER 154

#define BLOCKS_DISPLAY_X 20
#define BLOCKS_DISPLAY_Y 18

#define BLOCKS_MEMORY_X 32
#define BLOCKS_MEMORY_Y 32

#define SPRITES_NUMBER 40
#define SPRITES_NUMBER_PER_LINE 10

#define EMULATOR_SCREEN_SIZE_X 640
#define EMULATOR_SCREEN_SIZE_Y 576

enum ColorMode
{
	grayscale,
	greenscale
};

struct ColorRGB
{
	uint8 r;
	uint8 g;
	uint8 b;
};

class Ppu
{
private:
	//GameBoy
	Memory* memory = nullptr;

	// struct Screen
	// {
	// 	uint8 colorRGB;
	// 	bool backgroundTransparent;
	// } lcdScreen[DOTS_DISPLAY_X][DOTS_DISPLAY_Y];


	ColorMode currentColorMode;
	struct ColorModePalette
	{
		ColorRGB black;
		ColorRGB gray1;
		ColorRGB gray2;
		ColorRGB white;
	} GameBoyColorMode;

	uint8 lcd[160 * 144 * 3];
	bool lcdTransparent[160 * 144 * 3];

	int scanLineCounter;
	uint8 LY;
	uint8 LYC;


	//SDL
	string windowTitle = "GameBoyEmulator";

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture;
	SDL_Event event;

	bool windowing;
	int windowingWidth;
	int windowingHeigth;


public:
	Ppu(Memory* memory, ColorMode colorMode = greenscale);
	// Ppu(Memory* memory, int windowWidth = 640, int windowHeight = 576);
	~Ppu();


public:
	// SDL functions
	void toggleFullScreen();
	void updateScreen();
	// void SDL_drawSquare(const int& x, const int& y, const int& color);
	void displayFramerate(const int& value) const;
	bool windowIsActive();

	// Game Boy screen functions
public:
	void reset();
	void setGameBoyColorMode(const ColorMode& colorMode);
	void setPixel(const int& x, const int& y, const uint8& r, const uint8& g, const uint8& b);
	void draw(const int& cycles);
private:
	void updateStatRegister();
	void drawLine();
	void drawBackgroundLine(const uint8& lcdc);
	void drawSpritesLine(const uint8& lcdc);
	uint8 transformDotDataToColor(const uint8& dotData, const uint16& dataPaletteAddress);
	ColorRGB colorToRGB(uint8 colorGameBoy);
	void requestInterrupt(const uint8& bitIndex);
	bool checkLyEqualsLyc();
};

#endif
