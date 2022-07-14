#ifndef DEF_MBCROM
#define DEF_MBCROM

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class MbcRom : public Mbc
{
public:
	MbcRom();

	// uint32 getReadRomAddress(const uint16& address) const override;
	// uint16 getReadRamAddress(const uint16& address) const override;

	void writeRomSetRomBank(const uint16& address, const uint8& data) override;
	void writeRamSetBankRam(const uint16& address, const uint8& data) override;
};

#endif // !DEF_ROM
