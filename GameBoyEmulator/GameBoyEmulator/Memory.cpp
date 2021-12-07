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

void Memory::write(uint16_t index, uint8_t value)
{
	memoryArray[index] = value;
}