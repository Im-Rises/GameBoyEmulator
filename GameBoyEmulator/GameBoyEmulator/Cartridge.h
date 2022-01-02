#ifndef DEF_CARTRIDGE
#define DEF_CARTRIDGE

#include "binaryLib.h"

#include <iostream>
#include <fstream>

using namespace std;

class Cartridge
{
private:
	string gameName;
	int MBC;
	uint8 gameRom[0x100000];//Max GB rom size 8Mb, 1Mo

public:
	Cartridge(const string& romPath);
};

#endif
