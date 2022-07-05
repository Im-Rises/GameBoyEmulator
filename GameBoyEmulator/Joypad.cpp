#include "Joypad.h"

#include <iostream>

#include "SDL2/include/SDL.h"

using namespace std;

Joypad::Joypad()
{
	keystate = SDL_GetKeyboardState(NULL); //Get pointer to the state of all keys of the keayboard
	// previousInputs = 0b11111111;
	enableInterrupt = false;

	if (SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK) != 0)
	{
		cerr << "Error: Cannot init GameController and Joystick handling" << SDL_GetError() << endl;
	}

	cout << "Number of connected controllers and joysticks " << SDL_NumJoysticks() << ":" << endl;

	// gameController = SDL_NumJoysticks() ? SDL_GameControllerOpen(0) : NULL;
	gameController = SDL_GameControllerOpen(0);
	if (gameController != NULL)
	{
		cout << "Using controller 0: " << SDL_GameControllerName(gameController) << " 0" << endl;
#ifdef _WIN32
		// SDL_GameControllerSetLED(gameController, 0xFF,0,0);//Red
		SDL_GameControllerSetLED(gameController, 0x00, 0xFF, 0x00); //Green
		// SDL_GameControllerSetLED(gameController, 0,0,0xFF);//Blue
#endif
		SDL_GameControllerRumble(gameController, 0xFFFF, 0xFFFF, 100);
	}
	else
		cout << "No controller, use keyboard" << endl;
}

Joypad::~Joypad()
{
	if (gameController != NULL)
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

	uint8 gameBoyInputs = 0;

	SDL_PumpEvents();

	// Keyboard
	gameBoyInputs |= keystate[SDL_SCANCODE_RIGHT] << 0;
	gameBoyInputs |= keystate[SDL_SCANCODE_LEFT] << 1;
	gameBoyInputs |= keystate[SDL_SCANCODE_UP] << 2;
	gameBoyInputs |= keystate[SDL_SCANCODE_DOWN] << 3;
	gameBoyInputs |= keystate[SDL_SCANCODE_D] << 4;
	gameBoyInputs |= keystate[SDL_SCANCODE_S] << 5;
	gameBoyInputs |= keystate[SDL_SCANCODE_SPACE] << 6;
	gameBoyInputs |= keystate[SDL_SCANCODE_RETURN] << 7;

	if (gameController != NULL)
	{
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) << 0;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT) << 1;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_UP) << 2;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN) << 3;

		int16 stickX = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTX);
		int16 stickY = SDL_GameControllerGetAxis(gameController, SDL_CONTROLLER_AXIS_LEFTY);
		gameBoyInputs |= (stickX > 5000) << 0;
		gameBoyInputs |= (stickX < -5000) << 1;
		gameBoyInputs |= (stickY > 5000) << 3;
		gameBoyInputs |= (stickY < -5000) << 2;

		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_B) << 4;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_A) << 5;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_BACK) << 6;
		gameBoyInputs |= SDL_GameControllerGetButton(gameController, SDL_CONTROLLER_BUTTON_START) << 7;
	}

	gameBoyInputs = ~gameBoyInputs;

	uint8 previousInputs = 0xFF;

	if (!testBit(memoryInputs, 4)) //Directions buttons
	{
		memoryInputs &= 0xF0;
		memoryInputs |= (gameBoyInputs & 0xF);

		// // //Check if there if the button is pressed (from 1 to 0)
		// // checkInputsInterrupt(gameBoyInputs & 0xF, previousInputs & 0xF);
		//
		// //Change only the directional buttons to set their previous state
		// previousInputs &= 0xF0;
		// previousInputs |= gameBoyInputs & 0x0F;
	}
	else if (!testBit(memoryInputs, 5)) //Action buttons
	{
		memoryInputs &= 0xF0;
		memoryInputs |= (gameBoyInputs >> 4);

		// // //Check if there if the button is pressed (from 1 to 0)
		// // checkInputsInterrupt(gameBoyInputs >> 4, previousInputs >> 4);
		//
		// //Change only the action buttons to set their previous state
		// previousInputs &= 0x0F;
		// previousInputs |= gameBoyInputs & 0xF0;
	}

	return memoryInputs;
}

void Joypad::checkInputsInterrupt(uint8 currentInputs, uint8 previousInputs)
{
	// enableInterrupt = false;
	// // cout << (int)previousInputs << endl;
	//
	// for (int i = 0; i < 4; i++)
	// {
	// 	if ((testBit(previousInputs, i) == 1) && (testBit(currentInputs, i) == 0))
	// 		//If previous input equals 1 and current button input equals 0 
	// 		enableInterrupt = true;
	// }
}


bool Joypad::getEnableInterrupt()
{
	return enableInterrupt;
}
