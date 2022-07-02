#include "GameBoy.h"

#include <iostream>

GameBoy* GameBoy::gameboyInstance = 0;

GameBoy::GameBoy() : memory(&joypad, &spu), cpu(&memory, &ppu, &spu), ppu(&memory), spu(&memory)
{
	fps = 0;
	fpsStartTime = 0;
}

GameBoy* GameBoy::getInstance()
{
	if (gameboyInstance == 0)
	{
		gameboyInstance = new GameBoy();
	}

	return gameboyInstance;
}


void GameBoy::reset()
{
	cpu.reset();
	memory.reset();
	ppu.reset();
	spu.reset();
}

void GameBoy::setGameBoyWithoutBios()
{
	cpu.setCpuWithoutBios();
	memory.setMemoryWithoutBios();
	ppu.reset();
}

void GameBoy::loadBios(const string& biosPath)
{
	if (memory.loadBiosInMemory(biosPath) == false)
		exit(1);

	cpu.setCpuWithBios();
}

void GameBoy::insertGame(Cartridge* cartridge)
{
	this->cartridge = cartridge;
	memory.connectCartridge(cartridge);
}

void GameBoy::start()
{
	// SdlLib sdlLib(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, DOTS_DISPLAY_X, DOTS_DISPLAY_Y, PROJECT_NAME);//Create window

	const int cyclesToDo = CLOCK_FREQUENCY / 60;//Calcul the number of cycles for the update of the screen

	fpsStartTime = SDL_GetTicks();

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		// while (sdlLib.readEmulatorInputs() && cpu.getPc() < 0x100)//cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive()
		while (true)//cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive()
		{
			doGameBoyCycle(cyclesToDo);
		}

		//Load temporary array in memory
		memory.loadRomBeginning();
	}
	else
	{
		//Set emulator without bios
		this->setGameBoyWithoutBios();
	}


	// bool useSaveFile = false;
	// if (useSaveFile && cpu.getPc() == 0x100) //Once game is launching put save into ram
	// {
	// 	//loadSaveGame();
	// }


	// while (sdlLib.readEmulatorInputs())//sdlLib.windowIsActive()
	while (true)//sdlLib.windowIsActive()
	{
		doGameBoyCycle(cyclesToDo);
	}
}


void GameBoy::doGameBoyCycle(const int cyclesToDo)
{
	uint32_t startTime = SDL_GetTicks();

	double timeCycle = (1.0 / CLOCK_FREQUENCY) * 1000000000; //time of a cyle in nanoseconds

	int performedCycles = 0;

	while (performedCycles < cyclesToDo)
	{
		uint8 cycles = cpu.doCycle();
		performedCycles += cycles;
	}

	ppu.updateScreen();
	fps++;

	double elapsedTime = (SDL_GetTicks() - startTime);

	if (elapsedTime < 16.67)
	{
		SDL_Delay((16.67 - elapsedTime));
	}

	if (SDL_GetTicks() - fpsStartTime >= 1000)
	{
		ppu.displayFramerate(fps);
		fpsStartTime = SDL_GetTicks();
		fps = 0;
	}
}


/*------------------------------------------GETTERS--------------------------------*/

bool GameBoy::getBiosInMemory()
{
	return memory.getBiosInMemeory();
}
