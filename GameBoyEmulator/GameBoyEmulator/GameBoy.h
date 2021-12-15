#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"

class GameBoy
{
private:
	Memory memory;
	Cpu cpu;
	Ppu ppu;
	
public:
	GameBoy();
	void loadBios(const string biosPath);
	void start();
};

#endif