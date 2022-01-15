#include <iostream>

#include "Cartridge.h"
#include "GameBoy.h"

void writeUsage(const char* appName)
{
	cout << appName << " <gamePath>" << endl;

	cout << PROJECT_NAME << " " << VER << " " << AUTHOR << endl;

	cout << "Game Boy emulator" << endl;
}

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;
	string biosPath;
	string romPath;

	GameBoy* gameBoy = GameBoy::getInstance();//Game Boy creation

	if (true)//Debug
	{
		biosPath = "../../Bios_Games/Bios/dmg_boot.bin";
		//romPath = "../../Bios_Games/cpu_instrs/individual/03-op sp,hl.gb";
		romPath = "../../Bios_Games/Games/Kirby's dream land.gb";
		//romPath = "../../Bios_Games/Games/MarioLand2.gb";
		//romPath = "../../Bios_Games/Games/bgbtest.gb";
		//romPath = "../../Bios_Games/Games/Gremlins 2.gb";
		//romPath = "../../Bios_Games/Games/tetris.gb";
		//romPath = "../../Bios_Games/Games/tennis.gb";
		//romPath = "../../Bios_Games/Games/Zelda Link's Awakening.gb";
		//romPath = "../../Bios_Games/Games/Tennis.gb";
		//romPath = "../../Bios_Games/Games/Pokemon - Version Bleue (F) [S].gb";	


		//Failed:
		//romPath = "../../Bios_Games/dmg-acid2.gb";
		//romPath = "../../Bios_Games/window_y_trigger.gb";

		//Passed:
		//romPath = "../../Bios_Games/cpu_instrs/cpu_instrs.gb";
		//romPath = "../../Bios_Games/instr_timing/instr_timing.gb";
		//romPath = "../../Bios_Games/mem_timing-2/mem_timing.gb";
		argc = 2;
	}


	if (false)//settings.isBiosPresent()
	{
		gameBoy->loadBios(biosPath);
	}

	if (argc > 1)//If a game is loaded
	{
		//romPath = argv[1];
		Cartridge cartridge(romPath);
		cout << cartridge.toString() << endl;

		gameBoy->insertGame(&cartridge);
		gameBoy->start();
	}
	else if (gameBoy->getBiosInMemory())//If no game but bios is present
	{
		writeUsage(argv[0]);
		gameBoy->start();
	}
	else//Write usage
	{
		writeUsage(argv[0]);
	}

	return 0;
}