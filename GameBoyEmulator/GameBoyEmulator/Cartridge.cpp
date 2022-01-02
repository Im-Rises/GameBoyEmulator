#include "Cartridge.h"

Cartridge::Cartridge(const string& romPath)
{
	std::ifstream input(romPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::end);
		int romSize = input.tellg();
		input.seekg(0, ios::beg);

		if (biosInMemory)
		{
			for (int i = 0; i < 0x100; i++)//Load RST and interrupt address in a temporary array
			{
				memoryTempInterruptRst[i] = input.get();
			}
			for (int i = 0x100; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
			{
				memoryArray[i] = input.get();
			}
		}
		else
		{
			for (int i = 0; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
			{
				memoryArray[i] = input.get();
			}
		}

		checkMemoryBankingUsed();

		input.close();
	}
	else
	{
		cout << "Can't open rom file" << endl;
		exit(1);
	}
}