#include <iostream>

#include "GameBoy.h"
#include "Cartridge.h"

void writeUsage()
{
	cout << "In console mode you have to add a parameter that correspond to the game path" << endl;
}

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;
	string biosPath;
	string romPath;

	GameBoy* gameBoy = GameBoy::getInstance();//Game Boy creation

	if (true)//Debug
	{
		biosPath = "../../Bios_Games/dmg_boot.bin";
		romPath = "../../Bios_Games/Games/TENNIS.GB";
		//romPath = "../../Bios_Games/cpu_instrs.gb";
		//romPath = "../../Bios_Games/cpu_instrs/individual/";
		argc = 2;
	}


	if (false)//settings.isBiosPresent()
	{
		gameBoy->loadBios(biosPath);
	}

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
		writeUsage();
		gameBoy->start();
	}
	else//Write usage
	{
		writeUsage();
	}

	return 0;
}