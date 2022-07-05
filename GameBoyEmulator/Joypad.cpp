#include "Joypad.h"

#include <iostream>

#include "SDL2/include/SDL.h"

Joypad::Joypad()
{
	keystate = SDL_GetKeyboardState(NULL); //Get pointer to the state of all keys of the keayboard
	previousInputs = 0b11111111;
	enableInterrupt = false;

	if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) != 0)
	{
		std::cerr << "Error: Cannot init GameController and Joystick handling" << SDL_GetError() << std::endl;
	}

	std::cout << "Number of connected controllers and joysticks " << SDL_NumJoysticks() << ":" << std::endl;
	// for (int i = 0; i < SDL_NumJoysticks(); ++i)
	// {
	// 	std::cout << SDL_JoystickName << std::endl;
	// }

	gameController = SDL_NumJoysticks() ? SDL_GameControllerOpen(0) : NULL;
	if (gameController != NULL)
	{
		std::cout << "Using controller 0: " << SDL_GameControllerName(gameController) << " 0 (" << SDL_GameControllerGetJoystick(gameController) << ")" << std::endl;
		// SDL_GameControllerSetLED(gameController, 0xFF,0,0);//Red
		SDL_GameControllerSetLED(gameController, 0x00, 0xFF, 0x00); //Green
		// SDL_GameControllerSetLED(gameController, 0,0,0xFF);//Blue
		SDL_GameControllerRumble(gameController, 0xFFFF, 0xFFFF, 100);
	}
	else
		std::cout << "No controller, use keyboard" << std::endl;
}

Joypad::~Joypad()
{
	if (gameController!=NULL)
	{
		SDL_GameControllerClose(gameController);
	}
}


uint8 Joypad::readInputs(uint8 memoryInputs) //Memory inputs indicate which type of input is readed
{
	/*
	* User inputs bits:
	* Right  = 0b00000001
	* Left   = 0b00000010
	* Up     = 0b00000100
	* Down   = 0b00001000
	* A      = 0b00010000
	* B      = 0b00100000
	* Select = 0b01000000
	* Start  = 0b10000000
	*/
	uint8 gameBoyInputs;

	SDL_PumpEvents();

	(keystate[SDL_SCANCODE_RIGHT])
		? gameBoyInputs = resetBit(gameBoyInputs, 0)
		: gameBoyInputs = setBit(gameBoyInputs, 0);
	(keystate[SDL_SCANCODE_LEFT])
		? gameBoyInputs = resetBit(gameBoyInputs, 1)
		: gameBoyInputs = setBit(gameBoyInputs, 1);
	(keystate[SDL_SCANCODE_UP]) ? gameBoyInputs = resetBit(gameBoyInputs, 2) : gameBoyInputs = setBit(gameBoyInputs, 2);
	(keystate[SDL_SCANCODE_DOWN])
		? gameBoyInputs = resetBit(gameBoyInputs, 3)
		: gameBoyInputs = setBit(gameBoyInputs, 3);
	(keystate[SDL_SCANCODE_D]) ? gameBoyInputs = resetBit(gameBoyInputs, 4) : gameBoyInputs = setBit(gameBoyInputs, 4);
	(keystate[SDL_SCANCODE_S]) ? gameBoyInputs = resetBit(gameBoyInputs, 5) : gameBoyInputs = setBit(gameBoyInputs, 5);
	(keystate[SDL_SCANCODE_SPACE])
		? gameBoyInputs = resetBit(gameBoyInputs, 6)
		: gameBoyInputs = setBit(gameBoyInputs, 6);
	(keystate[SDL_SCANCODE_RETURN])
		? gameBoyInputs = resetBit(gameBoyInputs, 7)
		: gameBoyInputs = setBit(gameBoyInputs, 7);

	if (gameController)
	{
		
	}

	if (!testBit(memoryInputs, 4)) //Directions buttons
	{
		memoryInputs &= 0xF0;
		memoryInputs |= (gameBoyInputs & 0xF);

		//Check if there if the button is pressed (from 1 to 0)
		checkInputsInterrupt(gameBoyInputs & 0xF, previousInputs & 0xF);

		//Change only the directional buttons to set their previous state
		previousInputs &= 0xF0;
		previousInputs |= gameBoyInputs & 0x0F;
	}
	else if (!testBit(memoryInputs, 5)) //Action buttons
	{
		memoryInputs &= 0xF0;
		memoryInputs |= (gameBoyInputs >> 4);

		//Check if there if the button is pressed (from 1 to 0)
		checkInputsInterrupt(gameBoyInputs >> 4, previousInputs >> 4);

		//Change only the action buttons to set their previous state
		previousInputs &= 0x0F;
		previousInputs |= gameBoyInputs & 0xF0;
	}

	return memoryInputs;
}

void Joypad::checkInputsInterrupt(uint8 currentInputs, uint8 previousInputs)
{
	enableInterrupt = false;

	for (int i = 0; i < 4; i++)
	{
		if ((testBit(previousInputs, i) == 1) && (testBit(currentInputs, i) == 0))
			//If previous input equals 1 and current button input equals 0 
			enableInterrupt = true;
	}
}


bool Joypad::getEnableInterrupt()
{
	return enableInterrupt;
}
