#ifndef DEF_GAMEBOY
#define DEF_GAMEBOY

#include "binaryLib/binaryLib.h"

#include "Cpu.h"
#include "Memory.h"
#include "Ppu.h"
#include "Cartridge.h"
#include "Spu.h"
#include "Joypad.h"

#define VER 0.8
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
	~GameBoy();


	SDL_Event event;

	Memory memory;
	Cpu cpu;
	Ppu ppu;
	Joypad joypad;
	Spu spu;
	Cartridge cartridge;

	uint8 fps;
	uint32_t fpsStartTime;
	string gameName;
	string screenshotsFolder = "./screenshots/";

	float volume;
	int currentColorMode = 0;

public:
	static GameBoy* getInstance();
	void reset();
	void setGameBoyWithoutBios();

	void loadBios(const string& biosPath);
	void insertGame(const string& rompath);

	void start();

private:
	/*------------------------------------------Game Boy Cycle--------------------------------*/
	void doGameBoyCycle(const int cyclesNumberToDo);

	// /*------------------------------------Handle Emulator inputs--------------------------------*/
	bool handleInputs();

public:
	/*------------------------------------------Screenshots--------------------------------*/
	string generateScreeShotName(const int& index);

	/*------------------------------------------Save states--------------------------------*/
	void createSaveState();
	void loadSaveState();

	/*------------------------------------------Set volume--------------------------------*/
	void setVolume(const float& volume);
	void incDecVolume(const float& value);

public:
	/*------------------------------------------GETTERS--------------------------------*/
	bool getBiosInMemory();

	/*------------------------------------------SETTERS-------------------------------*/
	void setWidthHeight(const int& width, const int& height);

	void setColorMode(const int& colorModeCode);

	/*------------------------------------------OTHER--------------------------------*/
	string static getDateTime();

	bool static fileExist(const std::string& name);

	string static addLeadingZero(string text, const int& numberOfZero);
};

#endif
