#include "GameBoy.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// #include <format> // Issue with Unix system, using my functions to format string for screesnshots name

GameBoy* GameBoy::gameboyInstance = 0;

GameBoy::GameBoy() : memory(&joypad, &spu), cpu(&memory, &ppu, &spu), ppu(&memory), spu(&memory)
{
	volume = spu.getVolume();
	fps = 0;
	fpsStartTime = 0;

	// Deactivate the controller reading while pooling events to prevent program from queuing to many inputs from controller's axis resulting in blocking the app from exiting
	// https://wiki.libsdl.org/SDL_EventState
	// Or not working so writing one line for one deactivation
	SDL_EventState(SDL_JOYAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBALLMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYHATMOTION, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_JOYBUTTONUP, SDL_IGNORE);

	SDL_EventState(SDL_CONTROLLERAXISMOTION, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONDOWN, SDL_IGNORE);
	SDL_EventState(SDL_CONTROLLERBUTTONUP, SDL_IGNORE);

	SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

	// srand(time(NULL));
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
	memory.reset();
	cpu.reset();
	ppu.reset();
	spu.reset();
	cartridge->reset();
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
	if (cartridge == nullptr)
	{
		cerr << "Error: Cartridge is empty, the path may be wrong." << endl;
		exit(1);
	}

	this->cartridge = cartridge;
	memory.connectCartridge(cartridge);
}

void GameBoy::start()
{
	ppu.powerOnScreen();

	//Calcul the number of cycles for the update of the screen
	const int cyclesToDo = CLOCK_FREQUENCY / SCREEN_FREQUENCY;

	fpsStartTime = SDL_GetTicks();

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (handleInputs() && cpu.getPc() < 0x100) //cpu.getPc() < 0x100 && glfwOpenglLib.windowHandling()
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

	gameName = cartridge->getGameName();

	std::filesystem::create_directories(screenshotsFolder + gameName + "/");

	ppu.addGameNameWindow(gameName);

	while (handleInputs()) // Window is active
	{
		doGameBoyCycle(cyclesToDo);
	}

	cout << "Stoping Emulation please wait..." << endl;
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
		ppu.updateFramerate(fps);
		fpsStartTime = SDL_GetTicks();
		fps = 0;
	}
}

bool GameBoy::handleInputs()
{
	static bool switchColorMode = false;
	static bool switchWindowMode = false;
	static bool switchPause = false;
	static bool switchScreenshot = false;
	static bool switchVolumePlus = false;
	static bool switchVolumeMinus = false;
	static bool switchSaveState = false;
	static bool switchReset = false;

	SDL_PollEvent(&event);

	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_F11)
			switchWindowMode = true;

		if (event.key.keysym.sym == SDLK_F10)
			switchColorMode = true;

		if (event.key.keysym.sym == SDLK_p)
			switchPause = true;

		if (event.key.keysym.sym == SDLK_u)
			switchVolumePlus = true;

		if (event.key.keysym.sym == SDLK_j)
			switchVolumeMinus = true;

		if (event.key.keysym.sym == SDLK_PRINTSCREEN)
			switchScreenshot = true;

		if (event.key.keysym.sym == SDLK_b)
			switchSaveState = true;

		if (event.key.keysym.sym == SDLK_TAB)
			switchReset = true;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_F11 && switchWindowMode)
		{
			switchWindowMode = false;
			ppu.toggleFullScreen();
		}

		if (event.key.keysym.sym == SDLK_F10 && switchColorMode)
		{
			switchColorMode = false;
			ppu.setGameBoyColorMode(currentColorMode);
			currentColorMode++;
			if (currentColorMode > sizeof(ColorMode))
				currentColorMode = 0;
		}

		if (event.key.keysym.sym == SDLK_p && switchPause)
		{
			do
			{
				SDL_WaitEvent(&event);
				string message;
				switch (event.key.keysym.sym)
				{
				case(SDLK_p):
					switchPause = false;
					break;
				case(SDLK_ESCAPE):
					return false;
				}

				if (event.type == SDL_QUIT)
					return false;
			}
			while (switchPause);
		}

		if (event.key.keysym.sym == SDLK_u && switchVolumePlus)
		{
			switchVolumePlus = false;
			incDecVolume(0.05f);
		}

		if (event.key.keysym.sym == SDLK_j && switchVolumeMinus)
		{
			switchVolumeMinus = false;
			incDecVolume(-0.05f);
		}

		if (event.key.keysym.sym == SDLK_PRINTSCREEN && switchScreenshot)
		{
			switchScreenshot = false;

			int index = 0;
			string screenshotPath = generateScreeShotName(index);

			while (fileExist(screenshotPath))
			{
				index++;
				screenshotPath = generateScreeShotName(index);
			}

			ppu.doScreenshot(screenshotPath);
		}

		if (event.key.keysym.sym == SDLK_b && switchSaveState)
		{
			switchSaveState = false;
			createSaveState();
		}

		if (event.key.keysym.sym == SDLK_TAB && switchReset)
		{
			switchReset = false;
			reset();
		}

		return !(event.key.keysym.sym == SDLK_ESCAPE);
	}

	return !(event.type == SDL_QUIT);
}

