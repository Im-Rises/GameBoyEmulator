#ifndef DEF_CARTRIDGE
#define DEF_CARTRIDGE


#include <iostream>
#include <fstream>
#include <map>

#include "binaryLib/binaryLib.h"

using namespace std;

enum CartridgeType
{
	ROM,
	MBC1,
	MBC2,
	MBC3,
	MBC5
};

class Cartridge
{
private:
	string romPath;

	CartridgeType cartridgeType;

	//Rom and Ram banking
	uint8* rom = nullptr; //uint8 gameRom[0x100000];//Max rom size 8Mb, 1Mo
	uint8* ram = nullptr; //Ram bank of size 0x2000 (maximum of 4 ram bank)

	uint8 currentRomBank;
	uint8 currentRamBank;

	bool romBankingEnable;
	bool ramBankingEnable;


	//Other data p299
	string gameName;
	string gameCode;
	uint8 cgbSupport;
	uint8 romSize;
	uint8 externalRamSize;
	uint8 destinationCode;
	string destinationText;

	map<uint8, string> destinationMap;

public:
	//Constructor and destructor
	Cartridge(const string& romPath);
	~Cartridge();
	void reset();

	//Read and write
	uint8 readRomBank(const uint16& address) const;


	uint8 readRamBank(const uint16& address) const;
	void writeRamBank(const uint16& address, const uint8& data);

	void handleBanking(const uint16& address, const uint8& data);

private:
	//Handle rom and ram banking
	void mbcRegister0(const uint16& address, const uint8& data);
	void mbcRegister1(const uint16& address, const uint8& data);
	void mbcRegister2(const uint16& address, const uint8& data);
	void mbcRegister3(const uint16& address, const uint8& data);

public:
	//Getters and setters

	CartridgeType getCartridgeType();

	uint8 getCurrentRamBank() const;
	void setCurrentRamBank(uint8 value);

	uint8 getCurrentRomBank() const;
	void setCurrentRomBank(uint8 value);

	bool getRamBankingEnable() const;
	void setRamBankingEnable(bool state);

	uint8 getRomFromIndex(int index) const;

	string getCartridgeTypeToString() const;

	//toString

	string getGameName()const;
	string getRomPath()const;

	string toString() const;
};

#endif
