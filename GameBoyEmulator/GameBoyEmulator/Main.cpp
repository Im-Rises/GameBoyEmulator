#include <iostream>

#include "Cpu.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	string biosPath = "../../Bios_Games/dmg_boot.bin";
	string romPathDebug = "../../Bios_Games/Tetris.GB";
	
	Cpu cpu(biosPath);
	cpu.start();
	
	//cpu.loadRom(romPathDebug);
	//cpu.start();
	
	return 0;
}