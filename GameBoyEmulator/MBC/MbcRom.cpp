#include "MbcRom.h"

MbcRom::MbcRom(): Mbc()
{
	romBankingEnabled = true;
	ramAccessEnabled = true;
	currentRomBank = 1;
	currentRamBank = 0;
}

void MbcRom::handleBanking(const uint16& address, const uint8& data)
{
	currentRomBank = data;
}

