#include "Mbc1.h"

void Mbc1::writeRomSetRomBank(const uint16& address, const uint8& data)
{
	if (address < 0x1FFF)
		currentRomBank = 0x0A;
}

void Mbc1::writeRamSetBankRam(const uint16& address, const uint8& data)
{
}
