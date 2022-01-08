#ifndef DEF_MEMORY
#define DEF_MEMORY 

#include <iostream>
#include <fstream>

#include "binaryLib.h"

#include "Cartridge.h"

#define MEMORY_SIZE (0xFFFF + 0x0001)	//65535 KB
#define ROM_DATA_AREA 0x100
#define RAM_CHARACTER_DATA_BANK_0_DMG 0x8000
#define INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START 0xFF00
#define CPU_WORK_RAM_OR_AND_STACK_END 0xFFFE


#define INTERRUPT_FLAG_IF_ADDRESS 0xFF0F
#define INTERRUPT_FLAG_IE_ADDRESS 0xFFFF


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

#define ETERNAL_EXPANSION_WORKING_RAM 0xA000

#define STAT_ADDRESS 0xFF41
#define BG_PALETTE_DATA 0xFF47
#define WX_ADDRESS 0xFF4B
#define WY_ADDRESS 0xFF4A

#define OAM_Y_COODINATE 0xFE00
#define OAM_X_COODINATE 0xFE01
#define OAM_CHR_CODE 0xFE02
#define OAM_ATTRIBUTE_FLAG 0xFE03

#define OPB0_PALETTE_DATA 0xFF48
#define OPB1_PALETTE_DATA 0xFF49

#define DMA_ADDRESS 0xFF46


using namespace std;

class Memory {

private:
	uint8 memoryArray[MEMORY_SIZE];
	bool biosInMemory;
	bool gameInMemory;
	Cartridge* cartridge = nullptr;

public:
	Memory();
	void reset();

	bool loadBiosInMemory(const string& biosPath);

	void connectCartridge(Cartridge* cartridge);

	void loadRomInMemory();
	void loadRomBeginning();
	void setMemoryWithoutBios();

	//Read and write to cartridge or memory
	uint8 read(const uint16 address)const;
	void write(const uint16& address, const uint8 value);
	uint8 directRead(const uint16& address)const;
	void directWrite(const uint16& address, const uint8& value);

	//void increment(const uint16& address);
	//void decrement(const uint16& address);






	void setResetBitMemory(const uint16& address, const bool bit, const int bitIndex);

	bool getBiosInMemeory();

};

#endif
