#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "GLFW/include/glfw3.h"

//Made a singleton of this class
//Here get inputs and start cycle of cpu

//this class is used to made an interface between the CPU and the screen, buttons.

class GameBoy
{
private:
	//static GameBoy* gameboy = nullptr;

	Cpu cpu;
	Memory memory;
	
public:
	GameBoy();
	void reset();
	void loadBios(const string& biosPath);
	void loadGame(const string& gamePath);
	void start();
	void updateScreen();
};

#endif