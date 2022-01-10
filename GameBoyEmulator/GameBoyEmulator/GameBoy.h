#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>
#include <chrono>
#include <thread>

//#include "debug.h"
//#include "settings.h"
#include "binaryLib.h"
//#include "GlfwOpenglLib.h"
#include "SdlLib.h"

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "Cartridge.h"

#define VER 0.5
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
	~GameBoy();//Put GlfwOpenglLib destructor in here to destroy video if it is memeber of the class

	Cpu cpu;
	Ppu ppu;
	Memory memory;
	//GlfwOpenglLib lcdScreenInputs;
	Cartridge* cartridge = nullptr;

public:
	static GameBoy* getInstance();
	void reset();
	void setGameBoyWithoutBios();

	void loadBios(const string& biosPath);
	void insertGame(Cartridge* cartridge);

	void start();

private:
	void doGameBoyCycle(SdlLib& glfwOpenglLib, const int cyclesNumberToDo);

	/*------------------------------------------INPUTS--------------------------------*/
	void handleInputs(const uint8& userInputs);

	/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/
	void updateScreen(SdlLib& glfwOpenglLib);

public:
	/*------------------------------------------GETTERS--------------------------------*/
	bool getBiosInMemory();
};

#endif