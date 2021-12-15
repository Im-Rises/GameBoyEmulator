#ifndef DEF_CPU
#define DEF_CPU

#include "Memory.h"
#include "Ppu.h"

#define FREQUENCY_NORMAL_MODE 1.05
#define FREQUENCY_DOUBLE_SPEED_MODE 2*FREQUENCY_NORMAL_MODE 

#include <iostream>

using namespace std;

class Cpu {

private:
	int cycles;					//Cycles to do (increasse after each instructions)

	/// <summary>
	/// CPU mode
	/// </summary>
	bool halted;				//CPU is halted
	bool stopped;				//CPU is stopped
	bool resetTerminal;			//CPU terminal state
	bool onOff;					//On off button state (1:ON, 2:OFF)

	/// <summary>
	/// 8 bits registers
	/// </summary>
	uint8_t A;					//Accumulator A
	uint8_t B, C, D, E, H, L;	//Auxiliary registers of the accumulator A, they work by pairs (BC, DE, HL)

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
	/// Program Counter and Stack Pointer
	/// </summary>
	uint16_t pc;				//Program counter
	uint16_t sp;				//Stack pointer

	bool IME;					//IME flag (Interupt Master Enable)

	Memory* memory = nullptr;	//Memory of the console
	//Ppu ppu;					//PPU of the console

public:
	Cpu(Memory* memory);								//Constructor without bios
	Cpu(Memory* memory, const string& biosPath);		//Constructor with bios
	void reset();										//Reset Cpu
	void loadBios(const string& biosPath);				//Load bios
	void loadRomCompletey(const string& romPath);		//Load game
	void start();										//Start Cpu

private:
	uint16_t haltSubFunction();					//Halt mode function

	void writeUserInput();						//Function to write user inputs
	void incrementTimer();

	void readOpcode();							//Read an opcode
	void executeOpcode(uint8_t opcode);			//Execute an opcode
	void executeOpcodeFollowingCB();			//Execute an opcode on two bytes (following the CB opcode) 


	uint16_t pairRegisters(const uint8_t reg1, const uint8_t reg2)const;				//Function to pair registers
	void unpairRegisters(uint8_t& reg1, uint8_t& reg2, const uint16_t& registersPair);	//Function to unpair registers

	uint8_t flagToByte(const Flag& flag)const;//Function to convert from flag to byte
	Flag byteToFlag(const uint8_t& byte)const;//Function to convert from byte to flag

	/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

	/// <summary>
	/// Registers functions:
	/// Mnemonic therms:
	/// - R register
	/// - RP registers pair (for example HL)
	/// - d8 direct 8 bits following in the memory pointed by the pc
	/// - d16 direct 16 bits following in the memory pointed by the pc and pc+1
	/// - aRP value pointed in the memory by the registers pair value
	/// - Ro means a register + an offset
	/// - aRo means the value in the memory pointed by the address of the register + an offset
	/// - a8 value in the memory pointed by the 8 following bits pointed by the pc 
	/// - a16 value in the memory pointed by 16 following bits pointed by the pc and pc+1
	/// - aR the value pointed in the memory by the register
	/// - RI means incrementation of the register
	/// - RD means decrementation of the register

	/// </summary>


	/*-------------------------------------8bits TRANSFER AND INPUT/OUTPUT INSTRUCTIONS---------------------------------------*/

