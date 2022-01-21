#ifndef DEF_SDLLIB
#define DEF_SDLLIB

#include <iostream>
#include <string>

#include "SDL2/include/SDL.h"
#include "binaryLib.h"

using namespace std;

class SdlLib
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	string windowTitle;

	bool windowing;
	int windowingWidth;
	int windowingHeigth;
	int xOffset;
	int yOffset;
	int pixelsSize;
	int numberPixelsX;
	int numberPixelsY;



	bool running;

	const uint8* keystate;
	uint8 gameBoyInputs;

public:
	SdlLib(int windowWidth, int windowHeight, int numberPixelsX, int numberPixelsY, string title);
	~SdlLib();

private:
	void stopSdl();
	void setPixelsSize(const int& width, const int& height);

public:
	void drawSquare(const int& x, const int& y, const int& color);

	void renderPresent();

	//uint8 readGameBoyInputs();

	uint32 getTicks();

	bool readEmulatorInputs();

	bool isRunning();

	void setFps(const int fps);

	void toggleFullScreen();
};

#endif 
