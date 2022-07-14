#include "Mbc.h"

#include <iostream>
#include <string>

using namespace std;

Mbc::Mbc(bool battery)
{
	this->battery = battery;
	romBankingEnabled = ramAccessEnabled = false;
	ramAccessEnabled = false;
	currentRomBank = 0;
	currentRamBank = 0;
}

Mbc::~Mbc()
{
}

uint32 Mbc::getReadRomAddress(const uint16& address) const
{
	if (romBankingEnabled)
		return address - 0x4000 + 0x4000 * currentRomBank;
	else
	{
		cerr << "Error: Rom banking access not enabled" << endl;
		exit(1);
	}
}

uint16 Mbc::getReadWriteRamAddress(const uint16& address) const
{
	if (ramAccessEnabled)
		return address - 0xA000 + 0x2000 * currentRamBank;
	else
	{
		cerr << "Error: Ram banking access not enabled" << endl;
		exit(1);
	}
}

uint8 Mbc::getCurrentRomBank() const
{
	return currentRomBank;
}

void Mbc::setCurrentRomBank(const int& currentRomBank)
{
	this->currentRomBank = currentRomBank;
}

uint8 Mbc::getCurrentRamBank() const
{
	return currentRamBank;
}

void Mbc::setCurrentRamBank(const int& currentRamBank)
{
	this->currentRamBank = currentRamBank;
}


bool Mbc::getRomBankingEnabled() const
{
	return romBankingEnabled;
}

void Mbc::setRomBankingEnabled(const bool& romBankingEnabled)
{
	this->romBankingEnabled = romBankingEnabled;
}

bool Mbc::getRamBankingEnabled() const
{
	return ramAccessEnabled;
}

void Mbc::setRamBankingEnabled(const bool& ramBankingEnabled)
{
	this->ramAccessEnabled = ramBankingEnabled;
}
