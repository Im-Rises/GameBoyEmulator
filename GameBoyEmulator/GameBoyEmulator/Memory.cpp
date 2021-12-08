#include "Memory.h"

Memory::Memory()
{
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memoryArray[i] = 0;
	}
}

uint8_t Memory::read(const uint16_t index)const
{
	return memoryArray[index];
}

void Memory::write(const uint16_t& index, uint8_t value)
{
	memoryArray[index] = value;
}

void Memory::loadRom(const string& romPath)
{
	std::ifstream input(romPath, std::ios::binary);
	input.seekg(0, ios::end);
	int romSize = input.tellg();
	input.seekg(0, ios::beg);
	for (int i = (0 + USER_PROGRAM_AREA); (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
	{
		memoryArray[i] = input.get();
	}
	input.close();
}