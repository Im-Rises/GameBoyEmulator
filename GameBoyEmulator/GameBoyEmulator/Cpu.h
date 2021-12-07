#ifndef DEF_CPU
#define DEF_CPU

#include "Memory.h"

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
	struct Flag {				//Flag structure:
		bool Z;					//Set to 1 when the result of an operation is 0
		bool N;					//Set to 1 following execution of the substraction instruction, regardless of the result
		bool H;					//Set to 1 when an operation results in carrying from or borrowing to bit 3
		bool CY;				//Set to 1 when an operation results in carrying from or borrowing to bit 7
	} F;						//Auxiliary register of the accumulator, consist of 4 flags that are set and reset according to the results of instruction execution


	/// <summary>
	/// Opcodes arrays with name, value and cycle time 
	/// </summary>

	const struct Opcode {				//Opcode structure:
		string name;			//Opcode name
		uint8_t value;			//Opcode value
		uint8_t cycle;			//Opcode cycle
	}
	opcodes_array[256] = {	//Normal ocpodes
	{"NOP",0x00,NULL}, {"",0x01,NULL}, {"",0x02,NULL}, {"",0x03,NULL}, {"",0x04,NULL}, {"",0x05,NULL}, {"",0x06,NULL}, {"",0x07,NULL}, {"",0x08,NULL}, {"",0x09,NULL}, {"",0x0A,NULL}, {"",0x0B,NULL}, {"",0x0C,NULL}, {"",0x0D,NULL}, {"",0x0E,NULL}, {"",0x0F,NULL}, {"",0x10,NULL}, {"",0x11,NULL}, {"",0x12,NULL}, {"",0x13,NULL}, {"",0x14,NULL}, {"",0x15,NULL}, {"",0x16,NULL}, {"",0x17,NULL}, {"",0x18,NULL}, {"",0x19,NULL}, {"",0x1A,NULL}, {"",0x1B,NULL}, {"",0x1C,NULL}, {"",0x1D,NULL}, {"",0x1E,NULL}, {"",0x1F,NULL},
	{"",0x20,NULL}, {"",0x21,NULL}, {"",0x22,NULL}, {"",0x23,NULL}, {"",0x24,NULL}, {"",0x25,NULL}, {"",0x26,NULL}, {"",0x27,NULL}, {"",0x28,NULL}, {"",0x29,NULL}, {"",0x2A,NULL}, {"",0x2B,NULL}, {"",0x2C,NULL}, {"",0x2D,NULL}, {"",0x2E,NULL}, {"",0x2F,NULL}, {"",0x30,NULL}, {"",0x31,NULL}, {"",0x32,NULL}, {"",0x33,NULL}, {"",0x34,NULL}, {"",0x35,NULL}, {"",0x36,NULL}, {"",0x37,NULL}, {"",0x38,NULL}, {"",0x39,NULL}, {"",0x3A,NULL}, {"",0x3B,NULL}, {"",0x3C,NULL}, {"",0x3D,NULL}, {"",0x3E,NULL}, {"",0x3F,NULL},
	{"",0x40,NULL}, {"",0x41,NULL}, {"",0x42,NULL}, {"",0x43,NULL}, {"",0x44,NULL}, {"",0x45,NULL}, {"",0x46,NULL}, {"",0x47,NULL}, {"",0x48,NULL}, {"",0x49,NULL}, {"",0x4A,NULL}, {"",0x4B,NULL}, {"",0x4C,NULL}, {"",0x4D,NULL}, {"",0x4E,NULL}, {"",0x4F,NULL}, {"",0x50,NULL}, {"",0x51,NULL}, {"",0x52,NULL}, {"",0x53,NULL}, {"",0x54,NULL}, {"",0x55,NULL}, {"",0x56,NULL}, {"",0x57,NULL}, {"",0x58,NULL}, {"",0x59,NULL}, {"",0x5A,NULL}, {"",0x5B,NULL}, {"",0x5C,NULL}, {"",0x5D,NULL}, {"",0x5E,NULL}, {"",0x5F,NULL},
	{"",0x60,NULL}, {"",0x61,NULL}, {"",0x62,NULL}, {"",0x63,NULL}, {"",0x64,NULL}, {"",0x65,NULL}, {"",0x66,NULL}, {"",0x67,NULL}, {"",0x68,NULL}, {"",0x69,NULL}, {"",0x6A,NULL}, {"",0x6B,NULL}, {"",0x6C,NULL}, {"",0x6D,NULL}, {"",0x6E,NULL}, {"",0x6F,NULL}, {"",0x70,NULL}, {"",0x71,NULL}, {"",0x72,NULL}, {"",0x73,NULL}, {"",0x74,NULL}, {"",0x75,NULL}, {"",0x76,NULL}, {"",0x77,NULL}, {"",0x78,NULL}, {"",0x79,NULL}, {"",0x7A,NULL}, {"",0x7B,NULL}, {"",0x7C,NULL}, {"",0x7D,NULL}, {"",0x7E,NULL}, {"",0x7F,NULL},
	{"",0x80,NULL}, {"",0x81,NULL}, {"",0x82,NULL}, {"",0x83,NULL}, {"",0x84,NULL}, {"",0x85,NULL}, {"",0x86,NULL}, {"",0x87,NULL}, {"",0x88,NULL}, {"",0x89,NULL}, {"",0x8A,NULL}, {"",0x8B,NULL}, {"",0x8C,NULL}, {"",0x8D,NULL}, {"",0x8E,NULL}, {"",0x8F,NULL}, {"",0x90,NULL}, {"",0x91,NULL}, {"",0x92,NULL}, {"",0x93,NULL}, {"",0x94,NULL}, {"",0x95,NULL}, {"",0x96,NULL}, {"",0x97,NULL}, {"",0x98,NULL}, {"",0x99,NULL}, {"",0x9A,NULL}, {"",0x9B,NULL}, {"",0x9C,NULL}, {"",0x9D,NULL}, {"",0x9E,NULL}, {"",0x9F,NULL},
	{"",0xA0,NULL}, {"",0xA1,NULL}, {"",0xA2,NULL}, {"",0xA3,NULL}, {"",0xA4,NULL}, {"",0xA5,NULL}, {"",0xA6,NULL}, {"",0xA7,NULL}, {"",0xA8,NULL}, {"",0xA9,NULL}, {"",0xAA,NULL}, {"",0xAB,NULL}, {"",0xAC,NULL}, {"",0xAD,NULL}, {"",0xAE,NULL}, {"",0xAF,NULL}, {"",0xB0,NULL}, {"",0xB1,NULL}, {"",0xB2,NULL}, {"",0xB3,NULL}, {"",0xB4,NULL}, {"",0xB5,NULL}, {"",0xB6,NULL}, {"",0xB7,NULL}, {"",0xB8,NULL}, {"",0xB9,NULL}, {"",0xBA,NULL}, {"",0xBB,NULL}, {"",0xBC,NULL}, {"",0xBD,NULL}, {"",0xBE,NULL}, {"",0xBF,NULL},
	{"",0xC0,NULL}, {"",0xC1,NULL}, {"",0xC2,NULL}, {"",0xC3,NULL}, {"",0xC4,NULL}, {"",0xC5,NULL}, {"",0xC6,NULL}, {"",0xC7,NULL}, {"",0xC8,NULL}, {"",0xC9,NULL}, {"",0xCA,NULL}, {"",0xCB,NULL}, {"",0xCC,NULL}, {"",0xCD,NULL}, {"",0xCE,NULL}, {"",0xCF,NULL}, {"",0xD0,NULL}, {"",0xD1,NULL}, {"",0xD2,NULL}, {"",0xD3,NULL}, {"",0xD4,NULL}, {"",0xD5,NULL}, {"",0xD6,NULL}, {"",0xD7,NULL}, {"",0xD8,NULL}, {"",0xD9,NULL}, {"",0xDA,NULL}, {"",0xDB,NULL}, {"",0xDC,NULL}, {"",0xDD,NULL}, {"",0xDE,NULL}, {"",0xDF,NULL},
	{"",0xE0,NULL}, {"",0xE1,NULL}, {"",0xE2,NULL}, {"",0xE3,NULL}, {"",0xE4,NULL}, {"",0xE5,NULL}, {"",0xE6,NULL}, {"",0xE7,NULL}, {"",0xE8,NULL}, {"",0xE9,NULL}, {"",0xEA,NULL}, {"",0xEB,NULL}, {"",0xEC,NULL}, {"",0xED,NULL}, {"",0xEE,NULL}, {"",0xEF,NULL}, {"",0xF0,NULL}, {"",0xF1,NULL}, {"",0xF2,NULL}, {"",0xF3,NULL}, {"",0xF4,NULL}, {"",0xF5,NULL}, {"",0xF6,NULL}, {"",0xF7,NULL}, {"",0xF8,NULL}, {"",0xF9,NULL}, {"",0xFA,NULL}, {"",0xFB,NULL}, {"",0xFC,NULL}, {"",0xFD,NULL}, {"",0xFE,NULL}, {"",0xFF,NULL},
	},
	opcodesCB_array[256] = {	//Opcodes following a CB opcode
	{"",0x00,NULL}, {"",0x01,NULL}, {"",0x02,NULL}, {"",0x03,NULL}, {"",0x04,NULL}, {"",0x05,NULL}, {"",0x06,NULL}, {"",0x07,NULL}, {"",0x08,NULL}, {"",0x09,NULL}, {"",0x0A,NULL}, {"",0x0B,NULL}, {"",0x0C,NULL}, {"",0x0D,NULL}, {"",0x0E,NULL}, {"",0x0F,NULL}, {"",0x10,NULL}, {"",0x11,NULL}, {"",0x12,NULL}, {"",0x13,NULL}, {"",0x14,NULL}, {"",0x15,NULL}, {"",0x16,NULL}, {"",0x17,NULL}, {"",0x18,NULL}, {"",0x19,NULL}, {"",0x1A,NULL}, {"",0x1B,NULL}, {"",0x1C,NULL}, {"",0x1D,NULL}, {"",0x1E,NULL}, {"",0x1F,NULL},
	{"",0x20,NULL}, {"",0x21,NULL}, {"",0x22,NULL}, {"",0x23,NULL}, {"",0x24,NULL}, {"",0x25,NULL}, {"",0x26,NULL}, {"",0x27,NULL}, {"",0x28,NULL}, {"",0x29,NULL}, {"",0x2A,NULL}, {"",0x2B,NULL}, {"",0x2C,NULL}, {"",0x2D,NULL}, {"",0x2E,NULL}, {"",0x2F,NULL}, {"",0x30,NULL}, {"",0x31,NULL}, {"",0x32,NULL}, {"",0x33,NULL}, {"",0x34,NULL}, {"",0x35,NULL}, {"",0x36,NULL}, {"",0x37,NULL}, {"",0x38,NULL}, {"",0x39,NULL}, {"",0x3A,NULL}, {"",0x3B,NULL}, {"",0x3C,NULL}, {"",0x3D,NULL}, {"",0x3E,NULL}, {"",0x3F,NULL},
	{"",0x40,NULL}, {"",0x41,NULL}, {"",0x42,NULL}, {"",0x43,NULL}, {"",0x44,NULL}, {"",0x45,NULL}, {"",0x46,NULL}, {"",0x47,NULL}, {"",0x48,NULL}, {"",0x49,NULL}, {"",0x4A,NULL}, {"",0x4B,NULL}, {"",0x4C,NULL}, {"",0x4D,NULL}, {"",0x4E,NULL}, {"",0x4F,NULL}, {"",0x50,NULL}, {"",0x51,NULL}, {"",0x52,NULL}, {"",0x53,NULL}, {"",0x54,NULL}, {"",0x55,NULL}, {"",0x56,NULL}, {"",0x57,NULL}, {"",0x58,NULL}, {"",0x59,NULL}, {"",0x5A,NULL}, {"",0x5B,NULL}, {"",0x5C,NULL}, {"",0x5D,NULL}, {"",0x5E,NULL}, {"",0x5F,NULL},
	{"",0x60,NULL}, {"",0x61,NULL}, {"",0x62,NULL}, {"",0x63,NULL}, {"",0x64,NULL}, {"",0x65,NULL}, {"",0x66,NULL}, {"",0x67,NULL}, {"",0x68,NULL}, {"",0x69,NULL}, {"",0x6A,NULL}, {"",0x6B,NULL}, {"",0x6C,NULL}, {"",0x6D,NULL}, {"",0x6E,NULL}, {"",0x6F,NULL}, {"",0x70,NULL}, {"",0x71,NULL}, {"",0x72,NULL}, {"",0x73,NULL}, {"",0x74,NULL}, {"",0x75,NULL}, {"",0x76,NULL}, {"",0x77,NULL}, {"",0x78,NULL}, {"",0x79,NULL}, {"",0x7A,NULL}, {"",0x7B,NULL}, {"",0x7C,NULL}, {"",0x7D,NULL}, {"",0x7E,NULL}, {"",0x7F,NULL},
	{"",0x80,NULL}, {"",0x81,NULL}, {"",0x82,NULL}, {"",0x83,NULL}, {"",0x84,NULL}, {"",0x85,NULL}, {"",0x86,NULL}, {"",0x87,NULL}, {"",0x88,NULL}, {"",0x89,NULL}, {"",0x8A,NULL}, {"",0x8B,NULL}, {"",0x8C,NULL}, {"",0x8D,NULL}, {"",0x8E,NULL}, {"",0x8F,NULL}, {"",0x90,NULL}, {"",0x91,NULL}, {"",0x92,NULL}, {"",0x93,NULL}, {"",0x94,NULL}, {"",0x95,NULL}, {"",0x96,NULL}, {"",0x97,NULL}, {"",0x98,NULL}, {"",0x99,NULL}, {"",0x9A,NULL}, {"",0x9B,NULL}, {"",0x9C,NULL}, {"",0x9D,NULL}, {"",0x9E,NULL}, {"",0x9F,NULL},
	{"",0xA0,NULL}, {"",0xA1,NULL}, {"",0xA2,NULL}, {"",0xA3,NULL}, {"",0xA4,NULL}, {"",0xA5,NULL}, {"",0xA6,NULL}, {"",0xA7,NULL}, {"",0xA8,NULL}, {"",0xA9,NULL}, {"",0xAA,NULL}, {"",0xAB,NULL}, {"",0xAC,NULL}, {"",0xAD,NULL}, {"",0xAE,NULL}, {"",0xAF,NULL}, {"",0xB0,NULL}, {"",0xB1,NULL}, {"",0xB2,NULL}, {"",0xB3,NULL}, {"",0xB4,NULL}, {"",0xB5,NULL}, {"",0xB6,NULL}, {"",0xB7,NULL}, {"",0xB8,NULL}, {"",0xB9,NULL}, {"",0xBA,NULL}, {"",0xBB,NULL}, {"",0xBC,NULL}, {"",0xBD,NULL}, {"",0xBE,NULL}, {"",0xBF,NULL},
	{"",0xC0,NULL}, {"",0xC1,NULL}, {"",0xC2,NULL}, {"",0xC3,NULL}, {"",0xC4,NULL}, {"",0xC5,NULL}, {"",0xC6,NULL}, {"",0xC7,NULL}, {"",0xC8,NULL}, {"",0xC9,NULL}, {"",0xCA,NULL}, {"",0xCB,NULL}, {"",0xCC,NULL}, {"",0xCD,NULL}, {"",0xCE,NULL}, {"",0xCF,NULL}, {"",0xD0,NULL}, {"",0xD1,NULL}, {"",0xD2,NULL}, {"",0xD3,NULL}, {"",0xD4,NULL}, {"",0xD5,NULL}, {"",0xD6,NULL}, {"",0xD7,NULL}, {"",0xD8,NULL}, {"",0xD9,NULL}, {"",0xDA,NULL}, {"",0xDB,NULL}, {"",0xDC,NULL}, {"",0xDD,NULL}, {"",0xDE,NULL}, {"",0xDF,NULL},
	{"",0xE0,NULL}, {"",0xE1,NULL}, {"",0xE2,NULL}, {"",0xE3,NULL}, {"",0xE4,NULL}, {"",0xE5,NULL}, {"",0xE6,NULL}, {"",0xE7,NULL}, {"",0xE8,NULL}, {"",0xE9,NULL}, {"",0xEA,NULL}, {"",0xEB,NULL}, {"",0xEC,NULL}, {"",0xED,NULL}, {"",0xEE,NULL}, {"",0xEF,NULL}, {"",0xF0,NULL}, {"",0xF1,NULL}, {"",0xF2,NULL}, {"",0xF3,NULL}, {"",0xF4,NULL}, {"",0xF5,NULL}, {"",0xF6,NULL}, {"",0xF7,NULL}, {"",0xF8,NULL}, {"",0xF9,NULL}, {"",0xFA,NULL}, {"",0xFB,NULL}, {"",0xFC,NULL}, {"",0xFD,NULL}, {"",0xFE,NULL}, {"",0xFF,NULL},
	};

	Memory memory;

