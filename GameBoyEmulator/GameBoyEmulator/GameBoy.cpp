#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;
uint8 GameBoy::inputs = 0b11111111;
bool GameBoy::pause = false;

GameBoy::GameBoy() : cpu(&memory, &ppu), ppu(&memory)
{
	fullScreen = FULL_SCREEN;
	useSaveFile = USE_SAVE_FILE;
	pause = false;
	fullSpeed = false;
	pixelSize = 2.0f / (float)DOTS_DISPLAY_X;
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
	//Set the background of the two buffers to white
	glfwOpenglLib.setBackground();

	while (glfwOpenglLib.windowIsActive())
	{

		glfwOpenglLib.updateScreen();
		glfwOpenglLib.getEvenements();
	}


	//float timeRefresh = 1.0f / SCREEN_FREQUENCY;
	//int timeRefreshInt = timeRefresh * 1000;
	//auto timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	//auto timeRefresthScreenFinish = std::chrono::high_resolution_clock::now();

	//auto timeCpuStart = std::chrono::high_resolution_clock::now();
	//auto timeCpuFinish = std::chrono::high_resolution_clock::now();

	//double timeCycle = (1.0 / CPU_FREQUENCY_NORMAL_MODE) * 1000000000; //time of a cyle in nanoseconds
	//int cycles = 0;													   //Machine cycle for the precedent operation

	//if (memory.getBiosInMemeory()) //if there is a bios
	//{
	//	//execute bios until its end. Once done replace the memory from 0 to 0x100 by the cartridge
	//	while (cpu.getPc() < 0x100 && !glfwWindowShouldClose(window))
	//	{
	//		//Write inputs to cpu that writes it to memory
	//		timeCpuFinish = std::chrono::high_resolution_clock::now();
	//		if (std::chrono::duration_cast<std::chrono::nanoseconds>(timeCpuFinish - timeCpuStart).count() > (cycles * timeCycle))
	//		{
	//			cpu.writeInputs(inputs);
	//			timeCpuStart = std::chrono::high_resolution_clock::now();
	//			cycles = cpu.doCycle();
	//		}

	//		//Update screen
	//		timeRefresthScreenFinish = std::chrono::high_resolution_clock::now();
	//		if (std::chrono::duration_cast<std::chrono::milliseconds>(timeRefresthScreenFinish - timeRefresthScreenStart).count() > timeRefreshInt)
	//		{
	//			updateScreen();
	//			glfwSwapBuffers(window);
	//			timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	//		}
	//		//Get evenements
	//		glfwPollEvents();
	//	}
	//	memory.loadTempArrayInterruptRst();
	//}
	//else
	//{
	//	cpu.setPc(ROM_DATA_AREA);
	//	cpu.setCpuWithoutBios();
	//	memory.setMemoryWithoutBios();
	//}


	//if (useSaveFile && cpu.getPc() == 0x100) //Once game is launching put save into ram
	//{
	//	loadSaveGame();
	//}

	//while (!glfwWindowShouldClose(window)) //While window not closed
	//{
	//	//Debug
	//	if (true)
	//	{
	//		//if (debug)
	//		//{
	//		//	writeScreenToFile();
	//		//	writeAllTiles();
	//		//	debug = false;
	//		//}

	//		//if (cpu.getPc() >= 0x239)
	//		//	cout << "test" << endl;
	//	}

	//	//Write inputs to cpu that writes it to memory
	//	timeCpuFinish = std::chrono::high_resolution_clock::now();
	//	if (std::chrono::duration_cast<std::chrono::nanoseconds>(timeCpuFinish - timeCpuStart).count() > (cycles * timeCycle))
	//	{
	//		cpu.writeInputs(inputs);
	//		timeCpuStart = std::chrono::high_resolution_clock::now();
	//		cycles = cpu.doCycle();
	//	}

	//	//Update screen
	//	timeRefresthScreenFinish = std::chrono::high_resolution_clock::now();
	//	if (std::chrono::duration_cast<std::chrono::milliseconds>(timeRefresthScreenFinish - timeRefresthScreenStart).count() > timeRefreshInt)
	//	{
	//		updateScreen();
	//		glfwSwapBuffers(window);
	//		timeRefresthScreenStart = std::chrono::high_resolution_clock::now();
	//	}


	//}
}






/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/

void GameBoy::updateScreen()
{
	for (int y = 0; y < DOTS_DISPLAY_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			//glfwOpenglLib.drawRectangle(pixelSize, x, y, ppu.getLcdScreenPixel(x, y));
		}
	}
}

