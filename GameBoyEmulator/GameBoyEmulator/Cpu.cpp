#include "Cpu.h"

Cpu::Cpu()
{
	
}

void Cpu::readOpcode()
{

}

void Cpu::executeOpcode(uint8_t opcode)
{
	/// <summary>
	/// 
	/// Lists of all the opcodes of the CPU.
	/// X is a representation of a bit of r
	/// Y is a representation of a bit of r'
	/// 
	/// 8 bits transfer I/O instructions:
	/// 01XXXYYY
	/// 00XXX110
	/// 01XXX110
	/// 
	/// 01110XXX
	/// 00110110
	/// 00001010
	/// 00011010
	/// 11110010
	/// 
	/// 11100010
	/// 11110000
	/// 11100000
	/// 11111010
	/// 
	/// 11101010
	/// 00101010
	/// 00111010
	/// 00000010
	/// 00010010
	/// 
	/// 00100010
	/// 00110010
	///
	/// 16 bits transfer I/O instructions:
	/// 00dd0001
	/// 11111001
	/// 11qq0101
	/// 
	/// 11qq0001
	/// 11111000
	/// 00001000
	/// 
	/// 
	/// 
	/// 8 bits arithmetic operation instructions
	/// 10000XXX
	/// 11000110
	/// 10000110
	/// 10001XXX
	/// 11001110
	/// 10001110
	/// 
	/// 10010XXX
	/// 11010110
	/// 10010110
	/// 10011XXX
	/// 11011110
	/// 10011110
	/// 10100XXX
	/// 11100110
	/// 10100110
	/// 
	/// 10110XXX
	/// 11110110
	/// 10110110
	/// 10101XXX
	/// 11101110
	/// 10101110
	/// 
	/// 10111XXX
	/// 11111110
	/// 10111110
	/// 00XXX100
	/// 00110100
	/// 00XXX101
	/// 
	/// 00110101
	/// 
	/// 
	/// 16 bits arithmetic operation instructions
	/// 00ss1001
	///	11101000
	/// 00ss0011
	/// 00ss1011
	/// 
	/// 
	/// 
	/// Rotate Shift Instructions
	/// 00000111
	/// 00010111
	/// 00001111
	/// 00011111
	/// p98
	/// 
	/// </summary>
	/// <param name="opcode"></param>
	switch (opcode & 0b11111111)
	{
	default:
		break;
	}
}