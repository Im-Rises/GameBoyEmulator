#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;

GameBoy::GameBoy() : cpu(&memory, &ppu), ppu(&memory)
{

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
}

void GameBoy::setGameBoyWithoutBios()
{
	cpu.setCpuWithoutBios();
	memory.setMemoryWithoutBios();
}



void GameBoy::loadBios(const string& biosPath)
{
	if (memory.loadBiosInMemory(biosPath) == false)
		exit(1);
}

void GameBoy::loadGame(const string& gamePath)
{
	if (memory.getBiosInMemeory()) //If there is a bios
	{
		memory.loadRomInMemory(gamePath);
	}
	else //If there's no bios
	{
		memory.loadRomInMemory(gamePath);
		setGameBoyWithoutBios();
	}
}

void GameBoy::launch()
{
	GlfwOpenglLib glfwOpenglLib(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME);//Create window
	glfwOpenglLib.setBackground();	//Set the background of the two buffers to white


	float timeRefresh = 1.0f / SCREEN_FREQUENCY;
	int timeRefreshInt = timeRefresh * 1000;
	std::chrono::steady_clock::time_point timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	std::chrono::steady_clock::time_point timeCpuStart = std::chrono::high_resolution_clock::now();
	double timeCycle = (1.0 / CPU_FREQUENCY_NORMAL_MODE) * 1000000000; //time of a cyle in nanoseconds
	int cycles = 0;													   //Machine cycle for the precedent operation


	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive())
		{
			doGameBoyCycle(glfwOpenglLib, timeRefresthScreenStart, timeCpuStart, timeRefreshInt, timeCycle, cycles);
		}

		//Load temporary array in memory
		memory.loadTempArrayInterruptRst();
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

	while (glfwOpenglLib.windowIsActive())//Play game
	{
		doGameBoyCycle(glfwOpenglLib, timeRefresthScreenStart, timeCpuStart, timeRefreshInt, timeCycle, cycles);
	}
}


/*------------------------------------------GAME BOY CYCLE--------------------------------*/

void GameBoy::doGameBoyCycle(GlfwOpenglLib& glfwOpenglLib, std::chrono::steady_clock::time_point& timeRefresthScreenStart, std::chrono::steady_clock::time_point& timeCpuStart, int& timeRefreshInt, double& timeCycle, int& cycles)
{
	//Write inputs to cpu that writes it to memory
	if (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - timeCpuStart).count() > (cycles * timeCycle))
	{
		//cpu.writeInputs(inputs);
		timeCpuStart = std::chrono::high_resolution_clock::now();
		cycles = cpu.doCycle();
	}

	//Update screen
	if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timeRefresthScreenStart).count() > timeRefreshInt)
	{
		updateScreen(glfwOpenglLib);
		timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	}
	//Get evenements
	glfwOpenglLib.getEvenements();
}


/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/

void GameBoy::updateScreen(GlfwOpenglLib& glfwOpenglLib)
{
	float pixelSize = 2.0f / (float)DOTS_DISPLAY_X;

	for (int y = 0; y < DOTS_DISPLAY_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			glfwOpenglLib.drawRectangle(pixelSize, x, y, ppu.getLcdScreenPixel(x, y));
		}
	}
	glfwOpenglLib.swapBuffers();
}

