#include "Mbc.h"

#include <string>

Mbc::Mbc(std::string rompath, int nbrRomBanks, int nbrRamBanks)
{
	this->nbrRomBanks = nbrRomBanks;
	this->nbrRamBanks = nbrRamBanks;
	rom.resize(nbrRomBanks * 0x4000);
	ram.resize(nbrRamBanks * 0x2000);

// rom = new uint8[0x200000];
// ram = new uint8[0x8000];
//
// cartridgeEmpty = true;
}

Mbc::~Mbc()
{
	// delete[] rom;
// delete[] ram;
}
