#include "Mbc.h"

#include <string>

Mbc::Mbc()
{
}

Mbc::~Mbc()
{
}

uint8 Mbc::getCurrentRomBank() const
{
	return currentRomBank;
}

void Mbc::setCurrentRomBank(const int& currentRomBank)
{
	this->currentRomBank= currentRomBank;
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
	return ramBankingEnabled;
}

void Mbc::setRamBankingEnabled(const bool& ramBankingEnabled)
{
	this->ramBankingEnabled = ramBankingEnabled;
}

