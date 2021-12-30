#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include <iostream>
#include <chrono>
#include <fstream>

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"

#include "settings.h"
#include "binaryLib.h"
#include "GlfwOpenglLib.h"

#define VER 0.1
#define AUTHOR "Im-Rises"
#define PROJECT_NAME "GameBoyEmulator"

#define EMULATOR_SCREEN_SIZE_X 640
#define EMULATOR_SCREEN_SIZE_Y 576
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
	static uint8 inputs;			//Game Boy inputs (Buttons)
	bool fullScreen;
	bool useSaveFile;
	bool fullSpeed;
	float pixelSize;

public:
	static GameBoy* getInstance();
	void reset();

	void loadBios(const string& biosPath);
	void loadGame(const string& gamePath);

	void launch();


private:
	/*------------------------------------------INIT WITHOUT BIOS--------------------------------*/
	void setGameBoyWithoutBios();

	/*------------------------------------------SCREEN FUNCTIONS--------------------------------*/

	uint8 colorToRGB(uint8 colorGameBoy);

};

#endif