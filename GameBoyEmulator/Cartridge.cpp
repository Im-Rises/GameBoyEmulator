#include "Cartridge.h"

#include <string>

Cartridge::Cartridge()
{
	destinationMap.insert(std::make_pair(0x00, "Japan"));
	destinationMap.insert(std::make_pair(0x01, "Other"));

	//Instead of loading all the rom to the ram of the computer, perhaps i should open the file and read it 
	rom = new uint8[0x200000];
	ram = new uint8[0x8000];

	cartridgeEmpty = true;
}

// Cartridge::Cartridge(const string& romPath)
// {
//
// }

Cartridge::~Cartridge()
{
	delete[] rom; //Not call if program crash
	delete[] ram;
}

void Cartridge::reset()
{
	currentRomBank = 1;
	currentRamBank = 0;
}

void Cartridge::dump(ofstream& savestateFile)
{
	uint8 currentRomRamBanks[2] = {
		currentRomBank, currentRamBank
	};

	bool romRamBanksEnabled[2] = {
		romBankingEnable, ramBankingEnable
	};


	cout << "Dumping Cartridge infos..." << endl;

	savestateFile.write((char*)currentRomRamBanks, sizeof(currentRomRamBanks));
	savestateFile.write((char*)romRamBanksEnabled, sizeof(romRamBanksEnabled));
}

void Cartridge::loadDumpedData(ifstream& savestateFile)
{
	savestateFile.read((char*)&currentRomBank, sizeof(currentRomBank));
	savestateFile.read((char*)&currentRamBank, sizeof(currentRamBank));

	savestateFile.read((char*)&romBankingEnable, sizeof(romBankingEnable));
	savestateFile.read((char*)&ramBankingEnable, sizeof(ramBankingEnable));
}

void Cartridge::writeRomInCartridge(const string& romPath)
{
	this->romPath = romPath;

	if (rom == nullptr || ram == nullptr)
	{
		cerr << "Error: cannot dynamically allocate memory" << endl;
		exit(1);
	}

	for (int i = 0; i < 0x200000; i++)
	{
		rom[i] = 0;
	}

	ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		input.seekg(0, ios::beg);
		for (int i = 0; (i < romSize) && (i < 0x100000); i++)
		{
			rom[i] = input.get();
		}
		input.close();
	}
	else
	{
		cerr << "Error: Can't open rom file" << endl;
		exit(1);
	}

	currentRomBank = 1;
	currentRamBank = 0;

	ramBankingEnable = false;


	for (int i = 0; i < 11; i++)
	{
		gameName += (char)rom[0x134 + i];
	}

	for (int i = 0; i < 4; i++)
	{
		gameCode += (char)rom[0x13F + i];
	}

	cgbSupport = rom[0x143];

	switch (rom[0x147])
	{
	case(0):
		{
			cartridgeType = ROM;
			break;
		}
	case(1):
		{
			cartridgeType = MBC1;
			break;
		}
	case(2):
		{
			cartridgeType = MBC1;
			break;
		}
	case(3):
		{
			cartridgeType = MBC1;
			break;
		}
	case(5):
		{
			cartridgeType = MBC2;
			break;
		}
	case(6):
		{
			cartridgeType = MBC2;
			break;
		}
	default:
		cerr << "Error: Cartridge type not recognized" << endl;
		exit(1);
	}

	romSize = rom[0x148];

	externalRamSize = rom[0x149];

	destinationCode = rom[0x014A];
	destinationText = destinationMap[destinationCode];

	cartridgeEmpty = false;

	cout << this->toString() << endl;
}


//Read and write
uint8 Cartridge::readRomBank(const uint16& address) const
{
	// int temp = address - 0x4000 + currentRomBank * 0x4000 > 0x200000;
	// int temp2 = currentRomBank;
	// if (address - 0x4000 + currentRomBank * 0x4000 > 0x200000)
	// 	exit(1);
	// return rom[0];

	return rom[address - 0x4000 + currentRomBank * 0x4000];
}

uint8 Cartridge::readRamBank(const uint16& address) const
{
	return ram[address - 0xA000 + currentRamBank * 0x2000];
}

void Cartridge::writeRamBank(const uint16& address, const uint8& data)
{
	ram[address - 0xA000 + currentRamBank * 0x2000] = data;
}


void Cartridge::handleBanking(const uint16& address, const uint8& data)
{
	//Developper guide p215
	if (cartridgeType != ROM)
	{
		if (address < 0x2000)
		{
			mbcRegister0(address, data);
		}
		else if ((address >= 0x2000) && (address < 0x4000))
		{
			mbcRegister1(address, data);
		}
		else if ((address >= 0x4000) && (address < 0x6000))
		{
			mbcRegister2(address, data);
		}
		else if ((address >= 0x6000) && (address < 0x8000))
		{
			mbcRegister3(address, data);
		}
	}
}


void Cartridge::mbcRegister0(const uint16& address, const uint8& data)
{
	//Register 0

	switch (cartridgeType)
	{
	case(ROM):
		{
			cerr << "Error: Error enabling/disactivating ram bank, ROM cartridge type ." << endl;
			exit(1);
		}
	case(MBC1):
		{
			if ((data & 0x0F) == 0x0A)
				ramBankingEnable = true;
			else
				ramBankingEnable = false;
			break;
		}
	case(MBC2):
		{
			if (address <= 0x0FFF)
			{
				if ((data & 0x0F) == 0x0A)
					ramBankingEnable = true;
				else
					ramBankingEnable = false;
			}
			break;
		}
	case(MBC3):
		{
			if ((data & 0x0F) == 0x0A)
				ramBankingEnable = true;
			else
				ramBankingEnable = false;
			break;
		}
	case(MBC5):
		{
			cerr << "Error: Error enabling/deactivating ram bank, MBC5 cartridge type not implemented." << endl;
			exit(1);
		}
	default:
		cerr << "Error: Error enabling/deactivating ram bank, cartridge type not recognized." << endl;
		exit(1);
	}
}

