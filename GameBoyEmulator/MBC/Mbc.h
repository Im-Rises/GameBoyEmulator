#ifndef DEF_MBC
#define DEF_MBC

#include <string>

#include "../binaryLib/binaryLib.h"
#include <vector>

class Mbc
{
protected:
	uint8 currentRomBank, currentRamBank;
	bool romBankingEnabled, ramBankingEnabled;

public:
	/*---------------Constructor and Destructor-----------------------*/
	Mbc(int nbrRomBanks, int nbrRamBanks);
	~Mbc();

	/*---------------Read and write methods-----------------------*/
	virtual uint32 getReadRomAddress(const uint16& address) const = 0;
	virtual uint16 getReadRamAddress(const uint16& address) const = 0;

	virtual void writeRomSetRomBank(const uint8& data, const uint16& address) = 0;
	virtual void writeRamSetBankRam(const uint8& data, const uint16& address) = 0;


	/*---------------Getters and setters-----------------------*/
	uint8 getCurrentRomBank() const;
	void setCurrentRomBank(const int& currentRomBank);
	uint8 getCurrentRamBank() const;
	void setCurrentRamBank(const int& currentRamBank);

	bool getRomBankingEnabled() const;
	void setRomBankingEnabled(const bool& romBankingEnabled);
	bool getRamBankingEnabled() const;
	void setRamBankingEnabled(const bool& ramBankingEnabled);
};

#endif
