#ifndef DEF_CPU
#define DEF_CPU

#include "Memory.h"
#include "Ppu.h"

#include <iostream>

using namespace std;

class Cpu {

private:

	int cycles;					//Cycles to do (incremented after each instructions)

	bool halted;				//CPU is halted

	bool stopped;				//CPU is stopped

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

	bool IME;					//IME flag (Interupt Master Enable)

	//Memory* memory = nullptr;
	Memory memory;				//Memory of the console

public:
	//Cpu(Memory* memory);						//Constructor
	Cpu();										//Constructor without bios
	Cpu(const string& biosPath);				//Constructor with bios
	~Cpu();
	void loadBios(const string& biosPath);
	void loadRom(const string& romPath);
	void start();

private:

	void readOpcode();							//Read an opcode
	void executeOpcode(uint8_t opcode);			//Execute an opcode
	void executeOpcodeFollowingCB();			//Execute an opcode on two bytes (following the CB opcode) 

	uint16_t pairRegisters(const uint8_t reg1, const uint8_t reg2)const;
	void unpairRegisters(uint8_t& reg1, uint8_t& reg2, const uint16_t& registersPair);//The & 0x00FF is not an obligation

	uint8_t flagToByte(const Flag& flag)const;
	Flag byteToFlag(const uint8_t& byte)const;

	int binaryAddition(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);
	int binarySubstraction(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);

	/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

	/// <summary>
	/// Registers functions:
	/// Mnemonic therms:
	/// - R register
	/// - RP registers pair (for example HL
	/// - d8 direct 8 bits following in the memory pointed by the pc
	/// - d16 direct 16 bits following in the memory pointed by the pc and pc+1
	/// - aRP value pointed in the memory by the the registers pair value
	/// - Ro means a register + an offset
	/// - aRo means the value in the memory pointed by the address of the register + an offset
	/// - a8 value in the memory pointed by the 8 following bits pointed by the pc 
	/// - a16 value in the memory pointed by 16 following bits pointed by the pc and pc+1
	/// - aR the value pointed in the memory by the register
	/// - RI means incrementation of the register
	/// - RD means decrementation of the register

	/// </summary>


	/*-------------------------------------8bits TRANSFER AND INPUT/OUTPUT INSTRUCTIONS---------------------------------------*/

	//Page 1	(p85)
	void LD_R_R(uint8_t& reg1, const uint8_t& reg2);//WORKING
	void LD_R_d8(uint8_t& reg);//WORKING
	void LD_R_aHL(uint8_t& reg);//WORKING

	//Page 2	(p86)
	void LD_aHL_R(const uint8_t& reg);//WORKING
	void LD_aHL_d8();//WORKING
	void LD_A_aBC();//WORKING
	void LD_A_aDE();//WORKING

	void LD_A_aCo();//WORKING
	void LD_aCo_A();//WORKING
	void LD_A_a8o();//WORKING NOT SURE ABOUT IF IT'S INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(pc) OR INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(memory.read(pc))
	void LD_a8o_A();//WORKING NOT SURE ...
	void LD_A_a16();//WORKING NOT SURE ABOUT THE ORDER OF THE LESS AND MOST SIGNIFICANT BITS, I THINK IT IS LOGICAL LIKE IT IS
	void LD_a16_A();//WORKING NOT SURE ABOUT THE ORDER OF THE LESS AND MOST SIGNIFICANT BITS, I THINK IT IS LOGICAL LIKE IT IS

	void LD_A_aHL_HLI();//WORKING, BUT I'M SURPRISED THE FLAGS DOESN'T CHANGE	
	void LD_A_aHL_HLD();//WORKING, BUT I'M SURPRISED THE FLAGS DOESN'T CHANGE

	//Page ?	(p99)
	void LD_aBC_A();//WORKING
	void LD_aDE_A();//WORKING
	void LD_aHL_A_HLI();//WORKING EXCEPT IF THERE'S AN ISSUE WITH THE PAIRREGISTERS AND UNPAIREGISTERS FUNCTIONS
	void LD_aHL_A_HLD();//WORKING EXCEPT IF THERE'S AN ISSUE WITH THE PAIRREGISTERS AND UNPAIREGISTERS FUNCTIONS

	void LD_RP_d16(uint8_t& reg1, uint8_t& reg2);//WORKING EXCEPT IF THE FUNCTIONS CALLING OTHERS DOESN'T WORK PROPERLY (IN PARTICULAR FOR UNPAIREGISTRES)
	void LD_RP_d16(uint16_t& regsPair);//WORKING EXCEPT IF THE FUNCTIONS CALLING OTHERS DOESN'T WORK PROPERLY (IN PARTICULAR FOR UNPAIREGISTRES)

