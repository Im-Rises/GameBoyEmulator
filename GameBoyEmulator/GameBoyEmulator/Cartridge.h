#ifndef DEF_CARTRIDGE
#define DEF_CARTRIDGE

#include "binaryLib.h"

#include <iostream>
#include <fstream>

using namespace std;

class Cartridge
{
private:
	//ifstream romFile;
	uint8* gameRom;//uint8 gameRom[0x100000];//Max GB rom size 8Mb, 1Mo
	uint8 ramBank[0x8000];//Ram bank of size 0x2000 (maximum of 4 ram bank)

	uint8 currentRomBank;
	uint8 currentRamBank;

	//uint8 MBC;
	enum cartridgeType {
		ROM,
		MBC1,
		MBC2,
		MBC3,
		MBC5
	}MBC;

	string gameName;
	string gameCode;
	uint8 CGBsupport;
	uint8 romSize;
	uint8 externalRamSize;
	string destination;


public:
	Cartridge(const string& romPath);
	~Cartridge();

	uint8 readRomBank(int address);
	uint8 readRamBank();
	uint8 writeRamBank();

	uint8 getCurrentRomBank();
	uint8 getCurrentRamBank();

	string toString();
};

#endif
