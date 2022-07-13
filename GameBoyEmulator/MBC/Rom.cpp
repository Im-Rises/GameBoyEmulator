#include "Rom.h"

Rom::Rom(int nbrRomBanks, int nbrRamBanks):Mbc(nbrRomBanks,nbrRamBanks)
{

}

uint32 Rom::getReadRomAddress(const uint16& address) const
{
	return address;
}

uint16 Rom::getReadRamAddress(const uint16& address) const
{
	return address;
}
