#include "Mbc1.h"

Mbc1::Mbc1(): Mbc()
{
}

void Mbc1::writeRomSetRomRamBank(const uint16& address, const uint8& data)
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

void Mbc1::writeRam(const uint16& address, const uint8& data)
{
}

void Mbc1::register0(const uint8& data)
{
	ramBankingEnabled = data == 0x0A;
}

void Mbc1::register1(const uint8& data)
{
	romBankingEnabled = 0x01 <= data && data <= 0x1F;
}

void Mbc1::register2(const uint8& data)
{
	if (romBankingEnabled)
	{
		
	}
	if (ramBankingEnabled)
	{
		
	}
}

void Mbc1::register3(const uint8& data)
{
}
