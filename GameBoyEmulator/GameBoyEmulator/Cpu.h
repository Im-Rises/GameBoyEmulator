#ifndef DEF_CPU
#define DEF_CPU

#include <iostream>
using namespace std;

class Cpu {

private:

	/// <summary>
	/// 8 bits registers
	/// </summary>
	uint8_t A;					//Accumulator A
	uint8_t B, C, D, E, H, L;	//Auxiliary registers of the accumulator A, they work by pairs (BC, DE, HL)

	/// <summary>
	/// Program Counter and Stack Pointer
	/// </summary>
	uint16_t pc;				//Program counter
	uint16_t sp;				//Stack pointer

	/// <summary>
	/// Flags
	/// </summary>
	struct Flag {
		bool Z;					//Set to 1 when the result of an operation is 0
		bool N;					//Set to 1 following execution of the substraction instruction, regardless of the result
		bool H;					//Set to 1 when an operation results in carrying from or borrowing to bit 3
		bool CY;				//Set to 1 when an operation results in carrying from or borrowing to bit 7
	} F;						//Auxiliary register of the accumulator, consist of 4 flags that are set and reset according to the results of instruction execution

	struct Opcode {
		string name;
		uint8_t value;
		uint8_t cycle;
	}
	const opcodeOneByteArray[0XFF] = {
		{"NOP",0x00,1},{"",0x01,NULL}
	},
	const opcodeTwoBytesArray[0XFF] = {

	};

public:
	Cpu();
	void readOpcode();
	void executeOpcode(uint8_t opcode);

private:
	void executeOneByteOpcode(uint8_t opcode);
	void executeTwoBytesOpcode(uint8_t opcode);
};

#endif
