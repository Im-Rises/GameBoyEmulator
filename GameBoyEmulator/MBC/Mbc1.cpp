#include "Mbc1.h"

Mbc1::Mbc1(): Mbc()
{
	romBankingEnabled = true;
	ramAccessEnabled = true;
}

void Mbc1::handleBanking(const uint16& address, const uint8& data)
{
	if (address < 0x2000)
		register0(data);
	else if (address < 0x4000)
		register1(data);
	else if (address < 0x6000)
		register2(data);
	else if (address < 0x8000)
		register3(data);
}

void Mbc1::register0(const uint8& data)
{
	ramAccessEnabled = (data & 0x0F) == 0x0A;
}

void Mbc1::register1(const uint8& data)
{
	currentRomBank &= 0b11100000; //Reset the lower 5 bits
	currentRomBank |= (data & 0b00011111); //Change the bits from 0 to 4
	if (currentRomBank == 0) currentRomBank++;
	romBankingEnabled = true;
}

void Mbc1::register2(const uint8& data)
{
	if (romBankingEnabled)
	{
		currentRomBank &= 0b00011111; //Reset high bits (5 to 7)
		//currentRomBank |= ((data << 5) & 0b01100000);//Add the bits 5 and 6 (no data shifting needed)
		currentRomBank |= (data & 0b01100000); //Add the bits 5 and 6
	}
	else
	{
		currentRamBank = data & 0x3;
	}
}

void Mbc1::register3(const uint8& data)
{
	romBankingEnabled = (data == 1);
	if (romBankingEnabled)
		currentRamBank = 0;
}