void Cartridge::mbcRegister1(const uint16& address, const uint8& data)
{
	//Register 1

	switch (cartridgeType)
	{
	case(ROM):
		{
			cerr << "Error: Error chaning rom bank low address, ROM cartridge type." << endl;
			exit(1);
		}
	case(MBC1):
		{
			currentRomBank &= 0b11100000; //Reset lower bits
			currentRomBank |= (data & 0b00011111); //Change the bits from 0 to 4
			break;
		}
	case(MBC2):
		{
			if (address >= 0x2100 && address <= 0x21FF)
			{
				currentRomBank = data & 0x0F;
			}
			break;
		}
	case(MBC3):
		{
			currentRomBank &= 0b10000000; //Reset lower bits
			currentRomBank |= (data & 0b01111111); //Change the bits from 0 to 6
			break;
		}
	case(MBC5):
		{
			cerr << "Error: Error changing rom bank low address, MBC5 cartridge not implemented." << endl;
			exit(1);
		}
	default:
		cerr << "Error: Error changing rom bank low address, cartridge type not recognized." << endl;
		exit(1);
	}

	(currentRomBank == 0) ? currentRomBank++ : currentRomBank;
	//If romBank equals 0 thant add 1 (don't know if it is a necessity)
}


void Cartridge::mbcRegister2(const uint16& address, const uint8& data)
{
	//Register 2

	switch (cartridgeType)
	{
	case(ROM):
		{
			cerr << "Error: Error chaning rom bank high address, ROM cartridge type." << endl;
			exit(1);
			break;
		}
	case(MBC1):
		{
			if (romBankingEnable)
			{
				currentRomBank &= 0b00011111; //Reset high bits (5 to 7)
				//currentRomBank |= ((data << 5) & 0b01100000);//Add the bits 5 and 6 (no data shifting needed)
				currentRomBank |= (data & 0b01100000); //Add the bits 5 and 6
			}
			else
			{
				currentRamBank = data & 0x3;
			}
			break;
		}
	case(MBC2):
		{
			//Do nothing
			break;
		}
	case(MBC3):
		{
			cerr << "Error: Error changing rom bank high address, MBC3 cartridge not implemented." << endl;
			exit(1);
		}
	case(MBC5):
		{
			cerr << "Error: Error changing rom bank high address, MBC5 cartridge not implemented." << endl;
			exit(1);
		}
	default:
		cerr << "Error: Error changing rom bank high address, cartridge type not recognized." << endl;
		exit(1);
	}

	(currentRomBank == 0) ? currentRomBank++ : currentRomBank;
	//If romBank equals 0 thant add 1 (don't know if it is a necessity)
}


void Cartridge::mbcRegister3(const uint16& address, const uint8& data)
{
	switch (cartridgeType)
	{
	case(ROM):
		{
			cerr << "Error: Error changing changeRomRam mode, ROM cartridge type." << endl;
			exit(1);
			break;
		}
	case(MBC1):
		{
			romBankingEnable = (data == 1);
			if (romBankingEnable)
				currentRamBank = 0;
			break;
		}
	case(MBC2):
		{
			//Do nothing
			break;
		}
	case(MBC3):
		{
			cerr << "Error: Error changing changeRomRam mode, MBC3 cartridge type." << endl;
			exit(1);
			break;
		}
	case(MBC5):
		{
			cerr << "Error: Error changing changeRomRam mode, MBC5 cartridge type." << endl;
			exit(1);
			break;
		}
	default:
		cerr << "Error: Error changing changeRomRam mode, cartridge type not recognized." << endl;
		exit(1);
		break;
	}
}


//Getters and setters

CartridgeType Cartridge::getCartridgeType()
{
	return cartridgeType;
}


uint8 Cartridge::getCurrentRamBank() const
{
	return currentRamBank;
}

void Cartridge::setCurrentRamBank(uint8 value)
{
	currentRamBank = value;
}


uint8 Cartridge::getCurrentRomBank() const
{
	return currentRomBank;
}

void Cartridge::setCurrentRomBank(uint8 value)
{
	currentRomBank = value;
}


bool Cartridge::getRamBankingEnable() const
{
	return ramBankingEnable;
}

void Cartridge::setRamBankingEnable(bool state)
{
	ramBankingEnable = state;
}


uint8 Cartridge::getRomFromIndex(int index) const
{
	return rom[index];
}

string Cartridge::getCartridgeTypeToString() const
{
	switch (this->cartridgeType)
	{
	case(ROM):
		{
			return "ROM";
		}
	case(MBC1):
		{
			return "MBC1";
		}
	case(MBC2):
		{
			return "MBC2";
		}
	case(MBC3):
		{
			return "MBC3";
		}
	case(MBC5):
		{
			return "MBC5";
		}
	default:
		cerr << "Error: Unknown cartridge name." << endl;
		exit(1);
	}
}

bool Cartridge::getCartridgeIsEmpty() const
{
	return cartridgeEmpty;
}


string Cartridge::getGameName() const
{
	return gameName;
}

string Cartridge::getRomPath() const
{
	return romPath;
}

//toString

string Cartridge::toString() const
{
	return "Game name: " + gameName + "\nCartridge type: " + getCartridgeTypeToString() + "\nDestination: " +
		destinationText + " " +
		std::to_string(destinationCode);
}