public:
	Cpu();										//Constructor
	void readOpcode();							//Read an opcode
	void executeOpcode(uint8_t opcode);			//Execute an opcode
	void executeOpcodeFollowingCB();			//Execute an opcode on two bytes (following the CB opcode) 
	~Cpu();

private:

	uint16_t pairRegisters(const uint8_t reg1, const uint8_t reg2)const;
	uint8_t flagToByte(const Flag& flag)const;

	/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

	/// <summary>
	/// Registers functions:
	/// Mnemonic therms:
	/// - R register
	/// - aR the value pointed in the memory by the register
	/// - dR direct value of a register (sometimes written only R)
	/// - Ro means a register + an offset
	/// - aRo means the value in the memory pointed by the address of the register + an offset
	/// - RI means incrementation of the register
	/// - RD means decrementation of the register
	/// - RP registers pair (for example HL)
	///	- .... aRP, oRP, aRPowork the same for a pair of registers
	/// - X can be a register a d8
	/// - d8 direct 8 bits following in the memory pointed by the pc
	/// - d16 direct 16 bits following in the memory pointed by the pc and pc+1
	/// - a8 value in the memory pointed by the 8 following bits pointed by the pc 
	/// - a16 value in the memory pointed by 16 following bits pointed by the pc and pc+1
	/// </summary>


	/*-------------------------------------8bits TRANSFER AND INPUT/OUTPUT INSTRUCTIONS---------------------------------------*/

	//Page 1	(p85)
	void opcodeOperation_LD_R_R(uint8_t& reg1, const uint8_t& reg2);
	void opcodeOperation_LD_R_d8(uint8_t& reg);
	void opcodeOperation_LD_R_aRP(uint8_t& reg, const uint8_t regPair1, const uint8_t regPair2);

	//Page 2	(p86)
	void opcodeOperation_LD_aRP_R(const uint8_t& registerPair1, const uint8_t& registerPair2, const uint8_t& reg);
	void opcodeOperation_LD_aRP_d8(uint8_t& registerPair1, uint8_t& registerPair2);
	void opcodeOperation_LD_R_aRo(uint8_t& reg1, const uint8_t& reg2);

	//Page 3	(p87)
	void opcodeOperation_LD_aRo_R(const uint8_t& reg1, const uint8_t& reg2);
	void opcodeOperation_LD_R_a8o(uint8_t& reg);
	void opcodeOperation_LD_a8o_R(const uint8_t& reg);
	void opcodeOperation_LD_R_a16(uint8_t& reg);

	//Page 4	(p88)
	void opcodeOperation_LD_a16_R(const uint8_t& reg);
	void opcodeOperation_LD_R_aRP_RPI(uint8_t& reg, uint8_t regPair1, uint8_t regPair2);
	void opcodeOperation_LD_R_aRP_RPD(uint8_t& reg, uint8_t regPair1, uint8_t regPair2);

	//Page 5	(p89)
	void opcodeOperation_LD_aRP_R_RPI(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg);
	void opcodeOperation_LD_aRP_R_RPD(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg);


	/*-------------------------------------16bits TRANSFER INSTRUCTIONS---------------------------------------*/

	//Page 6	(p90) 
	void opcodeOperation16bits_LD_RP_d16(uint8_t& regPair1, uint8_t& regPair2);
	void opcodeOperation16bits_LD_RP_d16(uint16_t& registersPair);

	void opcodeOperation16bits_LD_RP_RP(uint16_t& registersPair, const uint8_t& regPairB1, const uint8_t& regPairB2);
	void opcodeOperation16bits_PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2);
	void opcodeOperation16bits_PUSH_RP(const uint8_t& regPair1, const Flag& flag);

	//Page 7	(p91)
	void opcodeOperation16bits_POP_RP(uint8_t& regPair1, uint8_t& regPair2);
	void opcodeOperation16bits_POP_RP(uint8_t& regPair1, Flag& flag);
	void opcodeOperation16bits_LDHL_SP_e();//TO BE CHECKED (issue possible with while casting)
	void opcodeOperation16bits_LD_a8_SP();


	/*-------------------------------------8bits ARITHMETIC AND LOGICAL OPERATION INSTRUCTIONS---------------------------------------*/

	//Page 8	(p92)
	void operationOpcode_ADD_R_R(uint8_t& reg1, const uint8_t& reg2);
	void operationOpcode_ADD_R_d8(uint8_t& reg1);
	void operationOpcode_ADD_R_aRP(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2);

	void operationOpcode_ADC_A_R_CY(const uint8_t& reg);//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SDC A,F.CY
	void operationOpcode_ADC_A_d8_CY();//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SDC A,F.CY
	void operationOpcode_ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SDC A,F.CY

	uint8_t operationOpcode_ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);
	int binaryAddition(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);


	//Page 9	(p93)
	void operationOpcode_SUB_A_R(const uint8_t& reg);
	void operationOpcode_SUB_A_d8();
	void operationOpcode_SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2);

	void operationOpcode_SBC_A_R_CY(const uint8_t& reg);//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SBC A,F.CY
	void operationOpcode_SBC_A_d8_CY();//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SBC A,F.CY
	void operationOpcode_SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);//TO BE CHECKED, PERHAPS IT IS NEEDED TO VERIFY IF F.CY=1 IF IT IS THAN WE DO THE SBC A,F.CY

	uint8_t operationOpcode_SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);
	int binarySubstraction(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);


	//Page 10	(p94)
	void operationOpcode_AND_R_R(uint8_t& reg1, const uint8_t& reg2);
	void operationOpcode_AND_R_d8(uint8_t& reg1);
	void operationOpcode_AND_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2);

	void operationOpcode_OR_R_R(uint8_t& reg1, const uint8_t& reg2);
	void operationOpcode_OR_R_d8(uint8_t& reg1);
	void operationOpcode_OR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2);

	void operationOpcode_XOR_R_R(uint8_t& reg1, const uint8_t& reg2);
	void operationOpcode_XOR_R_d8(uint8_t& reg1);
	void operationOpcode_XOR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2);


	//Page 11	(p95)
	void operationOpcode_CP_R_R(const uint8_t& reg1, const uint8_t& reg2);
	void operationOpcode_CP_R_d8(const uint8_t& reg1);
	void operationOpcode_CP_R_aHL(const uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2);
	void operationOpcode_CP_subFunctionFlag(const uint8_t& reg1, const uint8_t& reg2);


	void operationOpcode_INC_R(uint8_t& reg);
	void operationOpcode_INC_aHL(const uint8_t& regPair1, const uint8_t& regPair2);
	void operationOpcode_INC_subFunctionFlag(uint8_t& reg);

	void operationOpcode_DEC_R(uint8_t& reg);

	//Page 12	(p96)
	void operationOpcode_DEC_aHL(const uint8_t& regPair1, const uint8_t& regPair2);

	void operationOpcode_DEC_subFunctionFlag(uint8_t& reg);


	/*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/
	//Page 12	(p97)
	void operationOpcode16bits_ADD_HL_RP(const uint16_t& regsPair);
	void operationOpcode16bits_ADD_SP_e();
	void operationOpcode16bits_INC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void operationOpcode16bits_INC_RP(uint16_t& regsPair);
	void operationOpcode16bits_DEC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void operationOpcode16bits_DEC_RP(uint16_t& regsPair);

	int binaryAddition16bits(const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);


	/*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
	//Page 13	(p98)
	//TO CHECK, THERE MIGHT BE ERRORS IN THE EXAMPLES, SO THE OCPODES ARE POSSIBILY NOT WELL IMPLEMENTED
	void operationOpcode_RLCA();
	void operationOpcode_RLA();
	void operationOpcode_RRCA();
	void operationOpcode_RRA();



	//Page 14	(p99)
	void operationOpcode_RLC_R(uint8_t& reg);
	void operationOpcode_RLC_aHL();
	void operationOpcode_RL_R(uint8_t& reg);
	void operationOpcode_RL_aHL();

	//Page 15	(p100)
	void operationOpcode_RRC_R(uint8_t& reg);
	void operationOpcode_RRC_aHL();
	void operationOpcode_RR_R(uint8_t& reg);
	void operationOpcode_RR_aHL();

	//Page 16	(p101)
	void operationOpcode_SLA_R(uint8_t& reg);
	void operationOpcode_SLA_aHL();

	void operationOpcode_SRA_R(uint8_t& reg);
	void operationOpcode_SRA_aHL();

	//Page 17	(p102)
	void operationOpcode_SRL_R(uint8_t& reg);
	void operationOpcode_SRL_aHL();

	void operationOpcode_SWAP_R(uint8_t& reg);
	void operationOpcode_SWAP_aHL();

	/*-------------------------------------BIT OPERATIONS---------------------------------------*/

	//Page 16	(p103)
	void operationOpcode_BIT_R(const uint8_t& reg);

};

#endif
