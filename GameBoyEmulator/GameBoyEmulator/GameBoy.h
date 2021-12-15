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
	GameBoy();
	static GameBoy* gameboyInstance;

	Cpu cpu;
	Memory memory;

public:
	static GameBoy* getInstance();
	void reset();

	void loadBios(const string& biosPath);
	void loadGame(const string& gamePath);

	void launch();

	void updateScreen();
};

#endif