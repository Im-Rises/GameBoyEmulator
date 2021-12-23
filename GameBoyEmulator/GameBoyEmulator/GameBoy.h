#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>
#include <chrono>
#include <fstream>

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"

#include "glew/include/GL/glew.h"
#include "GLFW/include/glfw3.h"

#define VER 0.1
#define AUTHOR "Im-Rises"
#define PROJECT_NAME "GameBoyEmulator"

#define EMULATOR_SCREEN_SIZE_X 1600
#define EMULATOR_SCREEN_SIZE_Y 1440

#define SCREEN_RESOLUTION_X 160
#define SCREEN_RESOLUTION_Y 144

//Screen dimensions 4.4 x 4 cm

#define SCREEN_FREQUENCY 59.7	//In fps

/*
* this class is used to made an interface between the CPU and the screen, buttons.
* It represent the game boy itself
*/

class GameBoy
{
private:
	static GameBoy* gameboyInstance;
	GameBoy();

	//bool onOff;					//On off button state (1:ON, 2:OFF)
	Cpu cpu;
	Ppu ppu;
	Memory memory;

	static bool pause;				//Emulator in pause
	static uint8_t inputs;			//Game Boy inputs (Buttons)

public:
	static GameBoy* getInstance();
	void reset();

	void loadBios(const string& biosPath);
	void loadGame(const string& gamePath);
	void launch();

private:
	void updateScreen();
	uint8_t colorToRGB(uint8_t colorGameBoy);

	/*------------------------------------------GLFW FUNCTIONS--------------------------------*/

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	/*------------------------------------------OPENGL FUNCTIONS--------------------------------*/

	void RenderGame();


	/*------------------------------------------DEBUG--------------------------------*/

	void writeScreenToFile();
	static bool debug;
};

#endif