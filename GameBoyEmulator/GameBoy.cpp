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
	if (gameboyInstance == nullptr)
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

	const int cyclesToDo = CLOCK_FREQUENCY / SCREEN_FREQUENCY;//Calcul the number of cycles for the update of the screen

	fpsStartTime = SDL_GetTicks();

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (ppu.windowHandling() && cpu.getPc() < 0x100)//cpu.getPc() < 0x100 && glfwOpenglLib.windowHandling()
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

	ppu.addGameNameWindow(cartridge->getGameName());
	createSaveState();

	while (ppu.windowHandling())// Window is active
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

/*------------------------------------------Save states--------------------------------*/
void GameBoy::createSaveState()
{
	string path=cartridge->getRomPath()+".state.bmp";
	cout << path<<endl;
}

void GameBoy::loadSaveState()
{
	
}

/*------------------------------------------GETTERS--------------------------------*/

bool GameBoy::getBiosInMemory()
{
	return memory.getBiosInMemeory();
}
