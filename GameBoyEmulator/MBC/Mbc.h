#ifndef DEF_MBC
#define DEF_MBC

#include <string>

#include "../binaryLib/binaryLib.h"
#include <vector>

class Mbc
{
protected:
	int currentRomBank, currentRamBank;

public:
	Mbc(int nbrRomBanks, int nbrRamBanks);
	~Mbc();

	virtual uint32 getReadRomAddress(const uint16& address) const = 0;
	virtual uint16 getReadRamAddress(const uint16& address) const = 0;

	virtual void writeRom(const uint8& data, const uint16& address) = 0;
	virtual void writeRam(const uint8& data, const uint16& address) = 0;
};

#endif