	void LD_SP_HL();//WORKING
	void PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2);//WORKING
	void PUSH_RP(const uint8_t& regPair1, const Flag& flag);//WORING PERHAPS ISSUE WITH AF BECAUSE OF THE CONVERSION OF THE FLAG

	//Page ?	(p101)
	void POP_RP(uint8_t& regPair1, uint8_t& regPair2);//WORKING
	void POP_RP(uint8_t& regPair1, Flag& flag);//WORKING MAY HAVE A PROBLEM WITH THE CONVERSION FROM FLAG TO BYTE

	void LDHL_SP_e();//NOT SURE AT ALL PERHAPS CY AND H ARE SUPPOSED TO BE CARRY OF BIT 11 AND 15, ALSO ISSUE WHEN E NEGATIVE IS WRONG
	void LD_a16_SP();//WORKING IT SHOULD



	/*-------------------------------------8bits ARITHMETIC AND LOGICAL OPERATION INSTRUCTIONS---------------------------------------*/

	void ADD_A_R(const uint8_t& reg);//WORKING EXCEPT IF THE SUBFONCTION DOESN'T WORK
	void ADD_A_d8();//WORKING
	void ADD_A_aHL();//WORKING

	void ADC_A_R_CY(const uint8_t& reg);//WORKING IT SHOULD
	void ADC_A_d8_CY();//WORKING IT SHOULD
	void ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);//WORKING IT SHOULD

	uint8_t ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);//WORKING IT SHOULD



	void SUB_A_R(const uint8_t& reg);//WORKING EXCEPT IF THE SUBFONCTION DOESN'T WORK
	void SUB_A_d8();
	void SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2);

	void SBC_A_R_CY(const uint8_t& reg);//WORKING EXCEPT IF THE SUBFONCTION DOESN'T WORK
	void SBC_A_d8_CY();
	void SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);

	uint8_t SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);


	void AND_A_R(const uint8_t& reg);//WORKING
	void AND_A_d8();//WORKING
	void AND_A_aHL();//WORKING

	void OR_A_R(const uint8_t& reg);//WORKING
	void OR_A_d8();//WORKING
	void OR_A_aHL();//WORKING


	void XOR_A_R(const uint8_t& reg);//WORKING
	void XOR_A_d8();//WORKING
	void XOR_A_aHL();//WORKING


	////Page 11	(p95)
	void CP_A_R(const uint8_t& reg);//PERHAPS ISSUE IF CP IS IN FACT A SUBSTRACTION
	void CP_A_d8();//PERHAPS ISSUE IF CP IS IN FACT A SUBSTRACTION
	void CP_A_aHL();//PERHAPS ISSUE IF CP IS IN FACT A SUBSTRACTION
	void CP_subFunctionFlag(const uint8_t& reg);//SHOULD WORK


	void INC_R(uint8_t& reg);//WORKING
	void INC_aHL();//WORKING
	void INC_subFunctionFlag(uint8_t& reg);//WORKING

	void DEC_R(uint8_t& reg);//WORKING
	void DEC_aHL();//WORKING
	void DEC_subFunctionFlag(uint8_t& reg);//WORKING


	///*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/
	//Page 12	(p97)
	void ADD_HL_RP(const uint16_t& regsPair);//WORKING
	void ADD_HL_RP(const uint8_t& regPair1, const uint8_t& regPair2);//WORKING
	void ADD_SP_e();//NOT WORKING AT ALL
	void INC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void INC_RP(uint16_t& regsPair);
	void DEC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void DEC_RP(uint16_t& regsPair);
	int binaryAddition16bits(const int& value1, const int& value2, bool& carryBit3, bool& carryBit7);


	/*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
	//Page 13	(p98)

	//WORKING BUT MIGHT HAVE AN ISSUE WITH Z FLAG THAT MAY BE TO SET OR UNSET (the doc said no but still represent it in the calculs)
	void RLCA();
	void RLA();
	void RRCA();
	void RRA();



	//Page 14	(p99)
	void RLC_R(uint8_t& reg);//SHOULD WORK
	void RLC_aHL();
	void RL_R(uint8_t& reg);
	void RL_aHL();

	////Page 15	(p100)
	void RRC_R(uint8_t& reg);//SHOULD WORK
	void RRC_aHL();
	void RR_R(uint8_t& reg);
	void RR_aHL();

	////Page 16	(p101)
	void SLA_R(uint8_t& reg);//SHOULD WORK
	void SLA_aHL();

	void SRA_R(uint8_t& reg);
	void SRA_aHL();

	////Page 17	(p102)
	void SRL_R(uint8_t& reg);//SHOULD WORK
	void SRL_aHL();

	void SWAP_R(uint8_t& reg);//SHOULD WORK
	void SWAP_aHL();

	/*-------------------------------------BIT OPERATIONS---------------------------------------*/

	//RESUME HERE
	//Page 16	(p103)
	void BIT_b_R(const uint8_t& indexBit, const uint8_t& reg);//SHOULD WORK
	void BIT_b_aHL(const uint8_t& indexBit);

	void SET_b_R(const uint8_t& indexBit, uint8_t& reg);
	void SET_b_aHL(const uint8_t& indexBit);
	
	void RES_b_R(const uint8_t& indexBit, uint8_t& reg);
	void RES_b_aHL(const uint8_t& indexBit);


	/*-------------------------------------JUMP INSTRUCTIONS---------------------------------------*/
	
	/////////////////////////////////////TO CHECK////////////////////////////////////////////////////
	// Error, with the e in the functions
	//Page 18	(p105)
	void JP_d16();//WORKING
	void JP_cc_d16();//WORKING IT SHOULD
	void JR_e();

	////Page 19	(p106)
	void JR_cc_e();//WORKING IT SHOULD
	void JP_HL();//WORKING IT SHOULD

	/*-------------------------------------CALL AND RETURN INSTRUCTIONS---------------------------------------*/
	//Page 19	(p107)
	void CALL();//WORKING IT SHOULD
	void CALL_cc();

	////Page 20	(p108)
	void RET();
	void RETI();//TO CHECK
	void RET_cc();

	////Page 21	(p109)
	void RST();//SHOULD WORK

	/*-------------------------------------GENERAL-PURPOSE ARITHMETIC OPERATIONS AND CPU CONTROL INSTRUCTIONS---------------------------------------*/
	//Page 20	(p108)
	void DAA();//TO CHECK
	void CPL();
	void NOP();//I think it works

	void CCF();
	void SCF();

	void EI();
	void DI();

	//Page 21	(p109)
	void HALT();//NOT IMPLEMENTED
	void STOP();//NOT IMPLEMENTED

	

};

#endif
