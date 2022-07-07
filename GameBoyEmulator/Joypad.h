#ifndef DEF_JOYPAD
#define DEF_JOYPAD

#include "binaryLib/binaryLib.h"
#include "SDL2/include/SDL.h"

class Joypad
{
private:
	// uint8 previousInputs;
	bool enableInterrupt;
	const uint8* keystate = nullptr;
	SDL_GameController* gameController = nullptr;

public:
	Joypad();
	~Joypad();
	uint8 readInputs(uint8 inputsInMemory);
private:
	void checkInputsInterrupt(uint8 currentInputs, uint8 previousInputs);
public:
	bool getEnableInterrupt();
};

#endif
