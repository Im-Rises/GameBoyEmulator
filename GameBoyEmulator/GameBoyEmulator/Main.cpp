#include <iostream>

#include "Cpu.h"

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	Cpu cpu;
	string romPathDebug = "../../../Tetris.GB";
	cpu.loadRom(romPathDebug);
	cpu.start();

	return 0;
}