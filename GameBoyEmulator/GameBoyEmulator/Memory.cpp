#include "Memory.h"

Memory::Memory()
{
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memoryArray[i] = 0;
	}
}

uint8_t Memory::getMemoryOfIndex(uint16_t index)
{
	return memoryArray[index];
}

void Memory::setMemoryOfIndex(uint16_t index, uint8_t value)
{
	memoryArray[index] = value;
}