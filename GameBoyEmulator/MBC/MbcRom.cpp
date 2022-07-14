#include "MbcRom.h"

MbcRom::MbcRom(): Mbc()
{
}

uint32 MbcRom::getReadRomAddress(const uint16& address) const
{
	return address + 0x4000 * currentRomBank;
}

uint16 MbcRom::getReadRamAddress(const uint16& address) const
{
	return address;
}

void MbcRom::writeRomSetRomBank(const uint16& address, const uint8& data)
{
	currentRomBank = data;
}

void MbcRom::writeRamSetBankRam(const uint16& address, const uint8& data)
{
	currentRamBank = data;
}
