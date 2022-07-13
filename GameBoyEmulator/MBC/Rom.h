#ifndef DEF_ROM
#define DEF_ROM

#include <string>
#include "../binaryLib/binaryLib.h"
#include "Mbc.h"

class Mbc;

class Rom : public Mbc
{
public:
	Rom(std::string rompath, int nbrRomBanks, int nbrRamBanks);

	uint8 readRom(const uint16& address) const;
	uint8 readRam(const uint16& address) const;
};

#endif // !DEF_ROM
