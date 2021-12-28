#include "binaryLib.h"

uint8 getBit(uint8 byte, int bitIndex)
{
	return (byte >> bitIndex) & 0x1;
}

bool testBit(int value, int bitNumber)
{
	return (((value >> bitNumber) & 0x1) == 1);
}