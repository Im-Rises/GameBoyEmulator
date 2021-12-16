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

#define LCD_LY 0xFF44
#define LCD_LCDC 0xFF40

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
