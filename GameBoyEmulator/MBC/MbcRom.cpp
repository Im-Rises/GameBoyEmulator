#include "MbcRom.h"

MbcRom::MbcRom(): Mbc()
{
	romBankingEnabled = true;
	ramBankingEnabled = true;
	currentRomBank = 1;
	currentRamBank = 0;
}

void MbcRom::writeRomSetRomRamBank(const uint16& address, const uint8& data)
{
	currentRomBank = data;
}

void MbcRom::writeRam(const uint16& address, const uint8& data)
{
	currentRamBank = data;
}
