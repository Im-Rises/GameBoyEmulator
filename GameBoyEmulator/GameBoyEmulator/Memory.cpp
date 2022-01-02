#include "Memory.h"

Memory::Memory()
{
	reset();
}

void Memory::reset()
{
	biosInMemory = false;
	gameInMemory = false;
	//Reset all the memory
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memoryArray[i] = 0;
	}

	//For bootrom black square
	for (int i = 0x100; i < 0x150; i++)
	{
		memoryArray[i] = 0xFF;
	}
}

void Memory::connectCartridge(Cartridge* cartridge)
{
	this->cartridge = cartridge;
}


bool Memory::loadBiosInMemory(const string& biosPath)
{
	std::ifstream input(biosPath, std::ios::binary);
	if (input)
	{
		input.seekg(0, ios::beg);
		for (int i = 0; i < ROM_DATA_AREA; i++)
		{
			memoryArray[i] = input.get();
		}
		input.close();
		biosInMemory = true;
		return true;
	}
	else
	{
		cout << "Can't open bios file" << endl;
		return false;
	}
}

bool Memory::loadRomInMemory(const string& romPath)
{
	//Load rom from cartridge

	//std::ifstream input(romPath, std::ios::binary);
	//if (input)
	//{
	//	input.seekg(0, ios::end);
	//	int romSize = input.tellg();
	//	input.seekg(0, ios::beg);

	//	if (biosInMemory)
	//	{
	//		for (int i = 0; i < 0x100; i++)//Load RST and interrupt address in a temporary array
	//		{
	//			//memoryTempInterruptRst[i] = input.get();
	//		}
	//		for (int i = 0x100; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
	//		{
	//			memoryArray[i] = input.get();
	//		}
	//	}
	//	else
	//	{
	//		for (int i = 0; (i < romSize) && (i < RAM_CHARACTER_DATA_BANK_0_DMG); i++)
	//		{
	//			memoryArray[i] = input.get();
	//		}
	//	}

	//	//checkMemoryBankingUsed();
	//	gameInMemory = true;
	//	input.close();
	//	return true;
	//}
	//else
	//{
	//	cout << "Can't open rom file" << endl;
	//	return false;
	//}


}

//void Memory::loadTempArrayInterruptRst()
//{
//	for (int i = 0; i < 0x100; i++)
//	{
//		//memoryArray[i] = memoryTempInterruptRst[i];
//	}
//}

void Memory::setMemoryWithoutBios()
{
	memoryArray[0xFF05] = 0x00;
	memoryArray[0xFF06] = 0x00;
	memoryArray[0xFF07] = 0x00;
	memoryArray[0xFF10] = 0x80;
	memoryArray[0xFF11] = 0xBF;
	memoryArray[0xFF12] = 0xF3;
	memoryArray[0xFF14] = 0xBF;
	memoryArray[0xFF16] = 0x3F;
	memoryArray[0xFF17] = 0x00;
	memoryArray[0xFF19] = 0xBF;
	memoryArray[0xFF1A] = 0x7F;
	memoryArray[0xFF1B] = 0xFF;
	memoryArray[0xFF1C] = 0x9F;
	memoryArray[0xFF1E] = 0xBF;
	memoryArray[0xFF20] = 0xFF;
	memoryArray[0xFF21] = 0x00;
	memoryArray[0xFF22] = 0x00;
	memoryArray[0xFF23] = 0xBF;
	memoryArray[0xFF24] = 0x77;
	memoryArray[0xFF25] = 0xF3;
	memoryArray[0xFF26] = 0xF1;
	memoryArray[0xFF40] = 0x91;
	memoryArray[0xFF42] = 0x00;
	memoryArray[0xFF43] = 0x00;
	memoryArray[0xFF45] = 0x00;
	memoryArray[0xFF47] = 0xFC;
	memoryArray[0xFF48] = 0xFF;
	memoryArray[0xFF49] = 0xFF;
	memoryArray[0xFF4A] = 0x00;
	memoryArray[0xFF4B] = 0x00;
	memoryArray[0xFFFF] = 0x00;
}

//void Memory::checkMemoryBankingUsed()
//{
//	/*
//	* Game Boy programing manual V1.1 (p298)
//	*/
//	switch (memoryArray[0x147])
//	{
//	case(1):
//	{
//		mbc1 = true;
//		break;
//	}
//	case(2):
//	{
//		mbc1 = true;
//		break;
//	}
//	case(3):
//	{
//		mbc1 = true;
//		break;
//	}
//	case(5):
//	{
//		mbc2 = true;
//		break;
//	}
//	case(6):
//	{
//		mbc2 = true;
//		break;
//	}
//	}
//}


uint8 Memory::read(const uint16 address)const
{
	if ((address >= 0x4000) && (address <= 0x7FFF))//Read in rom bank area
	{
		return cartridge->readRomBank(address - 0x4000 + cartridge->getCurrentRomBank() * 0x4000);
	}
	else if ((address >= 0x1000) && (address <= 0xBFFF))//Read in ram bank area
	{
		return cartridge->readRomBank(address - 0xA000 + cartridge->getCurrentRomBank() * 0x2000);
	}
	else//Read in base game (bank 0)
	{
		return memoryArray[address];
	}
}

void Memory::write(const uint16& address, uint8 value)
{
	//if (index == 0xFF41)
	//	cout << "error" << endl;

	if (address < 0x8000)
	{
		cerr << "Error: Writting in the read only area" << endl;
		exit(1);
	}
	else if (address >= 0xE000 && address < 0xFE00)
	{
		cerr << "Error: Writting in the first reserved area" << endl;
		/*
		* According to pandocs "Game BoyTM CPU Manual":
		* The addresses E000-FE00 appear to access the internal
		* RAM the same as C000-DE00. (i.e. If you write a byte to
		* address E000 it will appear at C000 and E000.
		* Similarly, writing a byte to C000 will appear at C000
		* and E000.)
		*/
		memoryArray[address] = value;
		memoryArray[address - 0x2000] = value;
	}
	else if ((address >= 0xFEA0) && (address < 0xFEFF))
	{
		cerr << "Error: Writting in the second reserved area" << endl;
		exit(1);
	}
	else
	{
		memoryArray[address] = value;
	}
}



void Memory::increment(const uint16& address)
{
	memoryArray[address]++;
}

void Memory::decrement(const uint16& address)
{
	memoryArray[address]--;
}



void Memory::setResetBitMemory(const uint16& address, const bool bit, const int bitIndex)
{
	if (bit)
		memoryArray[address] = setBit(memoryArray[address], bitIndex);
	else
		memoryArray[address] = resetBit(memoryArray[address], bitIndex);
}


bool Memory::getBiosInMemeory()
{
	return biosInMemory;
}