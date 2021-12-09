#ifndef DEF_MEMORY
#define DEF_MEMORY 

#include <iostream>
#include <fstream>

#define MEMORY_SIZE (0xFFFF + 0x0001)	//65535 KB

#define INTERRUPT_ADDRESS 0x0
#define ROM_DATA_AREA 0x100
#define USER_PROGRAM_AREA 0x150

#define RAM_CHARACTER_DATA_BANK_0_DMG 0x8000
#define RAM_CHARACTER_DATA_BANK_1_CGB 0x8000
#define RAM_BG_DISPLAY_DATA_1_CGB 0x9800
#define RAM_BG_DISPLAY_DATA_2_CGB 0x9C00

#define EXTERNAL_EXPENSION_RAM_START 0xA000
#define EXTERNAL_EXPENSION_RAM_END 0xBFFF

#define RAM_DMG 0xC000
#define RAM_BANK_0_CGB 0xC000
#define RAM_BANK_1_TO_7_CGB 0xD000

#define PROHIBITED_AREA 0xE000

#define OAM_START 0xFE00
#define OAM_END 0xFEA0

#define RAM_INTERNAL_CPU_START 0xFE00
#define RAM_DISPLAY_DATA_START 0xFE00
#define RAM_DISPLAY_DATA_END 0xFE9F
#define INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START 0xFF00
#define INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_END 0xFF7F
#define INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_OTHER 0x0xFFFF
#define CPU_WORK_RAM_OR_AND_STACK_START 0xFF80
#define CPU_WORK_RAM_OR_AND_STACK_END 0xFFFE
#define RAM_INTERNAL_CPU_END 0xFFFF

#define CONTROL_DATA_AREA 0xFF00


using namespace std;

class Memory {

private:

	uint8_t memoryArray[MEMORY_SIZE];


public:
	Memory();

	uint8_t read(const uint16_t index)const;
	void write(const uint16_t& index, uint8_t value);
	bool loadRom(const string& romPath);
};

#endif
