#include "Rom.h"

Rom::Rom(std::string rompath, int nbrRomBanks, int nbrRamBanks):Mbc(rompath, nbrRomBanks,nbrRamBanks)
{

}

uint8 Rom::readRom(const uint16& address) const
{
	return rom[address];
}
