#ifndef DEF_MEMORY
#define DEF_MEMORY 

#include <iostream>
#include <fstream>

#define MEMORY_SIZE (0xFFFF + 0x0001)	//65535 KB
#define ROM_DATA_AREA 0x100
#define RAM_CHARACTER_DATA_BANK_0_DMG 0x8000
#define INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START 0xFF00
#define CPU_WORK_RAM_OR_AND_STACK_END 0xFFFE

#define CONTROLLER_DATA_ADDRESS 0xFF00

#define DIVIDER_REGISTER_ADDRESS 0xFF04

#define TIMER_REGISTER_TIMA_ADDRESS 0xFF05
#define TIMER_REGISTER_TMA_ADDRESS 0xFF06
#define TIMER_REGISTER_TAC_ADDRESS 0xFF07

#define INTERRUPT_FLAG_IF_ADDRESS 0xFF0F
#define INTERRUPT_FLAG_IE_ADDRESS 0xFFFF


//Screen and PPU memory registers
#define CHARACTER_DATA 0x8000

#define BG_CHARACTER_DATA_SELECTION_0 0x8800
#define BG_CHARACTER_DATA_SELECTION_1 0x8000

#define BG_DISPLAY_DATA_1 0x9800
#define BG_DISPLAY_DATA_2 0x9C00

#define LCDC_ADDRESS 0xFF40
#define STAT_ADDRESS 0xFF41
#define SCY_ADDRESS 0xFF42
#define SCX_ADDRESS 0xFF43
#define LY_ADDRESS 0xFF44
#define LYC_ADDRESS 0xFF45

#define VBK_ADDRESS 0xFF4F

#define DOTS_NUMBER 1024

#define WINDOW_CODE_AREA_SELECTION_0 0x9800
#define WINDOW_CODE_AREA_SELECTION_1 0X9C00

#define WX_ADDRESS 0xFF4A
#define WY_ADDRESS 0xFF4B

using namespace std;

class Memory {

private:
	bool biosInMemory;
	uint8_t memoryArray[MEMORY_SIZE];
	//uint8_t memoryBios[0x100];

public:
	Memory();
	void reset();
	uint8_t read(const uint16_t index)const;
	void write(const uint16_t& index, uint8_t value);
	void increment(const uint16_t& index);
	void decrement(const uint16_t& index);
	bool loadBiosInMemory(const string& biosPath);
	bool loadRomInMemory(const string& romPath);
	bool getBiosInMemeory();
};

#endif
