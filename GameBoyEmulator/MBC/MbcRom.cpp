#include "MbcRom.h"

MbcRom::MbcRom():Mbc()
{

}

uint32 MbcRom::getReadRomAddress(const uint16& address) const
{
	return address;
}

uint16 MbcRom::getReadRamAddress(const uint16& address) const
{
	return address;
}

void MbcRom::writeRomSetRomBank(const uint16& address, const uint8& data)
{
	//Do nothing (no bank switching)
}

void MbcRom::writeRamSetBankRam(const uint16& address, const uint8& data)
{
	//Do nothing (no bank switching)
}
