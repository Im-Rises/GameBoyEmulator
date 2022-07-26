#ifndef DEF_MBC5
#define DEF_MBC5

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class Mbc5 : public Mbc
{
public:
	Mbc5();

	void handleBanking(const uint16& address, const uint8& data) override;

	void register0(const uint8& data);
	void register1(const uint8& data);
	void register2(const uint8& data);
	void register3(const uint8& data);
};

#endif // !DEF_ROM
