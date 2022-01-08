#include <iostream>

#include "GameBoy.h"
#include "Cartridge.h"

void writeUsage(const char* appName)
{
	cout << appName << " <gamePath>" << endl;

	cout << PROJECT_NAME << " " << VER << " " << AUTHOR << endl;

	cout << "Game Boy emulator" << endl;
}

int main(int argc, char* argv[])
{
	try {

		std::cout << "Nintendo GameBoy Emulator" << std::endl;
		string biosPath;
		string romPath;

		GameBoy* gameBoy = GameBoy::getInstance();//Game Boy creation

		if (false)//Debug
		{
			//biosPath = "../../Bios_Games/Bios/dmg_boot.bin";
			//romPath = "../../Bios_Games/cpu_instrs/individual/03-op sp,hl.gb";
			//romPath = "../../Bios_Games/Games/Kirby's dream land.gb";
			//romPath = "../../Bios_Games/Games/bgbtest.gb";
			//romPath = "../../Bios_Games/Games/Gremlins 2.gb";
			//romPath = "../../Bios_Games/Games/Tetris.gb";
			//romPath = "../../Bios_Games/Games/Zelda Link's Awakening.gb";
			//romPath = "../../Bios_Games/cpu_instrs/cpu_instrs.gb";
			//romPath = "../../Bios_Games/halt_bug.gb";
			//romPath = "../../Bios_Games/instr_timing/instr_timing.gb";
			//argc = 2;
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

	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}
	return 0;
}