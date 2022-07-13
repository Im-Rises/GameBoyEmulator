#include "Cartridge.h"

#include <iostream>
#include <string>

using namespace std;

Cartridge::Cartridge(string romPath)
{
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

	cartridgeType = header.cartridgeType;

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
		mbcPtr = std::make_shared<Rom>(nbrRomBanks, nbrRamBanks);
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

void Cartridge::writeRom(const uint8& data, const uint16& address)
{
	mbcPtr->writeRom(address, data);
}

void Cartridge::writeRam(const uint8& data, const uint16& address)
{
	mbcPtr->writeRam(address, data);
}

std::string Cartridge::getGameName() const
{
	return gameTitle;
}
