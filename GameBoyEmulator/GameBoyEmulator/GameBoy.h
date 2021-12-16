#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>
#include <chrono>

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "GLFW/include/glfw3.h"
//#include "glew/include/GL/glew.h"

#define VER 0.1
#define AUTHOR "Im-Rises"
#define PROJECT_NAME "GameBoyEmulator"

//Here get inputs and start cycle of cpu

//this class is used to made an interface between the CPU and the screen, buttons.

class GameBoy
{
private:
	static GameBoy* gameboyInstance;
	GameBoy();

	//bool onOff;					//On off button state (1:ON, 2:OFF)
	Cpu cpu;
	Memory memory;

public:
	static GameBoy* getInstance();
	void reset();

	void loadBios(const string& biosPath);
	void loadGame(const string& gamePath);
	void launch();

private:
	void updateScreen();

	/*------------------------------------------GLFW FUNCTIONS--------------------------------*/

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

#endif