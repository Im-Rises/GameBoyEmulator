#include "Memory.h"

#include <iostream>

#include "Spu.h"

Memory::Memory(Joypad* joypad, Spu* spu) //memoryArray{}
{
	this->spu = spu;
	this->joypad = joypad;
	biosInMemory = false;
	gameInMemory = false;

	for (uint8& i : memoryArray)
		i = 0x0;

	// To print the black rectangle when starting the game boy without games
	for (int i = 0x100; i < 0x8000; i++)
	{
		memoryArray[i] = 0xFF;
	}
}

Memory::~Memory()
{
	//delete[] memoryArray;
}

void Memory::reset()
{
	//Reset all the memory
	for (int i = 0x8000; i < 0xFF00; i++)
	{
		memoryArray[i] = 0;
	}

	// Don't reset (from 0xFF00 to 0xFF7F):
	/*
	 * Port/Mode Registers
	 * Control Register
	 * Sound Register
	 */

	for (int i = 0xFF80; i < MEMORY_SIZE; i++)
	{
		memoryArray[i] = 0;
	}
}

void Memory::dump(ofstream& savestateFile)
{
	// Dump memory from 0x8000 to 0xFFFF

	cout << "Dumping MMU ..." << endl;

	savestateFile.write(((char*)memoryArray) + 0x8000, sizeof(memoryArray) - 0x8000);
}

void Memory::loadDumpedData(ifstream& savestateFile)
{
	savestateFile.read(((char*)memoryArray) + 0x8000, sizeof(memoryArray) - 0x8000);
}

void Memory::connectCartridge(shared_ptr<Cartridge>& cartridge)
{
	this->cartridgePtr = cartridge;

	int index = 0;
	if (biosInMemory)
		index = 0x100;

	// if (cartridge)
	// {
	for (int i = index; i < 0x8000; i++)
	{
		memoryArray[i] = cartridge->readRom(i);
	}
	// }
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
		cerr << "Error: Can't open bios file" << endl;
		return false;
	}
}

void Memory::loadRomBeginning()
{
	if (cartridgePtr)
	{
		for (int i = 0; i < 0x100; i++)
		{
			memoryArray[i] = cartridgePtr->readRom(i);
		}
		biosInMemory = false;
	}
}


void Memory::setMemoryWithoutBios()
{
	//memoryArray[0xFF00] = 0b00111111;//Controller

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


uint8 Memory::read(const uint16 address)
{
	// if (address == 0x0104)
	// 	cerr << "here" << endl;

	if ((address >= 0x4000) && (address <= 0x7FFF)) //Read in rom bank area (Cartridge)
	{
		return cartridgePtr->readRom(address);
	}
	else if ((address >= 0xA000) && (address <= 0xBFFF))
	//Read in ram bank also known as External Expansion Working RAM (Cartridge)
	{
		return cartridgePtr->readRam(address);
	}
	else if (address == 0xFF00) //Trap input's read
	{
		uint8 temp = joypad->readInputs(memoryArray[0xFF00]);
		if (joypad->getEnableInterrupt())
			requestInterrupt(4);
		return temp;
	}
	else //Read everywhere else in the memory (memory)
	{
		return memoryArray[address];
	}
}

void Memory::write(const uint16& address, const uint8 value)
{
	if (address < 0x8000) //Writting in this area change the used banks in the cartridge
	{
		cartridgePtr->writeRom(address, value);
	}
	else if (address >= 0xA000 && address < 0xC000) //External expension ram wrtting
	{
		cartridgePtr->writeRam(address, value);
	}
	else if (address >= 0xE000 && address < 0xFE00)
	{
		//cerr << "Error: Writting in the first reserved area" << endl;
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
		//cerr << "Error: Writting in the second reserved area" << endl;
		//exit(1);
	}
	else if (address == 0xFF46)
	{
		uint16 address = value << 8;
		for (int i = 0; i < 0xA0; i++)
		{
			write(0xFE00 + i, read(address + i));
		}
	}
	else if (address == 0xFF14 && (value >> 7))
	{
		memoryArray[address] = value;
		spu->resetSound1(memoryArray[0xff11] & 0x3f);
	}
	else if (address == 0xFF19 && (value >> 7))
	{
		memoryArray[address] = value;
		spu->resetSound2(memoryArray[0xff16] & 0x3f);
	}
	else if (address == 0xFF1E && (value >> 7))
	{
		memoryArray[address] = value;
		spu->resetSound3(value);
	}
	else if (address == 0xFF23 && (value >> 7))
	{
		memoryArray[address] = value;
		spu->resetSound4(value);
	}
	else if (address == 0xFF26)
	{
		if (value)
			memoryArray[0xff26] = 0xff;
		else
			memoryArray[0xff26] = 0x00;
	}
	else //Write everywhere else (Character Data, BG Display Data 1, BG Display Data 2, OAM etc...
	{
		memoryArray[address] = value;
	}
}

uint8 Memory::directRead(const uint16& address) const
{
	return memoryArray[address];
}

void Memory::directWrite(const uint16& address, const uint8& value)
{
	//This function write in the memory without taking care of the ram/rom banks
	//It is used for the timers that needs to write to the memory without being treated like it was from the user program
	memoryArray[address] = value;
}


void Memory::requestInterrupt(uint8 bitIndex)
{
	uint8 ifRegister = memoryArray[INTERRUPT_FLAG_IF_ADDRESS];
	ifRegister = setBit(ifRegister, bitIndex);
	memoryArray[INTERRUPT_FLAG_IF_ADDRESS] = ifRegister;
}


void Memory::setResetBitMemory(const uint16& address, const bool bit, const int bitIndex)
{
	if (bit)
		memoryArray[address] = setBit(memoryArray[address], bitIndex);
	else
		memoryArray[address] = resetBit(memoryArray[address], bitIndex);
}


bool Memory::getBiosInMemeory() const
{
	return biosInMemory;
}
