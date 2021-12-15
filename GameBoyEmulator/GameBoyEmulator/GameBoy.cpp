#include "GameBoy.h"

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
	memory.loadBiosInMemory(biosPath);
}

void GameBoy::loadGame(const string& gamePath)
{

}

void GameBoy::launch()
{
	while (true)
	{
		//Get inputs and send them to CPU
		//this->setinputes();

		//Read one opcode
		this->cpu.start();

		//Update screen

		//If escape button is pressed leave function
	}
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