	void LD_R_R(uint8_t& reg1, const uint8_t& reg2);
	void LD_R_d8(uint8_t& reg);
	void LD_R_aHL(uint8_t& reg);
	void LD_aHL_R(const uint8_t& reg);
	void LD_aHL_d8();
	void LD_A_aBC();
	void LD_A_aDE();
	void LD_A_aCo();
	void LD_aCo_A();
	void LD_A_a8o();//WORKING NOT SURE ABOUT IF IT'S INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(pc) OR INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(memory.read(pc))
	void LD_a8o_A();//WORKING NOT SURE ...
	void LD_A_a16();
	void LD_a16_A();
	void LD_A_aHL_HLI();
	void LD_A_aHL_HLD();
	void LD_aBC_A();
	void LD_aDE_A();
	void LD_aHL_A_HLI();
	void LD_aHL_A_HLD();
	void LD_RP_d16(uint8_t& reg1, uint8_t& reg2);
	void LD_RP_d16(uint16_t& regsPair);
	void LD_SP_HL();
	void PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2);
	void PUSH_RP(const uint8_t& regPair, const Flag& flag);
	void POP_RP(uint8_t& regPair1, uint8_t& regPair2);
	void POP_RP(uint8_t& regPair1, Flag& flag);
	void LDHL_SP_e();
	void LD_a16_SP();

	/*-------------------------------------8bits ARITHMETIC AND LOGICAL OPERATION INSTRUCTIONS---------------------------------------*/
	void ADD_A_R(const uint8_t& reg);
	void ADD_A_d8();
	void ADD_A_aHL();
	void ADC_A_R_CY(const uint8_t& reg);
	void ADC_A_d8_CY();
	void ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);
	uint8_t ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);

	void SUB_A_R(const uint8_t& reg);
	void SUB_A_d8();
	void SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2);
	void SBC_A_R_CY(const uint8_t& reg);
	void SBC_A_d8_CY();
	void SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2);
	uint8_t SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value);

	void AND_A_R(const uint8_t& reg);
	void AND_A_d8();
	void AND_A_aHL();

	void OR_A_R(const uint8_t& reg);
	void OR_A_d8();
	void OR_A_aHL();

	void XOR_A_R(const uint8_t& reg);
	void XOR_A_d8();
	void XOR_A_aHL();

	void CP_A_R(const uint8_t& reg);
	void CP_A_d8();
	void CP_A_aHL();
	void CP_subFunctionFlag(const uint8_t& reg);

	void INC_R(uint8_t& reg);
	void INC_aHL();
	void INC_subFunctionFlag(uint8_t& reg);

	void DEC_R(uint8_t& reg);
	void DEC_aHL();
	void DEC_subFunctionFlag(uint8_t& reg);

	///*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/
	void ADD_HL_RP(const uint16_t& regsPair);
	void ADD_HL_RP(const uint8_t& regPair1, const uint8_t& regPair2);
	void ADD_SP_e();

	void INC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void INC_RP(uint16_t& regsPair);

	void DEC_RP(uint8_t& regPair1, uint8_t& regPair2);
	void DEC_RP(uint16_t& regsPair);

	/*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
	//WORKING BUT MIGHT HAVE AN ISSUE WITH Z FLAG THAT MAY BE TO SET OR UNSET (the doc said no but still represent it in the calculs)
	void RLCA();
	void RLA();
	void RRCA();
	void RRA();

	void RLC_R(uint8_t& reg);//SHOULD WORK
	void RLC_aHL();
	void RL_R(uint8_t& reg);
	void RL_aHL();

	void RRC_R(uint8_t& reg);//SHOULD WORK
	void RRC_aHL();
	void RR_R(uint8_t& reg);
	void RR_aHL();

	void SLA_R(uint8_t& reg);//SHOULD WORK
	void SLA_aHL();

	void SRA_R(uint8_t& reg);
	void SRA_aHL();

	void SRL_R(uint8_t& reg);//SHOULD WORK
	void SRL_aHL();

	void SWAP_R(uint8_t& reg);//SHOULD WORK
	void SWAP_aHL();

	/*-------------------------------------BIT OPERATIONS---------------------------------------*/
	void BIT_b_R(const uint8_t& indexBit, const uint8_t& reg);
	void BIT_b_aHL(const uint8_t& indexBit);

	void SET_b_R(const uint8_t& indexBit, uint8_t& reg);
	void SET_b_aHL(const uint8_t& indexBit);

	void RES_b_R(const uint8_t& indexBit, uint8_t& reg);
	void RES_b_aHL(const uint8_t& indexBit);


	/*-------------------------------------JUMP INSTRUCTIONS---------------------------------------*/
	void JP_d16();
	void JP_cc_d16();
	void JR_e();
	void JR_cc_e();
	void JP_HL();

	/*-------------------------------------CALL AND RETURN INSTRUCTIONS---------------------------------------*/
	void CALL();
	void CALL_cc();

	void RET();
	void RETI();//TO CHECK, TO IMPLEMENT THE MIE (Master Interrupt Enable)
	void RET_cc();

	void RST();

	/*-------------------------------------GENERAL-PURPOSE ARITHMETIC OPERATIONS AND CPU CONTROL INSTRUCTIONS---------------------------------------*/
	void DAA();//TO CHECK
	void CPL();
	void NOP();

	void CCF();
	void SCF();

	void EI();
	void DI();

	void HALT();
	void STOP();
};

#endif
