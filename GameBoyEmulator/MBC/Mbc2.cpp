#include "Mbc2.h"

Mbc2::Mbc2()
{
}

void Mbc2::handleBanking(const uint16& address, const uint8& data)
{
	if (address <= 0x0FFF)
	{
		register0(data);
	}
	else if (0x2100 <= address && address <= 0x21FF)
	{
		register1(data);
	}
}

void Mbc2::register0(const uint8& data)
{
	ramAccessEnabled = (data & 0x0F) == 0x0A;
}

void Mbc2::register1(const uint8& data)
{
	currentRomBank = data & 0x0F;
}
