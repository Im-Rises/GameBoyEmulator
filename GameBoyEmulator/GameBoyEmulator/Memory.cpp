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
	//if (index == 0xFF41)
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
	memoryArray[0xFF05] = 0x00;
	memoryArray[0xFF06] = 0x00;
	memoryArray[0xFF07] = 0x00;
	memoryArray[0xFF10] = 0x80;
	memoryArray[0xFF11] = 0xBF;
	memoryArray[0xFF12] = 0xF3;
	memoryArray[0xFF14] = 0xBF;
	memoryArray[0xFF16] = 0x3F;
	memoryArray[0xFF17] = 0x00;
	memoryArray[0xFF19] = 0xBF;
	memoryArray[0xFF1A] = 0x7F;
	memoryArray[0xFF1B] = 0xFF;
	memoryArray[0xFF1C] = 0x9F;
	memoryArray[0xFF1E] = 0xBF;
	memoryArray[0xFF20] = 0xFF;
	memoryArray[0xFF21] = 0x00;
	memoryArray[0xFF22] = 0x00;
	memoryArray[0xFF23] = 0xBF;
	memoryArray[0xFF24] = 0x77;
	memoryArray[0xFF25] = 0xF3;
	memoryArray[0xFF26] = 0xF1;
	memoryArray[0xFF40] = 0x91;
	memoryArray[0xFF42] = 0x00;
	memoryArray[0xFF43] = 0x00;
	memoryArray[0xFF45] = 0x00;
	memoryArray[0xFF47] = 0xFC;
	memoryArray[0xFF48] = 0xFF;
	memoryArray[0xFF49] = 0xFF;
	memoryArray[0xFF4A] = 0x00;
	memoryArray[0xFF4B] = 0x00;
	memoryArray[0xFFFF] = 0x00;
}



bool Memory::getBiosInMemeory()
{
	return biosInMemory;
}