#ifndef DEF_LCD
#define DEF_LCD 

#include "binaryLib.h"
#include "Memory.h"
#include "SDL2/include/SDL.h"

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
	grayscaleNative = 0,
	grayscaleReal=1,
	greenscaleNative = 2,
	greenscaleReal=3,
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

	int currentColorMode;

	struct ColorModePalette
	{
		ColorRGB darkest;
		ColorRGB dark;
		ColorRGB light;
		ColorRGB lightest;
	} GameBoyColorMode;

	uint8 lcd[160 * 144 * 3];
	bool lcdTransparent[160 * 144 * 3];

	int scanLineCounter;
	uint8 LY;
	uint8 LYC;


	//SDL
	string windowTitle = "GameBoyEmulator";
	string gameName;
	string screenshotsPath;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture;
	SDL_Event event;

	bool windowing;
	int windowingWidth;
	int windowingHeigth;


public:
	Ppu(Memory* memory, ColorMode colorMode = grayscaleReal);
	~Ppu();


public:
	// SDL functions
	void updateScreen();
	void addGameNameWindow(string text);
	void displayFramerate(const int& value) const;
	bool windowHandling();
	void doScreenshot(string path);
	void toggleFullScreen();
	string getDateTime();

	// Game Boy screen functions
public:
	void reset();
	void setGameBoyColorMode(const int& colorMode);
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

// public:
// 	string getScreenshotsPath();
};

#endif
