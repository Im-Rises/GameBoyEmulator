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
		//memory.loadRomInMemoryPartially();
	}
	else//If there's no bios
	{
		memory.loadRomInMemory(gamePath);

		//Set memory and CPU like after bios
	}
}

void GameBoy::launch()
{
	//if (!glfwInit())
	//{
	//	cout << "Initialization failed" << endl;
	//	exit(1);
	//}
	//GLFWwindow* window = glfwCreateWindow(640, 480, PROJECT_NAME, NULL, NULL);
	//if (!window)
	//{
	//	cout << "Window or OpenGL context creation failed" << endl;
	//}
	//glfwMakeContextCurrent(window);
	//gladLoadGL(glfwGetProcAddress);

	while (true)
	{
		//Get inputs and send them to CPU
		readInputs();
		//this->setinputes();

		//Read one opcode
		this->cpu.start();

		//Update screen
		updateScreen();
		//If escape button is pressed leave function
	}

	glfwTerminate();
}

void GameBoy::readInputs()
{

}

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