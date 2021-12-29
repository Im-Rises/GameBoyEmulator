#include "Memory.h"

Memory::Memory()
{
	reset();
}

void Memory::reset()
{
	biosInMemory = false;
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memoryArray[i] = 0;
	}

	//For bootrom black square
	for (int i = 0x100; i < 0x150; i++)
	{
		memoryArray[i] = 0xFF;
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


void Memory::increment(const uint16_t& index)
{
	memoryArray[index]++;
}

void Memory::decrement(const uint16_t& index)
{
	memoryArray[index]--;
}

bool Memory::loadBiosInMemory(const string& biosPath)
{
	std::ifstream input(biosPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::beg);
		for (int i = 0; i < ROM_DATA_AREA; i++)
		{
			memoryArray[i] = input.get();
		}
		input.close();
		biosInMemory = true;
		return true;
	}
	else
	{
		cout << "Can't open bios file" << endl;
		return false;
	}
}

bool Memory::loadRomInMemory(const string& romPath,const int index)
{
	std::ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		//input.seekg(0, ios::beg);
		input.seekg(index);
		for (int i = index; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
		{
			memoryArray[i] = input.get();
		}
		input.close();
		return true;
	}
	else
	{
		cout << "Can't open rom file" << endl;
		return false;
	}
}

bool Memory::getBiosInMemeory()
{
	return biosInMemory;
}

void Memory::setResetBitMemory(const uint16_t& address, const bool value, const int index)
{
	
	//memoryArray[address]
}