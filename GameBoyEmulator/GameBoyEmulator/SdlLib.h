#ifndef DEF_SDLLIB
#define DEF_SDLLIB

#include "SDL2/include/SDL.h"
#include "binaryLib.h"
#include <iostream>

using namespace std;

class SdlLib
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	int pixelsSize;
	bool running;

	const uint8* keystate;
	uint8 gameBoyInputs;

public:
	SdlLib(int width, int height, string title);
	~SdlLib();

private:
	void stopSdl();

public:
	void drawSquare(const float& pixelSize, const int& x, const int& y, const int& color);

	void renderPresent();

	uint8 readGameBoyInputs();

	uint32 getTicks();

	bool readExitInputs();

	bool isRunning();
};

#endif 
