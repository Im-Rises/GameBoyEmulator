#include "Cartridge.h"

#include <iostream>
#include <string>

using namespace std;

Cartridge::Cartridge()
{
}

Cartridge::~Cartridge()
{
}

void Cartridge::loadRom(std::string romPath)
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
	input.close();

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

	nbrRomBanks = romSizeCodeBankMap.at(header.nbrRomBanks);
	nbrRamBanks = ramSizeCodeBankMap.at(header.nbrRamBanks);

	destination = destinationMap.at(header.destinationCode);

	maskRomVersion = header.maskRomVersionNumber;

	headerChecksum = header.headerChecksum;

	globalChecksum = header.globalChecksum;


	/*-------Handle MBC type----------*/

	switch (header.cartridgeType)
	{
	case(0x00):
		mbcPtr = std::make_shared<Rom>(header.nbrRomBanks, header.nbrRamBanks);
		break;
	// case(0x01):
	default:
		cerr << "Error unknown Cartridge type : " << header.cartridgeType << endl;
		exit(2);
	}
}

uint8 Cartridge::readRom(const uint16& address) const
{
	return mbcPtr->readRom(address);
}

uint8 Cartridge::readRam(const uint16& address) const
{
	return mbcPtr->readRam(address);
}

void Cartridge::writeRom(const uint8& data, const uint16& address)
{
	return mbcPtr->writeRom(address, address);
}

void Cartridge::writeRam(const uint8& data, const uint16& address)
{
	return mbcPtr->writeRam(address, address);
}
