#include <iostream>

#include "Cpu.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	string biosPath = "../../../dmg_boot.bin";
	string romPathDebug = "../../../Tetris.GB";
	
	Cpu cpu(biosPath);
	
	cpu.loadRom(romPathDebug);
	cpu.start();

	return 0;
}