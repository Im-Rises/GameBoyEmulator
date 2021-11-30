#include "Cpu.h"

Cpu::Cpu()
{
	
}

void Cpu::readOpcode()
{

}

void Cpu::executeOpcode(uint8_t opcode)
{
	if (opcode == 0xCB)
	{
		//Advance of 1 in the memory and use CB opcode switch
		//executeTwoBytesOpcode();
	}
	else
	{
		executeOneByteOpcode(opcode);
	}
}

void Cpu::executeOneByteOpcode(uint8_t opcode)
{

}

void Cpu::executeTwoBytesOpcode(uint8_t opcode)
{

}
