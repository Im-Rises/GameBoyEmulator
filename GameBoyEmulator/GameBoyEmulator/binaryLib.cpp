#include "binaryLib.h"

uint8 getBit(uint8 byte, int bitIndex)
{
	return (byte >> bitIndex) & 0x1;
}

uint8 setBit(uint8 byte, int bitIndex)
{
	return (byte | (1 << bitIndex));
}

bool testBit(int value, int bitNumber)
{
	return (((value >> bitNumber) & 0x1) == 1);
}