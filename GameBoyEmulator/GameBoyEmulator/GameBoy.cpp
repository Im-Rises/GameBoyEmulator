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

	const int cyclesToDo = CLOCK_FREQUENCY / 60;//Calcul the number of cycles for the update of the screen

	if (memory.getBiosInMemeory()) //if there is a bios
	{
		while (cpu.getPc() < 0x100 && glfwOpenglLib.windowIsActive())
		{
			doGameBoyCycle(glfwOpenglLib, cyclesToDo);
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
		doGameBoyCycle(glfwOpenglLib, cyclesToDo);
	}
}


void GameBoy::doGameBoyCycle(GlfwOpenglLib& glfwOpenglLib, const int cyclesToDo)
{
	double timeCycle = (1.0 / CLOCK_FREQUENCY) * 1000000000; //time of a cyle in nanoseconds

	int performedCycles = 0;

	while (performedCycles < cyclesToDo)
	{
		std::chrono::steady_clock::time_point timeCpuStart = std::chrono::high_resolution_clock::now();

		handleInputs(GlfwOpenglLib::gameBoyInputs);
		uint8 cycles = cpu.doCycle();
		performedCycles += cycles;

		while ((std::chrono::high_resolution_clock::now() - timeCpuStart).count() < timeCycle * cycles)
		{
			//Wait
		}
	}

	glfwOpenglLib.getEvenements();
	updateScreen(glfwOpenglLib);
}


/*------------------------------------------INPUTS--------------------------------*/

void GameBoy::handleInputs(const uint8& userInputs)
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

	uint8 memoryInputs = memory.read(0xFF00);

	if (!testBit(memoryInputs, 4))
	{
		memoryInputs &= 0xF0;
		memoryInputs |= (userInputs & 0xF);
		memory.write(0xFF00, memoryInputs);
	}
	else if (!testBit(memoryInputs, 5))
	{
		userInputs >= 4;
		//cout << "test";
		memory.write(0xFF00, 0xFF);
		memoryInputs &= 0xF0;
		memoryInputs |= (userInputs >> 4);
		memory.write(0xFF00, memoryInputs);
	}
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