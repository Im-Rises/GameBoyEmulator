#include "Mbc5.h"

Mbc5::Mbc5()
{
	// ramAccessEnabled = true;
	romBankingEnabled = true;
}

void Mbc5::handleBanking(const uint16& address, const uint8& data)
{
	if (address < 0x2000)
		register0(data);
	else if (address < 0x3000)
		register1(data);
	else if (address < 0x4000)
		register2(data);
	else if (address < 0x6000)
		register3(data);
}

void Mbc5::register0(const uint8& data)
{
	ramAccessEnabled = (data & 0x0F) == 0x0A;
}

void Mbc5::register1(const uint8& data)
{
	currentRomBank &= 0x10;
	currentRomBank |= data;
}

void Mbc5::register2(const uint8& data)
{
	currentRomBank &= 0x0F;
	currentRomBank |= data << 8;
}

void Mbc5::register3(const uint8& data)
{
	currentRamBank = data & 0x0F;
}
