#include "Mbc3.h"

Mbc3::Mbc3()
{
	// ramAccessEnabled = true;
	// romBankingEnabled = true;
}

void Mbc3::handleBanking(const uint16& address, const uint8& data)
{
	if (address < 0x2000)
		register0(data);
	else if (address < 0x4000)
		register1(data);
	else if (address < 0x4000)
		register2(data);
	else if (address < 0x6000)
		register3(data);
}

void Mbc3::register0(const uint8& data)
{
	ramAccessEnabled = (data & 0x0F) == 0x0A;
}

void Mbc3::register1(const uint8& data)
{
	currentRomBank &= 0b10000000; //Reset the lower 5 bits
	currentRomBank |= (data & 0b01111111); //Change the bits from 0 to 4
	if (currentRomBank == 0) currentRomBank++;
	romBankingEnabled = true;
}

void Mbc3::register2(const uint8& data)
{
}

void Mbc3::register3(const uint8& data)
{
}
