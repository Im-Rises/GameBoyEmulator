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
	GlfwOpenglLib glfwOpenglLib(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME);//Create window
	glfwOpenglLib.setBackground();	//Set the background of the two buffers to white

	const int cyclesNumberToDo = CLOCK_FREQUENCY / 60;//Calcul the number of cycles for the update of the screen

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive())
		{
			doGameBoyCycle(glfwOpenglLib, cyclesNumberToDo);
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



	while (glfwOpenglLib.windowIsActive())//As long as we don't leave program
	{
		doGameBoyCycle(glfwOpenglLib, cyclesNumberToDo);
	}

	/*
		GlfwOpenglLib glfwOpenglLib(EMULATOR_SCREEN_SIZE_X, EMULATOR_SCREEN_SIZE_Y, PROJECT_NAME);//Create window
		glfwOpenglLib.setBackground();	//Set the background of the two buffers to white


		float timeRefresh = 1.0f / SCREEN_FREQUENCY;
		int timeRefreshInt = timeRefresh * 1000;
		std::chrono::steady_clock::time_point timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
		std::chrono::steady_clock::time_point timeCpuStart = std::chrono::high_resolution_clock::now();
		double timeCycle = (1.0 / CPU_FREQUENCY_NORMAL_MODE) * 1000000000; //time of a cyle in nanoseconds
		int cycles = 0;													   //Machine cycle for the precedent operation

	*/
}


void GameBoy::doGameBoyCycle(GlfwOpenglLib& glfwOpenglLib, const int cyclesNumberToDo)
{
	int performedCycles = 0;

	while (performedCycles < cyclesNumberToDo)
	{
		//get user inputs from the doCycle function or a separate function ?

		performedCycles += cpu.doCycle();
	}
	glfwOpenglLib.getEvenements();

	updateScreen(glfwOpenglLib);
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


/*------------------------------------------GETTERS--------------------------------*/

bool GameBoy::getBiosInMemory()
{
	return memory.getBiosInMemeory();
}