#include <iostream>

#include "GameBoy.h"
#include "Cartridge.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;
	string biosPath;
	string romPath;

	GameBoy* gameBoy = GameBoy::getInstance();//Game Boy creation

	if (true)//Debug
	{
		biosPath = "../../Bios_Games/dmg_boot.bin";
		romPath = "../../Bios_Games/TENNIS.GB";
		argc = 2;
		gameBoy->loadBios(biosPath);
	}

	//if (settings.isBiosPresent())
	//{
	//	gameBoy->loadBios(biosPath);
	//}

	if (argc > 1)//If a game is loaded
	{
		//romPath = argv[1];
		//File name
		Cartridge cartridge(romPath);
		//cartridge.toString();

		gameBoy->insertGame(&cartridge);
		gameBoy->start();
	}
	else if (gameBoy->getBiosInMemory())//If no game but bios is present
	{
		gameBoy->start();
	}
	else
	{
		//Write usage
	}

	return 0;
}