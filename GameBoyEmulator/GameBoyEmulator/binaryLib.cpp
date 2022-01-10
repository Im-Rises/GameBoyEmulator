#include "binaryLib.h"

uint8 getBit(const uint8& byte, const int& bitIndex)
{
	return (byte >> bitIndex) & 0x1;
}

uint8 setBit(const uint8& byte, const int& bitIndex)
{
	return (byte | (0b00000001 << bitIndex));
}

uint8 resetBit(const uint8& byte, const int& bitIndex)
{
	return (byte & (~(0b00000001 << bitIndex)));
}

bool testBit(const int& value, const int& bitNumber)
{
	return (((value >> bitNumber) & 0x1) == 1);
}