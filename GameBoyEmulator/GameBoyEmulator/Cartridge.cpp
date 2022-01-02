#include "Cartridge.h"

Cartridge::Cartridge(const string& romPath)
{
	//Instead of loading all the rom to the ram of the computer, perhaps i should open the file and read it 
	gameRom = new uint8[0x800000];

	ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		input.seekg(0, ios::beg);
		for (int i = 0; (i < romSize) && (i < 0x100000); i++)
		{
			gameRom[i] = input.get();
		}
		input.close();
	}
	else
	{
		cout << "Can't open rom file" << endl;
		exit(1);
	}

	currentRomBank = 1;
	currentRamBank = 0;



	for (int i = 0; i < 11; i++)
	{
		gameName += (char)gameRom[0x134 + i];
	}

	for (int i = 0; i < 4; i++)
	{
		gameCode += (char)gameRom[0x13F + i];
	}

	CGBsupport = gameRom[0x143];

	switch (gameRom[0x127])
	{
	case(0):
	{
		MBC = ROM;
		break;
	}
	case(1):
	{
		MBC = MBC1;
		break;
	}
	case(2):
	{
		MBC = MBC1;
		break;
	}
	case(3):
	{
		MBC = MBC1;
		break;
	}
	case(5):
	{
		MBC = MBC2;
		break;
	}
	case(6):
	{
		MBC = MBC2;
		break;
	}
	default:
		break;
	}

	romSize = gameRom[0x148];

	externalRamSize = gameRom[0x149];

	destination = gameRom[0x014A];

}

Cartridge::~Cartridge()
{
	delete[] gameRom;//Not call if program crash
}

uint8 Cartridge::readRomBank(int address)
{
	return gameRom[address];
}

uint8 readRamBank();
uint8 writeRamBank();

uint8 Cartridge::getCurrentRomBank()
{
	return currentRomBank;
}

uint8  Cartridge::getCurrentRamBank()
{
	return currentRamBank;
}

string toString();