#include "MbcRom.h"

MbcRom::MbcRom(): Mbc()
{
}

void MbcRom::writeRomSetRomBank(const uint16& address, const uint8& data)
{
	currentRomBank = data;
}

void MbcRom::writeRamSetBankRam(const uint16& address, const uint8& data)
{
	currentRamBank = data;
}
