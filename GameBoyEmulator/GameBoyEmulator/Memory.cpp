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

bool Memory::loadRom(const string& romPath)
{
	bool loadRomBool = false;
	std::ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		input.seekg(0, ios::beg);
		for (int i = 0; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
		{
			memoryArray[i] = input.get();
		}
		input.close();
		loadRomBool = true;
	}
	else
	{
		cout << "Can't open file" << endl;
		loadRomBool = false;
	}
	return loadRomBool;
}