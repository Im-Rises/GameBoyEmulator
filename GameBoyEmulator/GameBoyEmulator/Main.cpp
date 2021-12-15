#include <iostream>

#include "GameBoy.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	string biosPath;
	string romPath;

	if (true)//Debug
	{
		biosPath = "../../Bios_Games/dmg_boot.bin";
		romPath = "../../Bios_Games/Tetris.GB";
		argc = 2;
	}

	if (argc > 1)
	{
		//romPath = argv[1];
		GameBoy gameBoy;

		if (true)
		{
			gameBoy.loadBios(biosPath);
		}

		gameBoy.start();
	}

	return 0;
}