string GameBoy::generateScreeShotName(const int& index)
{
	string indexS = to_string(index);
	indexS = addLeadingZero(indexS, 2);
	return screenshotsFolder + gameName + "/" + gameName + " " + getDateTime() + "-(" + indexS
		+ ')' + ".bmp";
}


/*------------------------------------------Save states--------------------------------*/
void GameBoy::createSaveState()
{
	string path = cartridge->getRomPath() + ".state.bmp";
	// cout << path << endl;

	ppu.doScreenshot(path);

	ofstream saveState;
	saveState.open(path, std::ios_base::app | std::ios_base::binary | std::ios_base::out | std::ios_base::ate);

	if (saveState)
	{
		// cpu.dump();
		// spu.dump();
		// ppu.dump();
		// cartridge->dump();
		// mmu.dump();
		saveState << "Dump data here";
	}
	else
		cerr << "Error: Writing data to savestate" << endl;

	saveState.close();
}

void GameBoy::loadSaveState()
{
}


void GameBoy::setVolume(const float& volume)
{
	spu.setVolume(volume);
}

void GameBoy::incDecVolume(const float& value)
{
	spu.setVolume(spu.getVolume() + value);
	volume = spu.getVolume();
	// cout << "Volume value: " << volume << endl;
}

/*------------------------------------------GETTERS--------------------------------*/

bool GameBoy::getBiosInMemory()
{
	return memory.getBiosInMemeory();
}


/*------------------------------------------SETTERS-------------------------------*/

void GameBoy::setWidthHeight(const int& width, const int& height)
{
	ppu.setWidthHeight(width, height);
}

void GameBoy::setColorMode(const int& colorModeCode)
{
	ppu.setGameBoyColorMode(colorModeCode);
}


/*------------------------------------------OTHER--------------------------------*/

string GameBoy::getDateTime()
{
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	return to_string(now->tm_year + 1900) + '-' + addLeadingZero(to_string(now->tm_mon + 1), 2) + '-' +
		addLeadingZero(to_string(now->tm_mday), 2) + '-' + addLeadingZero(to_string(now->tm_hour), 2) + '-' +
		addLeadingZero(to_string(now->tm_sec), 2);
}

bool GameBoy::fileExist(const std::string& name)
{
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

string GameBoy::addLeadingZero(string text, const int& numberOfZero)
{
	// string result = text;
	// int stringSize = text.size();
	// for (int i = 0; i < (numberOfZero - stringSize); i++)
	// 	result = "0" + result;
	// return result;

	return std::string(numberOfZero - std::min(numberOfZero, static_cast<int>(text.length())), '0') + text;
}
