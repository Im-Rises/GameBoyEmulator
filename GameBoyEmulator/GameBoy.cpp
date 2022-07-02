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
	// spu.reset();
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
	SdlLib sdlLib(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, DOTS_DISPLAY_X, DOTS_DISPLAY_Y, PROJECT_NAME);//Create window

	const int cyclesToDo = CLOCK_FREQUENCY / 60;//Calcul the number of cycles for the update of the screen

	fpsStartTime = sdlLib.getTicks();

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (sdlLib.readEmulatorInputs() && cpu.getPc() < 0x100)//cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive()
		{
			doGameBoyCycle(sdlLib, cyclesToDo);
		}

		//Load temporary array in memory
		memory.loadRomBeginning();
	}
	else
	{
		//Set emulator without bios
		this->setGameBoyWithoutBios();
	}


	bool useSaveFile = false;
	if (useSaveFile && cpu.getPc() == 0x100) //Once game is launching put save into ram
	{
		//loadSaveGame();
	}


	while (sdlLib.readEmulatorInputs())//sdlLib.windowIsActive()
	{
		doGameBoyCycle(sdlLib, cyclesToDo);
	}
}


void GameBoy::doGameBoyCycle(SdlLib& sdlLib, const int cyclesToDo)
{
	uint32_t startTime = sdlLib.getTicks();

	double timeCycle = (1.0 / CLOCK_FREQUENCY) * 1000000000; //time of a cyle in nanoseconds

	int performedCycles = 0;

	while (performedCycles < cyclesToDo)
	{
		uint8 cycles = cpu.doCycle();
		performedCycles += cycles;
	}

	updateScreen(sdlLib);
	sdlLib.renderPresent();
	fps++;

	double elapsedTime = (sdlLib.getTicks() - startTime);

	if (elapsedTime < 16.67)
	{
		SDL_Delay((16.67 - elapsedTime));
	}

	if (sdlLib.getTicks() - fpsStartTime >= 1000)
	{
		//cout << (int)fps << endl;
		sdlLib.setFps(fps);
		fpsStartTime = sdlLib.getTicks();
		fps = 0;
	}
}

/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/

void GameBoy::updateScreen(SdlLib& sdlLib)
{
	for (int y = 0; y < DOTS_DISPLAY_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			sdlLib.drawSquare(x, y, ppu.getLcdScreenPixel(x, y));
		}
	}
}


/*------------------------------------------GETTERS--------------------------------*/

bool GameBoy::getBiosInMemory()
{
	return memory.getBiosInMemeory();
}