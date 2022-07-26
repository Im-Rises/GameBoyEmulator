#ifndef DEF_MBC2
#define DEF_MBC2

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class Mbc2 : public Mbc
{
public:
	Mbc2();

	void handleBanking(const uint16& address, const uint8& data) override;

	void register0(const uint8& data);
	void register1(const uint8& data);
};

#endif // !DEF_ROM
