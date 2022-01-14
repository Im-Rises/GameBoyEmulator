#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>
#include <chrono>
#include <thread>

#include "SdlLib.h"
#include "binaryLib.h"

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "Cartridge.h"
#include "Spu.h"

#define VER 0.6
#define AUTHOR "Im-Rises"
#define PROJECT_NAME "GameBoyEmulator"

#define EMULATOR_SCREEN_SIZE_X 640
#define EMULATOR_SCREEN_SIZE_Y 576

#define SCREEN_FREQUENCY 60	//In fps

/*
* this class is used to made an interface between the CPU and the screen, buttons.
* It represent the game boy itself
*/

class GameBoy
{
private:
	static GameBoy* gameboyInstance;
	GameBoy();
	//~GameBoy();//Put GlfwOpenglLib destructor in here to destroy video if it is memeber of the class


	Memory memory;
	Cpu cpu;
	Ppu ppu;
	//Spu spu;
	//GlfwOpenglLib lcdScreenInputs;
	Cartridge* cartridge = nullptr;

	uint8 fps;
	uint32_t fpsStartTime;

public:
	static GameBoy* getInstance();
	void reset();
	void setGameBoyWithoutBios();

	void loadBios(const string& biosPath);
	void insertGame(Cartridge* cartridge);

	void start();

private:
	/*------------------------------------------Game Boy Cycle--------------------------------*/
	void doGameBoyCycle(SdlLib& glfwOpenglLib, const int cyclesNumberToDo);

	/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/
	void updateScreen(SdlLib& glfwOpenglLib);

public:
	/*------------------------------------------GETTERS--------------------------------*/
	bool getBiosInMemory();
};

#endif