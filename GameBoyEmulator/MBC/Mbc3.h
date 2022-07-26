#ifndef DEF_MBC3
#define DEF_MBC3

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class Mbc3 : public Mbc
{
public:
	Mbc3();

	void handleBanking(const uint16& address, const uint8& data) override;

	void register0(const uint8& data);
	void register1(const uint8& data);
	void register2(const uint8& data);
	void register3(const uint8& data);
	void register4(const uint8& data);
};

#endif // !DEF_ROM
