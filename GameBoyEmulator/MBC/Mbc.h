#ifndef DEF_MBC
#define DEF_MBC

#include <string>

#include "../binaryLib/binaryLib.h"
#include <vector>

class Mbc
{
protected:
	int nbrRomBanks, nbrRamBanks;
	std::vector<uint8> rom, ram;

public:
	Mbc(std::string rompath, int nbrRomBanks, int nbrRamBanks);
	~Mbc();

	virtual uint8 readRom(const uint16& address) const = 0;
	virtual uint8 readRam(const uint16& address) const = 0;

	virtual void writeRom(const uint8& data, const uint16& address) = 0;
	virtual void writeRam(const uint8& data, const uint16& address) = 0;
};

#endif
