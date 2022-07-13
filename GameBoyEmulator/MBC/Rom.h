#ifndef DEF_ROM
#define DEF_ROM

#include <string>
#include "../binaryLib/binaryLib.h"
#include "Mbc.h"

class Mbc;

class Rom : public Mbc
{
public:
	Rom(int nbrRomBanks, int nbrRamBanks);

	uint32 getReadRomAddress(const uint16& address) const override;
	uint16 getReadRamAddress(const uint16& address) const override;
};

#endif // !DEF_ROM
