#ifndef DEF_MBC1
#define DEF_MBC1

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class Mbc1 : public Mbc
{
public:
	Mbc1();

	void writeRomSetRomBank(const uint16& address, const uint8& data) override;
	void writeRamSetBankRam(const uint16& address, const uint8& data) override;
};

#endif // !DEF_ROM
