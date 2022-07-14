#ifndef DEF_MBC
#define DEF_MBC

#include <string>

#include "../binaryLib/binaryLib.h"
#include <vector>

class Mbc
{
protected:
	uint16 currentRomBank, currentRamBank;
	bool romBankingEnabled;
	bool ramAccessEnabled;
	bool battery;

public:
	/*---------------Constructor and Destructor-----------------------*/
	Mbc(bool battery = false);
	~Mbc();

	/*---------------Read and write methods-----------------------*/
	virtual void handleBanking(const uint16& address, const uint8& data) = 0;

	uint32 getReadRomAddress(const uint16& address) const;
	uint16 getReadWriteRamAddress(const uint16& address) const;

	// virtual void writeRam(const uint16& address, const uint8& data) = 0;

	// virtual void register0();
	// virtual void register1();
	// virtual void register2();
	// virtual void register3();
	// virtual void register4();

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
