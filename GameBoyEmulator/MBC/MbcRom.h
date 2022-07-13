#ifndef DEF_MBCROM
#define DEF_MBCROM

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class MbcRom : public Mbc
{
public:
	MbcRom();

	uint32 getReadRomAddress(const uint16& address) const override;
	uint16 getReadRamAddress(const uint16& address) const override;

	void writeRomSetRomBank(const uint8& data, const uint16& address) override;
	void writeRamSetBankRam(const uint8& data, const uint16& address) override;
};

#endif // !DEF_ROM
