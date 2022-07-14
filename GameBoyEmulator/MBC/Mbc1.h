#ifndef DEF_MBC1
#define DEF_MBC1

#include "../binaryLib/binaryLib.h"

#include "Mbc.h"

class Mbc1 : public Mbc
{
public:
	Mbc1();

	void handleBanking(const uint16& address, const uint8& data) override;

	void register0(const uint8& data);
	void register1(const uint8& data);
	void register2(const uint8& data);
	void register3(const uint8& data);
};

#endif // !DEF_ROM
