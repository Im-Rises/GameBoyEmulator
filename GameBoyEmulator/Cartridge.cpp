#include "Cartridge.h"

#include <iostream>
#include <string>
#include "MBC/MbcRom.h"

using namespace std;

Cartridge::Cartridge(const std::string& romPath)
{
	this->romPath = romPath;

	struct
	{
		char title[11];
		char manufacturerCode[4];
		char cgbFlag;
		char newLicenseeCode[2];
		char sgbFlag;
		char cartridgeType;
		char nbrRomBanks;
		char nbrRamBanks;
		char destinationCode;
		char oldLicenseeCode;
		char maskRomVersionNumber;
		char headerChecksum;
		char globalChecksum[2];
	} header{};

	ifstream input(romPath, std::ios::binary);
	if (!input)
	{
		cerr << "Error: Can't open rom file" << endl;
		exit(1);
	}

	input.seekg(0x0134);
	input.read(reinterpret_cast<char*>(&header), sizeof(header));

	gameTitle = header.title;
	manufacturerCode = header.manufacturerCode;
	cGBFlag = header.cgbFlag;

	if (header.oldLicenseeCode == 0x33)
		// May have issue here, no licensee code exceed 1 byte but it is still written with two bytes
		licensee = newLicenseeCodeMap.at(header.newLicenseeCode[0]);
	else
		licensee = oldLicenseeCodeMap.at(header.oldLicenseeCode);

	sGBFlag = header.sgbFlag;

	cartridgeType = cartridgeTypeMap.at(header.cartridgeType);

	char nbrRomBanks = romSizeCodeBankMap.at(header.nbrRomBanks);
	char nbrRamBanks = ramSizeCodeBankMap.at(header.nbrRamBanks);

	destination = destinationMap.at(header.destinationCode);

	maskRomVersion = header.maskRomVersionNumber;

	headerChecksum = header.headerChecksum;

	globalChecksum = header.globalChecksum;


	/*-------Handle MBC type----------*/

	switch (header.cartridgeType)
	{
	case(0x00):
		mbcPtr = std::make_shared<MbcRom>();
		break;
	// case(0x01):
	default:
		cerr << "Error unknown Cartridge type : " << header.cartridgeType << endl;
		exit(2);
	}


	/*-------Resize rom and ram----------*/
	rom.resize(nbrRomBanks * 0x4000);
	ram.resize(nbrRamBanks * 0x2000);

	/*-------Load complete rom----------*/
	input.seekg(0, ios::beg);
	input.read(reinterpret_cast<char*>(rom.data()), rom.size());

	input.close();
}

Cartridge::~Cartridge()
{
}

uint8 Cartridge::readRom(const uint16& address) const
{
	return rom[mbcPtr->getReadRomAddress(address)];
}

uint8 Cartridge::readRam(const uint16& address) const
{
	return ram[mbcPtr->getReadRamAddress(address)];
}

void Cartridge::writeRom(const uint16& address, const uint8& data)
{
	mbcPtr->writeRomSetRomBank(address, data);
}

void Cartridge::writeRam(const uint16& address, const uint8& data)
{
	mbcPtr->writeRamSetBankRam(address, data);
}

void Cartridge::dump(ofstream& savestateFile)
{
	cout << "Dumping Cartridge savestate data..." << endl;

	uint8 currentRomRamBanks[2] = {
		mbcPtr->getCurrentRomBank(), mbcPtr->getCurrentRamBank()
	};

	bool romRamBanksEnabled[2] = {
		mbcPtr->getRomBankingEnabled(), mbcPtr->getRamBankingEnabled()
	};

	savestateFile.write((char*)currentRomRamBanks, sizeof(currentRomRamBanks));
	savestateFile.write((char*)romRamBanksEnabled, sizeof(romRamBanksEnabled));
}

void Cartridge::loadDumpedData(ifstream& savestateFile)
{
	uint8 currentRomBank=0, currentRamBank = 0;
	bool romBankingEnabled = 0, ramBankingEnabled = 0;

	savestateFile.read((char*)&currentRomBank, sizeof(currentRomBank));
	mbcPtr->setCurrentRomBank(currentRomBank);
	savestateFile.read((char*)&currentRamBank, sizeof(currentRamBank));
	mbcPtr->setCurrentRamBank(currentRamBank);

	savestateFile.read((char*)&romBankingEnabled, sizeof(romBankingEnabled));
	mbcPtr->setRomBankingEnabled(romBankingEnabled);
	savestateFile.read((char*)&ramBankingEnabled, sizeof(ramBankingEnabled));
	mbcPtr->setRamBankingEnabled(ramBankingEnabled);
}

std::string Cartridge::getGameName() const
{
	return gameTitle;
}

std::string Cartridge::getRomPath() const
{
	return romPath;
}
