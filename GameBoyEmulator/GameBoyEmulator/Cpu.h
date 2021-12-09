#ifndef DEF_CPU
#define DEF_CPU

#include "Memory.h"
#include "Ppu.h"

#include <iostream>

using namespace std;

class Cpu {

private:

	int cycles;					//Cycles to do (incremented after each instructions)

	/// <summary>
	/// Frequency of the CPU
	/// </summary>
	double frequencyNormalMode = 1.05;//In MHZ
	double frequencyDoubleSpeedMode = 2.10;//In MHZ

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
	
	//Memory* memory = nullptr;
	Memory memory;				//Memory of the console

public:
	//Cpu(Memory* memory);						//Constructor
	Cpu();
	~Cpu();
	void loadRom(const string& romPath);
	void start();

private:

	void readOpcode();							//Read an opcode
	void executeOpcode(uint8_t opcode);			//Execute an opcode
	void executeOpcodeFollowingCB();			//Execute an opcode on two bytes (following the CB opcode) 

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
	void operationOpcode_BIT_aHL();
	void operationOpcode_SET_R(uint8_t& reg);

	//Page 17	(p104)
	void operationOpcode_SET_aHL();

	void operationOpcode_RES_R(uint8_t& reg);
	void operationOpcode_RES_aHL();


	/*-------------------------------------JUMP INSTRUCTIONS---------------------------------------*/
	
	/////////////////////////////////////TO CHECK////////////////////////////////////////////////////
	// Error, with the e in the functions
	//Page 18	(p105)
	void operationOpcode_JP_d16();
	void operationOpcode_JP_cc();
	void operationOpcode_JR();

	//Page 19	(p106)
	void operationOpcode_JR_cc();
	void operationOpcode_JP_HL();

	/*-------------------------------------CALL AND RETURN INSTRUCTIONS---------------------------------------*/
	//Page 19	(p107)
	void operationOpcode_CALL();
	void operationOpcode_CALL_cc();

	//Page 20	(p108)
	void operationOpcode_RET();
	void operationOpcode_RETI();
	void operationOpcode_RET_cc();

	//Page 21	(p109)
	void operationOpcode_RST();

	/*-------------------------------------GENERAL-PURPOSE ARITHMETIC OPERATIONS AND CPU CONTROL INSTRUCTIONS---------------------------------------*/
	//Page 20	(p108)
	void operationOpcode_DAA();//TO CHECK
	void operationOpcode_CPL();
	void operationOpcode_NOP();

	//Page 21	(p109)
	void operationOpcode_HALT();//NOT IMPLEMENTED
	void operationOpcode_STOP();//NOT IMPLEMENTED

	void operationOpcode_EI();//NOT IMPLEMENTED
	void operationOpcode_DI();//NOT IMPLEMENTED

};

#endif
