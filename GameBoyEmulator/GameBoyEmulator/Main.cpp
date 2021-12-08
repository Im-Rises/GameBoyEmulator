#include <iostream>

#include "Cpu.h"

/*
* To do:
* - Implements the PPU
* - Verify all opcodes
* - Change object Memory in class Cpu to a pointer
* 
*/

int main(int argc, char* argv[])
{
	std::cout << "Nintendo GameBoy Emulator" << std::endl;

	Cpu cpu;
	string romPathDebug = "../../../Tetris.GB";
	cpu.loadRom(romPathDebug);
	cpu.start();

	return 0;
}