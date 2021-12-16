#include "GameBoy.h"

GameBoy* GameBoy::gameboyInstance = 0;

GameBoy::GameBoy() :cpu(&memory)
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
}

void GameBoy::loadBios(const string& biosPath)
{
	if (memory.loadBiosInMemory(biosPath) == false)
		exit(1);
}

void GameBoy::loadGame(const string& gamePath)
{
	if (memory.getBiosInMemeory())//If there is a bios
	{

	}
	else//If there's no bios
	{
		memory.loadRomInMemory(gamePath);
		//Set memory and CPU like after bios
	}
}

void GameBoy::launch()
{
	////Wait the number of cycles
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
	//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

	while (true)
	{
		//Get inputs and send them to CPU
		//this->setinputes();

		//if (readInputs(window))
		//	onOff = 0;

		//Read one opcode
		this->cpu.doCycle();

		//Update screen
		updateScreen();
		//If escape button is pressed leave function
	}
}

//bool GameBoy::readInputs(GLFWwindow* window)
//{
//	int state = glfwGetKey(window, GLFW_KEY_ESCAPE);
//	if (state == GLFW_PRESS)
//	{
//		return true;
//	}
//	return false;
//}

void GameBoy::updateScreen()
{
	for (int y = 0; y < DOTS_NUMBER_Y; y++)
	{
		for (int x = 0; x < DOTS_DISPLAY_X; x++)
		{
			//Get memory data
			//memory.read
		}
	}
}