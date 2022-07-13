#include "Cartridge.h"

#include <iostream>
#include <string>

using namespace std;

Cartridge::Cartridge()
{
	//Instead of loading all the rom to the ram of the computer, perhaps i should open the file and read it 
	// rom = new uint8[0x200000];
	// ram = new uint8[0x8000];
	//
	// cartridgeEmpty = true;
}

Cartridge::~Cartridge()
{
	// delete[] rom;
	// delete[] ram;
}

void Cartridge::loadRom(std::string romPath)
{
	ifstream input(romPath, std::ios::binary);
	if (!input)
	{
		cerr << "Error: Can't open rom file" << endl;
		exit(1);
	}

	input.seekg(0x0134);
	input.read((char*)&header, sizeof(header));
	input.close();

	bool usingNewLicenseeCode = header.oldLicenseeCode == 0x33;

	if (usingNewLicenseeCode)
	{
		
	}
	else
	{
		
	}
}
