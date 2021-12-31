#include "Memory.h"

Memory::Memory()
{
	reset();
}

void Memory::reset()
{
	biosInMemory = false;
	//Reset all the memory
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



uint8 Memory::read(const uint16 index)const
{
	return memoryArray[index];
}

void Memory::write(const uint16& index, uint8 value)
{
	//if (index == 0x8030)
	//	cout << "error" << endl;
	memoryArray[index] = value;
}



void Memory::increment(const uint16& index)
{
	memoryArray[index]++;
}

void Memory::decrement(const uint16& index)
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

bool Memory::loadRomInMemory(const string& romPath)
{
	std::ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		input.seekg(0, ios::beg);

		if (biosInMemory)
		{
			for (int i = 0; i < 0x100; i++)//Load RST and interrupt address in a temporary array
			{
				memoryTempInterruptRst[i] = input.get();
			}
			for (int i = 0x100; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
			{
				memoryArray[i] = input.get();
			}
		}
		else
		{
			for (int i = 0; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
			{
				memoryArray[i] = input.get();
			}
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

void Memory::loadTempArrayInterruptRst()
{
	for (int i = 0; i < 0x100; i++)
	{
		memoryArray[i] = memoryTempInterruptRst[i];
	}
}



void Memory::setResetBitMemory(const uint16& address, const bool bit, const int bitIndex)
{
	if (bit)
		memoryArray[address] = setBit(memoryArray[address], bitIndex);
	else
		memoryArray[address] = resetBit(memoryArray[address], bitIndex);
}

void Memory::setMemoryWithoutBios()
{

}



bool Memory::getBiosInMemeory()
{
	return biosInMemory;
}