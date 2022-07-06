#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include "binaryLib.h"

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "Cartridge.h"
#include "Spu.h"
#include "Joypad.h"

#define VER 0.6
#define AUTHOR "Im-Rises"
#define PROJECT_NAME "GameBoyEmulator"

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

	Memory memory;
	Cpu cpu;
	Ppu ppu;
	Joypad joypad;
	Spu spu;
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
	void doGameBoyCycle(const int cyclesNumberToDo);

	// /*------------------------------------------Screen functions--------------------------------*/
	// void updateScreen();

public:
	/*------------------------------------------Save states--------------------------------*/
	void createSaveState();
	void loadSaveState();

public:
	/*------------------------------------------GETTERS--------------------------------*/
	bool getBiosInMemory();
};

#endif
