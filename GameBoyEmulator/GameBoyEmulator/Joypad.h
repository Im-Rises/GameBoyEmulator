#ifndef DEF_JOYPAD
#define DEF_JOYPAD

#include "binaryLib.h"
#include "SDL2/include/SDL.h"

class Joypad
{
private:
	uint8 previousInputs;
	const uint8* keystate = nullptr;
	bool enableInterrupt;

public:
	Joypad();
	uint8 readInputs(uint8 inputsInMemory);
private:
	void checkInputsInterrupt(uint8 currentInputs, uint8 previousInputs);
public:
	bool getEnableInterrupt();
};

#endif 