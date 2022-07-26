#ifndef DEF_MBCROM
#define DEF_MBCROM

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class MbcRom : public Mbc
{
public:
	MbcRom();

	void handleBanking(const uint16& address, const uint8& data) override;
};

#endif // !DEF_ROM
