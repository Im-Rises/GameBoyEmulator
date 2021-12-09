#include "Cpu.h"

//Cpu::Cpu(Memory* memory)
Cpu::Cpu()
{
	//this->memory = memory;

	//ERROR NEED TO SET AN INIT VALUE FOR THE REGISTERS
	A = 0;
	B = C = D = E = H = L = 0;
	pc = ROM_DATA_AREA;
	sp = CPU_WORK_RAM_OR_AND_STACK_END;
	F.Z = F.N = F.H = F.CY = 0;
	cycles = 0;
}


Cpu::Cpu(const string& biosPath)
{
	A = 0;
	B = C = D = E = H = L = 0;
	pc = 0;
	sp = CPU_WORK_RAM_OR_AND_STACK_END;
	F.Z = F.N = F.H = F.CY = 0;
	cycles = 0;

	loadBios(biosPath);
	for (int i = 0; i < ROM_DATA_AREA; i++)
	{
		readOpcode();
	}
}

Cpu::~Cpu()
{

}

void Cpu::loadBios(const string& biosPath)
{
	//Verify size of bios
	memory.loadInMemory(biosPath);
}

void Cpu::loadRom(const string& romPath)
{
	//Verify size of rom and identify if it is a GBC or DMG game
	memory.loadInMemory(romPath);
}

void Cpu::start()
{
	while (true)
	{
		//sleap the amount of the cycle variable
		readOpcode();
	}
}

void Cpu::readOpcode()
{
	//Do sometinh here//Wait the number of cycle following the value of variable "cycles"
	executeOpcode(memory.read(pc));//Execute opcode
}


void Cpu::executeOpcode(uint8_t opcode)
{
	/// <summary>
	/// Opcode issue with number 0x7A and 0x7D because D and L have the same three bits
	/// </summary>
	/// <param name="opcode"></param>
	switch (opcode) {
	case(0x00): {NOP(); break; }
	case(0x01): {LD_RP_d16(B, C); break; }
	case(0x02): {LD_aBC_A(); break; }
	case(0x03): {INC_RP(B, C); break; }
	case(0x04): {INC_R(B); break; }
	case(0x05): {DEC_R(B); break; }
	case(0x06): {LD_R_d8(B); break; }
	case(0x07): {RLCA(); break; }
	case(0x08): {LD_a8_SP(); break; }
	case(0x09): {ADD_HL_RP(pairRegisters(B, C)); break; }
	case(0x0A): {LD_A_aBC(); break; }
	case(0x0B): {DEC_RP(B, C); break; }
	case(0x0C): {INC_R(C); break; }
	case(0x0D): {DEC_R(C); break; }
	case(0x0E): {LD_R_d8(C); break; }
	case(0x0F): {RRCA(); break; }
	case(0x10): {STOP(); cout << "Opcode STOP not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0x11): {LD_RP_d16(D, E); break; }
	case(0x12): {LD_aDE_A(); break; }
	case(0x13): {INC_RP(D, E); break; }
	case(0x14): {INC_R(D); break; }
	case(0x15): {DEC_R(D); break; }
	case(0x16): {LD_R_d8(D); break; }
	case(0x17): {RLA(); break; }
	case(0x18): {JR(); break; }
	case(0x19): {ADD_HL_RP(pairRegisters(D, E)); break; }
	case(0x1A): {LD_A_aDE(); break; }
	case(0x1B): {DEC_RP(D, E); break; }
	case(0x1C): {INC_R(E); break; }
	case(0x1D): {DEC_R(E); break; }
	case(0x1E): {LD_R_d8(E); break; }
	case(0x1F): {RRA(); break; }
	case(0x20): {JR_cc(); break; }
	case(0x21): {LD_RP_d16(H, L); break; }
	case(0x22): {LD_aHL_A_HLI(); break; }
	case(0x23): {INC_RP(H, L); break; }
	case(0x24): {INC_R(H); break; }
	case(0x25): {DEC_R(H); break; }
	case(0x26): {LD_R_d8(H); break; }
	case(0x27): {DAA(); break; }
	case(0x28): {JR_cc(); break; }
	case(0x29): {ADD_HL_RP(pairRegisters(H, L)); break; }
	case(0x2A): {LD_A_aHL_HLI(); break; }
	case(0x2B): {DEC_RP(H, L); break; }
	case(0x2C): {INC_R(L); break; }
	case(0x2D): {DEC_R(L); break; }
	case(0x2E): {LD_R_d8(L); break; }
	case(0x2F): {CPL(); break; }
	case(0x30): {JR_cc(); break; }
	case(0x31): {LD_RP_d16(sp); break; }
	case(0x32): {LD_aHL_A_HLD(); break; }
	case(0x33): {INC_RP(sp); break; }
	case(0x34): {INC_aHL(H, L); break; }
	case(0x35): {DEC_aHL(H, L); break; }
	case(0x36): {LD_aHL_d8(); break; }
	case(0x37): {cout << "Opcode SCF not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0x38): {JR_cc(); break; }
	case(0x39): {ADD_HL_RP(sp); break; }
	case(0x3A): {LD_A_aHL_HLD(); break; }
	case(0x3B): {DEC_RP(sp); break; }
	case(0x3C): {INC_R(A); break; }
	case(0x3D): {DEC_R(A); break; }
	case(0x3E): {LD_R_d8(A); break; }
	case(0x3F): {cout << "Opcode CCF not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0x40): {LD_R_R(B, B); break; }
	case(0x41): {LD_R_R(B, C); break; }
	case(0x42): {LD_R_R(B, D); break; }
	case(0x43): {LD_R_R(B, E); break; }
	case(0x44): {LD_R_R(B, H); break; }
	case(0x45): {LD_R_R(B, L); break; }
	case(0x46): {LD_R_aHL(B); break; }
	case(0x47): {LD_R_R(B, A); break; }
	case(0x48): {LD_R_R(C, B); break; }
	case(0x49): {LD_R_R(C, C); break; }
	case(0x4A): {LD_R_R(C, D); break; }
	case(0x4B): {LD_R_R(C, E); break; }
	case(0x4C): {LD_R_R(C, H); break; }
	case(0x4D): {LD_R_R(C, L); break; }
	case(0x4E): {LD_R_aHL(C); break; }
	case(0x4F): {LD_R_R(C, A); break; }
	case(0x50): {LD_R_R(D, B); break; }
	case(0x51): {LD_R_R(D, C); break; }
	case(0x52): {LD_R_R(D, D); break; }
	case(0x53): {LD_R_R(D, E); break; }
	case(0x54): {LD_R_R(D, H); break; }
	case(0x55): {LD_R_R(D, L); break; }
	case(0x56): {LD_R_aHL(D); break; }
	case(0x57): {LD_R_R(D, A); break; }
	case(0x58): {LD_R_R(E, B); break; }
	case(0x59): {LD_R_R(E, C); break; }
	case(0x5A): {LD_R_R(E, D); break; }
	case(0x5B): {LD_R_R(E, E); break; }
	case(0x5C): {LD_R_R(E, H); break; }
	case(0x5D): {LD_R_R(E, L); break; }
	case(0x5E): {LD_R_aHL(E);  break; }
	case(0x5F): {LD_R_R(E, A); break; }
	case(0x60): {LD_R_R(H, B); break; }
	case(0x61): {LD_R_R(H, C); break; }
	case(0x62): {LD_R_R(H, D); break; }
	case(0x63): {LD_R_R(H, E); break; }
	case(0x64): {LD_R_R(H, H); break; }
	case(0x65): {LD_R_R(H, L); break; }
	case(0x66): {LD_R_aHL(H); break; }
	case(0x67): {LD_R_R(H, A); break; }
	case(0x68): {LD_R_R(L, B); break; }
	case(0x69): {LD_R_R(L, C); break; }
	case(0x6A): {LD_R_R(L, D); break; }
	case(0x6B): {LD_R_R(L, E); break; }
	case(0x6C): {LD_R_R(L, H); break; }
	case(0x6D): {LD_R_R(L, L); break; }
	case(0x6E): {LD_R_aHL(L); break; }
	case(0x6F): {LD_R_R(L, A); break; }
	case(0x70): {LD_aHL_R(B); break; }
	case(0x71): {LD_aHL_R(C); break; }
	case(0x72): {LD_aHL_R(D); break; }
	case(0x73): {LD_aHL_R(E); break; }
	case(0x74): {LD_aHL_R(H); break; }
	case(0x75): {LD_aHL_R(L); break; }
	case(0x76): {HALT(); cout << "Opcode HALT not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0x77): {LD_aHL_R(A);  break; }
	case(0x78): {LD_R_R(A, B); break; }
	case(0x79): {LD_R_R(A, C); break; }
	case(0x7A): {LD_R_R(A, D); break; }
	case(0x7B): {LD_R_R(A, E); break; }
	case(0x7C): {LD_R_R(A, H); break; }
	case(0x7D): {LD_R_R(A, L); break; }
	case(0x7E): {LD_R_aHL(A); break; }
	case(0x7F): {LD_R_R(A, A); break; }
	case(0x80): {ADD_R_R(A, B); break; }
	case(0x81): {ADD_R_R(A, C); break; }
	case(0x82): {ADD_R_R(A, D); break; }
	case(0x83): {ADD_R_R(A, E); break; }
	case(0x84): {ADD_R_R(A, H); break; }
	case(0x85): {ADD_R_R(A, L); break; }
	case(0x86): {ADD_R_aRP(A, H, L); break; }
	case(0x87): {ADD_R_R(A, A); break; }
	case(0x88): {ADC_A_R_CY(B); break; }
	case(0x89): {ADC_A_R_CY(C); break; }
	case(0x8A): {ADC_A_R_CY(D); break; }
	case(0x8B): {ADC_A_R_CY(E); break; }
	case(0x8C): {ADC_A_R_CY(H); break; }
	case(0x8D): {ADC_A_R_CY(L); break; }
	case(0x8E): {ADC_A_aHL_CY(H, L); break; }
	case(0x8F): {ADC_A_R_CY(A); break; }
	case(0x90): {SUB_A_R(B); break; }
	case(0x91): {SUB_A_R(C); break; }
	case(0x92): {SUB_A_R(D); break; }
	case(0x93): {SUB_A_R(E); break; }
	case(0x94): {SUB_A_R(H); break; }
	case(0x95): {SUB_A_R(L); break; }
	case(0x96): {SUB_A_aHL(H, L); break; }
	case(0x97): {SUB_A_R(A); break; }
	case(0x98): {SBC_A_R_CY(B); break; }
	case(0x99): {SBC_A_R_CY(C); break; }
	case(0x9A): {SBC_A_R_CY(D); break; }
	case(0x9B): {SBC_A_R_CY(E); break; }
	case(0x9C): {SBC_A_R_CY(H); break; }
	case(0x9D): {SBC_A_R_CY(L); break; }
	case(0x9E): {SBC_A_aHL_CY(H, L); break; }
	case(0x9F): {SBC_A_R_CY(A); break; }
	case(0xA0): {AND_R_R(A, B); break; }
	case(0xA1): {AND_R_R(A, C); break; }
	case(0xA2): {AND_R_R(A, D); break; }
	case(0xA3): {AND_R_R(A, E); break; }
	case(0xA4): {AND_R_R(A, H); break; }
	case(0xA5): {AND_R_R(A, L); break; }
	case(0xA6): {AND_R_aHL(A, H, L); break; }
	case(0xA7): {AND_R_R(A, A); break; }
	case(0xA8): {XOR_R_R(A, B); break; }
	case(0xA9): {XOR_R_R(A, C); break; }
	case(0xAA): {XOR_R_R(A, D); break; }
	case(0xAB): {XOR_R_R(A, E); break; }
	case(0xAC): {XOR_R_R(A, H); break; }
	case(0xAD): {XOR_R_R(A, L); break; }
	case(0xAE): {XOR_R_aHL(A, H, L); break; }
	case(0xAF): {XOR_R_R(A, A); break; }
	case(0xB0): {OR_R_R(A, B); break; }
	case(0xB1): {OR_R_R(A, C); break; }
	case(0xB2): {OR_R_R(A, D); break; }
	case(0xB3): {OR_R_R(A, E); break; }
	case(0xB4): {OR_R_R(A, H); break; }
	case(0xB5): {OR_R_R(A, L); break; }
	case(0xB6): {OR_R_aHL(A, H, L); break; }
	case(0xB7): {OR_R_R(A, A); break; }
	case(0xB8): {CP_R_R(A, B); break; }
	case(0xB9): {CP_R_R(A, C); break; }
	case(0xBA): {CP_R_R(A, D); break; }
	case(0xBB): {CP_R_R(A, E); break; }
	case(0xBC): {CP_R_R(A, H); break; }
	case(0xBD): {CP_R_R(A, L); break; }
	case(0xBE): {CP_R_aHL(A, H, L); break; }
	case(0xBF): {CP_R_R(A, A); break; }
	case(0xC0): {RET_cc(); break; }
	case(0xC1): {POP_RP(B, C); break; }
	case(0xC2): {JP_cc(); break; }
	case(0xC3): {JP_d16(); break; }
	case(0xC4): {CALL_cc(); break; }
	case(0xC5): {PUSH_RP(B, C); break; }
	case(0xC6): {ADD_R_d8(A); break; }
	case(0xC7): {RST(); break; }
	case(0xC8): {RET_cc(); break; }
	case(0xC9): {RET(); break; }
	case(0xCA): {JP_cc(); break; }
	case(0xCB): {executeOpcodeFollowingCB(); break; }
	case(0xCC): {CALL_cc(); break; }
	case(0xCD): {CALL(); break; }
	case(0xCE): {ADC_A_d8_CY(); break; }
	case(0xCF): {RST(); break; }
	case(0xD0): {RET_cc(); break; }
	case(0xD1): {POP_RP(D, E); break; }
	case(0xD2): {JP_cc(); break; }
	case(0xD4): {CALL_cc(); break; }
	case(0xD5): {PUSH_RP(D, E); break; }
	case(0xD6): {SUB_A_d8(); break; }
	case(0xD7): {RST(); break; }
	case(0xD8): {RET_cc(); break; }
	case(0xD9): {RETI(); break; }
	case(0xDA): {JP_cc(); break; }
	case(0xDC): {CALL_cc(); break; }
	case(0xDE): {SBC_A_d8_CY(); break; }
	case(0xDF): {RST(); break; }
	case(0xE0): {LD_a8o_A(); break; }
	case(0xE1): {POP_RP(H, L); break; }
	case(0xE2): {LD_aCo_A(); break; }
	case(0xE5): {PUSH_RP(H, L); break; }
	case(0xE6): {AND_R_d8(A); break; }
	case(0xE7): {RST(); break; }
	case(0xE8): {ADD_SP_e(); break; }
	case(0xE9): {JP_HL(); break; }
	case(0xEA): {LD_a16_A(); break; }
	case(0xEE): {XOR_R_d8(A); break; }
	case(0xEF): {RST(); break; }
	case(0xF0): {LD_A_a8o(); break; }
	case(0xF1): {POP_RP(A, F); break; }
	case(0xF2): {LD_A_aCo(); break; }
	case(0xF3): {DI(); cout << "Opcode DI not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0xF5): {PUSH_RP(A, F); break; }
	case(0xF6): {OR_R_d8(A); break; }
	case(0xF7): {RST(); break; }
	case(0xF8): {LDHL_SP_e(); break; }
	case(0xF9): {LD_SP_HL(); break; }
	case(0xFA): {LD_A_a16(); break; }
	case(0xFB): {EI(); cout << "Opcode EI not implemented for the moment at pc = " << hex << pc << endl; break; }
	case(0xFE): {CP_R_d8(A); break; }
	case(0xFF): {RST(); break; }
	default: {cout << "Error opcode unknown read at pc = 0x" << hex << pc << endl; break; }
	}
}

void Cpu::executeOpcodeFollowingCB()
{
	pc++;
	switch (memory.read(pc)) {
	case(0x00): {RLC_R(B); break; }
	case(0x01): {RLC_R(C); break; }
	case(0x02): {RLC_R(D); break; }
	case(0x03): {RLC_R(E); break; }
	case(0x04): {RLC_R(H); break; }
	case(0x05): {RLC_R(L); break; }
	case(0x06): {RLC_aHL(); break; }
	case(0x07): {RLC_R(A); break; }
	case(0x08): {RRC_R(B); break; }
	case(0x09): {RRC_R(C); break; }
	case(0x0A): {RRC_R(D); break; }
	case(0x0B): {RRC_R(E); break; }
	case(0x0C): {RRC_R(H); break; }
	case(0x0D): {RRC_R(L); break; }
	case(0x0E): {RRC_aHL(); break; }
	case(0x0F): {RRC_R(A); break; }
	case(0x10): {RL_R(B); break; }
	case(0x11): {RL_R(C); break; }
	case(0x12): {RL_R(D); break; }
	case(0x13): {RL_R(E); break; }
	case(0x14): {RL_R(H); break; }
	case(0x15): {RL_R(L); break; }
	case(0x16): {RL_aHL(); break; }
	case(0x17): {RL_R(A); break; }
	case(0x18): {RR_R(B); break; }
	case(0x19): {RR_R(C); break; }
	case(0x1A): {RR_R(D); break; }
	case(0x1B): {RR_R(E); break; }
	case(0x1C): {RR_R(H); break; }
	case(0x1D): {RR_R(L); break; }
	case(0x1E): {RR_aHL(); break; }
	case(0x1F): {RR_R(A); break; }
	case(0x20): {SLA_R(B); break; }
	case(0x21): {SLA_R(C); break; }
	case(0x22): {SLA_R(D); break; }
	case(0x23): {SLA_R(E); break; }
	case(0x24): {SLA_R(H); break; }
	case(0x25): {SLA_R(L); break; }
	case(0x26): {SLA_aHL(); break; }
	case(0x27): {SLA_R(A); break; }
	case(0x28): {SRA_R(B); break; }
	case(0x29): {SRA_R(C); break; }
	case(0x2A): {SRA_R(D); break; }
	case(0x2B): {SRA_R(E); break; }
	case(0x2C): {SRA_R(H); break; }
	case(0x2D): {SRA_R(L); break; }
	case(0x2E): {SRA_aHL(); break; }
	case(0x2F): {SRA_R(A); break; }
	case(0x30): {SWAP_R(B); break; }
	case(0x31): {SWAP_R(C); break; }
	case(0x32): {SWAP_R(D); break; }
	case(0x33): {SWAP_R(E); break; }
	case(0x34): {SWAP_R(H); break; }
	case(0x35): {SWAP_R(L); break; }
	case(0x36): {SWAP_aHL(); break; }
	case(0x37): {SWAP_R(A); break; }
	case(0x38): {SRL_R(B); break; }
	case(0x39): {SRL_R(C); break; }
	case(0x3A): {SRL_R(D); break; }
	case(0x3B): {SRL_R(E); break; }
	case(0x3C): {SRL_R(H); break; }
	case(0x3D): {SRL_R(L); break; }
	case(0x3E): {SRL_aHL(); break; }
	case(0x3F): {SRL_R(A); break; }
	case(0x40): {BIT_R(B); break; }
	case(0x41): {BIT_R(C); break; }
	case(0x42): {BIT_R(D); break; }
	case(0x43): {BIT_R(E); break; }
	case(0x44): {BIT_R(H); break; }
	case(0x45): {BIT_R(L); break; }
	case(0x46): {BIT_aHL(); break; }
	case(0x47): {BIT_R(A); break; }
	case(0x48): {BIT_R(B); break; }
	case(0x49): {BIT_R(C); break; }
	case(0x4A): {BIT_R(D); break; }
	case(0x4B): {BIT_R(E); break; }
	case(0x4C): {BIT_R(H); break; }
	case(0x4D): {BIT_R(L); break; }
	case(0x4E): {BIT_aHL(); break; }
	case(0x4F): {BIT_R(A); break; }
	case(0x50): {BIT_R(B); break; }
	case(0x51): {BIT_R(C); break; }
	case(0x52): {BIT_R(D); break; }
	case(0x53): {BIT_R(E); break; }
	case(0x54): {BIT_R(H); break; }
	case(0x55): {BIT_R(L); break; }
	case(0x56): {BIT_aHL(); break; }
	case(0x57): {BIT_R(A); break; }
	case(0x58): {BIT_R(B); break; }
	case(0x59): {BIT_R(C); break; }
	case(0x5A): {BIT_R(D); break; }
	case(0x5B): {BIT_R(E); break; }
	case(0x5C): {BIT_R(H); break; }
	case(0x5D): {BIT_R(L); break; }
	case(0x5E): {BIT_aHL(); break; }
	case(0x5F): {BIT_R(A); break; }
	case(0x60): {BIT_R(B); break; }
	case(0x61): {BIT_R(C); break; }
	case(0x62): {BIT_R(D); break; }
	case(0x63): {BIT_R(E); break; }
	case(0x64): {BIT_R(H); break; }
	case(0x65): {BIT_R(L); break; }
	case(0x66): {BIT_aHL(); break; }
	case(0x67): {BIT_R(A); break; }
	case(0x68): {BIT_R(B); break; }
	case(0x69): {BIT_R(C); break; }
	case(0x6A): {BIT_R(D); break; }
	case(0x6B): {BIT_R(E); break; }
	case(0x6C): {BIT_R(H); break; }
	case(0x6D): {BIT_R(L); break; }
	case(0x6E): {BIT_aHL(); break; }
	case(0x6F): {BIT_R(A); break; }
	case(0x70): {BIT_R(B); break; }
	case(0x71): {BIT_R(C); break; }
	case(0x72): {BIT_R(D); break; }
	case(0x73): {BIT_R(E); break; }
	case(0x74): {BIT_R(H); break; }
	case(0x75): {BIT_R(L); break; }
	case(0x76): {BIT_aHL(); break; }
	case(0x77): {BIT_R(A); break; }
	case(0x78): {BIT_R(B); break; }
	case(0x79): {BIT_R(C); break; }
	case(0x7A): {BIT_R(D); break; }
	case(0x7B): {BIT_R(E); break; }
	case(0x7C): {BIT_R(H); break; }
	case(0x7D): {BIT_R(L); break; }
	case(0x7E): {BIT_aHL(); break; }
	case(0x7F): {BIT_R(A); break; }
	case(0x80): {RES_R(B); break; }
	case(0x81): {RES_R(C); break; }
	case(0x82): {RES_R(D); break; }
	case(0x83): {RES_R(E); break; }
	case(0x84): {RES_R(H); break; }
	case(0x85): {RES_R(L); break; }
	case(0x86): {RES_aHL(); break; }
	case(0x87): {RES_R(A); break; }
	case(0x88): {RES_R(B); break; }
	case(0x89): {RES_R(C); break; }
	case(0x8A): {RES_R(D); break; }
	case(0x8B): {RES_R(E); break; }
	case(0x8C): {RES_R(H); break; }
	case(0x8D): {RES_R(L); break; }
	case(0x8E): {RES_aHL(); break; }
	case(0x8F): {RES_R(A); break; }
	case(0x90): {RES_R(B); break; }
	case(0x91): {RES_R(C); break; }
	case(0x92): {RES_R(D); break; }
	case(0x93): {RES_R(E); break; }
	case(0x94): {RES_R(H); break; }
	case(0x95): {RES_R(L); break; }
	case(0x96): {RES_aHL(); break; }
	case(0x97): {RES_R(A); break; }
	case(0x98): {RES_R(B); break; }
	case(0x99): {RES_R(C); break; }
	case(0x9A): {RES_R(D); break; }
	case(0x9B): {RES_R(E); break; }
	case(0x9C): {RES_R(H); break; }
	case(0x9D): {RES_R(L); break; }
	case(0x9E): {RES_aHL(); break; }
	case(0x9F): {RES_R(A); break; }
	case(0xA0): {RES_R(B); break; }
	case(0xA1): {RES_R(C); break; }
	case(0xA2): {RES_R(D); break; }
	case(0xA3): {RES_R(E); break; }
	case(0xA4): {RES_R(H); break; }
	case(0xA5): {RES_R(L); break; }
	case(0xA6): {RES_aHL(); break; }
	case(0xA7): {RES_R(A); break; }
	case(0xA8): {RES_R(B); break; }
	case(0xA9): {RES_R(C); break; }
	case(0xAA): {RES_R(D); break; }
	case(0xAB): {RES_R(E); break; }
	case(0xAC): {RES_R(H); break; }
	case(0xAD): {RES_R(L); break; }
	case(0xAE): {RES_aHL(); break; }
	case(0xAF): {RES_R(A); break; }
	case(0xB0): {RES_R(B); break; }
	case(0xB1): {RES_R(C); break; }
	case(0xB2): {RES_R(D); break; }
	case(0xB3): {RES_R(E); break; }
	case(0xB4): {RES_R(H); break; }
	case(0xB5): {RES_R(L); break; }
	case(0xB6): {RES_aHL(); break; }
	case(0xB7): {RES_R(A); break; }
	case(0xB8): {RES_R(B); break; }
	case(0xB9): {RES_R(C); break; }
	case(0xBA): {RES_R(D); break; }
	case(0xBB): {RES_R(E); break; }
	case(0xBC): {RES_R(H); break; }
	case(0xBD): {RES_R(L); break; }
	case(0xBE): {RES_aHL(); break; }
	case(0xBF): {RES_R(A); break; }
	case(0xC0): {SET_R(B); break; }
	case(0xC1): {SET_R(C); break; }
	case(0xC2): {SET_R(D); break; }
	case(0xC3): {SET_R(E); break; }
	case(0xC4): {SET_R(H); break; }
	case(0xC5): {SET_R(L); break; }
	case(0xC6): {SET_aHL(); break; }
	case(0xC7): {SET_R(A); break; }
	case(0xC8): {SET_R(B); break; }
	case(0xC9): {SET_R(C); break; }
	case(0xCA): {SET_R(D); break; }
	case(0xCB): {SET_R(E); break; }
	case(0xCC): {SET_R(H); break; }
	case(0xCD): {SET_R(L); break; }
	case(0xCE): {SET_aHL(); break; }
	case(0xCF): {SET_R(A); break; }
	case(0xD0): {SET_R(B); break; }
	case(0xD1): {SET_R(C); break; }
	case(0xD2): {SET_R(D); break; }
	case(0xD3): {SET_R(E); break; }
	case(0xD4): {SET_R(H); break; }
	case(0xD5): {SET_R(L); break; }
	case(0xD6): {SET_aHL(); break; }
	case(0xD7): {SET_R(A); break; }
	case(0xD8): {SET_R(B); break; }
	case(0xD9): {SET_R(C); break; }
	case(0xDA): {SET_R(D); break; }
	case(0xDB): {SET_R(E); break; }
	case(0xDC): {SET_R(H); break; }
	case(0xDD): {SET_R(L); break; }
	case(0xDE): {SET_aHL(); break; }
	case(0xDF): {SET_R(A); break; }
	case(0xE0): {SET_R(B); break; }
	case(0xE1): {SET_R(C); break; }
	case(0xE2): {SET_R(D); break; }
	case(0xE3): {SET_R(E); break; }
	case(0xE4): {SET_R(H); break; }
	case(0xE5): {SET_R(L); break; }
	case(0xE6): {SET_aHL(); break; }
	case(0xE7): {SET_R(A); break; }
	case(0xE8): {SET_R(B); break; }
	case(0xE9): {SET_R(C); break; }
	case(0xEA): {SET_R(D); break; }
	case(0xEB): {SET_R(E); break; }
	case(0xEC): {SET_R(H); break; }
	case(0xED): {SET_R(L); break; }
	case(0xEE): {SET_aHL(); break; }
	case(0xEF): {SET_R(A); break; }
	case(0xF0): {SET_R(B); break; }
	case(0xF1): {SET_R(C); break; }
	case(0xF2): {SET_R(D); break; }
	case(0xF3): {SET_R(E); break; }
	case(0xF4): {SET_R(H); break; }
	case(0xF5): {SET_R(L); break; }
	case(0xF6): {SET_aHL(); break; }
	case(0xF7): {SET_R(A); break; }
	case(0xF8): {SET_R(B); break; }
	case(0xF9): {SET_R(C); break; }
	case(0xFA): {SET_R(D); break; }
	case(0xFB): {SET_R(E); break; }
	case(0xFC): {SET_R(H); break; }
	case(0xFD): {SET_R(L); break; }
	case(0xFE): {SET_aHL(); break; }
	case(0xFF): {SET_R(A); break; }
	default: {cout << "Error opcode after CB unknown" << endl; break; }
	}
}


/*-----------------------------------------SUB FUNCTIONS------------------------------------------*/

uint16_t Cpu::pairRegisters(const uint8_t reg1, const uint8_t reg2)const
{
	return ((reg1 << 8) + reg2);
}

void Cpu::unpairRegisters(uint8_t& reg1, uint8_t& reg2, const uint16_t& registersPair)
{
	reg1 = (registersPair >> 8) & 0x00FF;//The & 0x00FF is not an obligation
	reg2 = registersPair & 0x00FF;
}

uint8_t Cpu::flagToByte(const Flag& flag)const
{
	uint8_t temp = (flag.Z << 7) + (flag.N << 6) + (flag.H << 5) + (flag.CY << 4);
	return temp;
}


Cpu::Flag Cpu::byteToFlag(const uint8_t& byte)const
{
	Flag temp;
	temp.Z = (byte >> 7) & 0x1;
	temp.N = (byte >> 6) & 0x1;
	temp.H = (byte >> 5) & 0x1;
	temp.CY = (byte >> 4) & 0x1;
	return temp;
}


/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

/*-------------------------------------8bits TRANSFER AND INPUT/OUTPUT INSTRUCTIONS---------------------------------------*/


void Cpu::LD_R_R(uint8_t& reg1, const uint8_t& reg2) {
	reg1 = reg2;
	pc++;
	cycles++;
}

void Cpu::LD_R_d8(uint8_t& reg)
{
	pc++;
	reg = memory.read(pc);
	pc++;
	cycles += 2;
}

void Cpu::LD_R_aHL(uint8_t& reg)
{
	reg = memory.read(pairRegisters(H, L));
	pc++;
	cycles += 2;
}



void Cpu::LD_aHL_R(const uint8_t& reg)
{
	memory.write(pairRegisters(H, L), reg);
	pc++;
	cycles += 2;
}

void Cpu::LD_aHL_d8()
{
	pc++;
	memory.write(pairRegisters(H, L), memory.read(pc));
	pc++;
	cycles += 3;
}

void Cpu::LD_A_aBC()
{
	A = memory.read(pairRegisters(B, C));
	pc++;
	cycles += 2;
}

void Cpu::LD_A_aDE()
{
	A = memory.read(pairRegisters(D, E));
	pc++;
	cycles += 2;
}



void Cpu::LD_A_aCo()
{
	A = memory.read(INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + C);
	pc++;
	cycles += 2;
}

void Cpu::LD_aCo_A()
{
	memory.write((INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + C), A);
	cycles += 2;
	pc++;
}



void Cpu::LD_A_a8o()
{
	pc++;
	A = memory.read((INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(pc)));
	cycles += 3;
	pc++;
}

void Cpu::LD_a8o_A()
{
	pc++;
	memory.write(INSTRUCTION_REGISTERS_AND_SYSTEM_CONTROLLER_START + memory.read(pc), A);
	cycles += 3;
	pc++;
}

void Cpu::LD_A_a16()
{
	pc++;
	A = memory.read(((memory.read(pc + 1) << 8) + memory.read(pc)));//the n are the less significant bits, the n+1 are the most significant bits.
	cycles += 4;
	pc += 2;
}

void Cpu::LD_a16_A()
{
	pc++;
	memory.write(((memory.read(pc + 1) << 8) + memory.read(pc)), A);//the n are the less significant bits, the n+1 are the most significant bits.
	cycles += 4;
	pc += 2;
}

void Cpu::LD_A_aHL_HLI()
{
	uint16_t tempHL = pairRegisters(H, L);
	A = memory.read(tempHL);
	tempHL++;
	unpairRegisters(H, L, tempHL);
	cycles += 2;
	pc++;
}

void Cpu::LD_A_aHL_HLD()
{
	uint16_t tempHL = pairRegisters(H, L);
	A = memory.read(tempHL);
	tempHL--;
	unpairRegisters(H, L, tempHL);
	cycles += 2;
	pc++;
}

void Cpu::LD_aBC_A()
{
	memory.write(pairRegisters(B, C), A);
	cycles += 2;
	pc++;
}

void Cpu::LD_aDE_A()
{
	memory.write(pairRegisters(D, E), A);
	cycles += 2;
	pc++;
}

void Cpu::LD_aHL_A_HLI()
{
	uint16_t tempHL = pairRegisters(H, L);
	memory.write(tempHL, A);
	tempHL++;
	unpairRegisters(H, L, tempHL);
	cycles += 2;
	pc++;
}

void Cpu::LD_aHL_A_HLD()
{
	uint16_t tempHL = pairRegisters(H, L);
	memory.write(tempHL, A);
	tempHL--;
	unpairRegisters(H, L, tempHL);
	cycles += 2;
	pc++;
}


void Cpu::LD_RP_d16(uint8_t& reg1, uint8_t& reg2)
{
	pc++;
	unpairRegisters(reg1, reg2, ((memory.read(pc + 1) << 8) + memory.read(pc)));
	cycles += 3; 
	pc += 2;
}

void Cpu::LD_RP_d16(uint16_t& regsPair)
{
	pc++;
	sp = ((memory.read(pc + 1) << 8) + memory.read(pc));
	cycles += 3;
	pc += 2;
}

void Cpu::LD_SP_HL()
{
	sp = pairRegisters(H, L);
	cycles += 2;
	pc++;
}


void Cpu::PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2)
{
	memory.write(sp - 1, regPair1);
	memory.write(sp - 2, regPair2);
	sp -= 2;
	cycles += 4;
	pc++;
}

void Cpu::PUSH_RP(const uint8_t& regPair1, const Flag& flag)
{
	uint8_t flagTemp = flagToByte(flag);
	PUSH_RP(regPair1, flagTemp);
}


void Cpu::POP_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	regPair2 = memory.read(sp);
	regPair1 = memory.read(sp + 1);
	sp += 2;
	cycles += 3;
	pc++;
}

void Cpu::POP_RP(uint8_t& regPair1, Flag& flagPair)
{
	uint8_t temp = memory.read(sp);
	flagPair = byteToFlag(temp);
	regPair1 = memory.read(sp + 1);
	sp += 2;
	cycles += 3;
	pc++;
}


void Cpu::LDHL_SP_e()
{
	uint8_t e = memory.read(pc + 1);
	//Temporariry variables
	uint16_t value1Temp = sp;
	int8_t value2Temp = e;
	bool carryTemp = 0;
	uint8_t calcResultTemp = 0;

	//Variables to use after calculs
	bool carryBit11 = 0;
	bool carryBit13 = 0;
	uint16_t additionValue = 0;

	for (int i = 0; i < 16; i++)
	{
		value1Temp = (sp >> i) & 0b1;
		value2Temp = (e >> i) & 0b1;

		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
		carryTemp = (value1Temp & value2Temp) | (value1Temp & carryTemp) | (value2Temp & carryTemp);

		if ((i == 11) && carryTemp)
			carryBit11 = 1;

		if ((i == 13) && carryTemp)
			carryBit13 = 1;

		additionValue += calcResultTemp << i;
	}

	H = additionValue >> 8;
	L = additionValue & 0xFF;

	F.Z = 0;
	F.H = carryBit11;
	F.N = 0;
	F.CY = carryBit13;

	cycles += 3;
	pc++;
}


//
//void Cpu::LD_R_aRP_RPD(uint8_t& reg, uint8_t regPair1, uint8_t regPair2)
//{
//	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
//	reg = memory.read(registersPairTemp);
//	registersPairTemp--;
//	regPair1 = registersPairTemp >> 8;
//	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
//	pc++;
//}
//
//
////Page 5
//void Cpu::LD_aRP_R_RPI(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg)
//{
//	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
//	memory.write(registersPairTemp, reg);
//	registersPairTemp++;
//	regPair1 = (registersPairTemp >> 8);
//	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
//	pc++;
//}
//
//void Cpu::LD_aRP_R_RPD(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg)
//{
//	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
//	memory.write(registersPairTemp, reg);
//	registersPairTemp--;
//	regPair1 = (registersPairTemp >> 8);
//	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
//	pc++;
//}
//
//
///*-------------------------------------16bits TRANSFER INSTRUCTIONS---------------------------------------*/
//
////Page 6 
////void Cpu::LD_RP_d16(uint8_t& regPair1, uint8_t& regPair2)
////{
////	pc++;
////	regPair1 = memory.read(pc + 1);
////	regPair2 = memory.read(pc);
////	pc += 2;
////}
////
////void Cpu::LD_RP_d16(uint16_t& registersPair)
////{
////	uint8_t regPair1 = registersPair >> 8;
////	uint8_t regpair2 = registersPair & 0xFF;//HERE CONVERSION ISSUE
////	LD_RP_d16(regPair1, regpair2);
////	registersPair = (regPair1 << 8) + regpair2;
////}
//
//void Cpu::LD_RP_RP(uint16_t& registersPair, const uint8_t& regPairB1, const uint8_t& regPairB2)
//{
//	registersPair = (regPairB1 << 8);
//	registersPair = regPairB2;
//	pc++;
//}
//
//void Cpu::PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	memory.write(sp - 1, regPair1);
//	memory.write(sp - 2, regPair2);
//	sp -= 2;
//	pc++;
//}
//
//void Cpu::PUSH_RP(const uint8_t& regPair1, const Flag& flag)
//{
//	uint8_t flagTemp = flagToByte(flag);
//	PUSH_RP(regPair1, flagTemp);
//}
//
//
////Page 7

//

//
//void Cpu::LD_a8_SP()
//{
//	pc++;
//	memory.write(memory.read(pc), sp & 0xFF);;//HERE CONVERSION ISSUE
//	memory.write(memory.read(pc + 1), (sp >> 8));
//	pc += 2;
//}
//
//
///*-------------------------------------8bits ARITHMETIC AND LOGICAL OPERATION INSTRUCTIONS---------------------------------------*/
//
////Page 8
//void Cpu::ADD_R_R(uint8_t& reg1, const uint8_t& reg2)
//{
//	reg1 = ADD_ADC_subFunctionFlag(reg1, reg2);
//	pc++;
//}
//
//void Cpu::ADD_R_d8(uint8_t& reg)
//{
//	pc++;
//	reg = ADD_ADC_subFunctionFlag(reg, memory.read(pc));
//	pc++;
//}
//
//void Cpu::ADD_R_aRP(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	reg = ADD_ADC_subFunctionFlag(reg, memory.read(pairRegisters(regPair1, regPair2)));
//	pc++;
//}
//
//void Cpu::ADC_A_R_CY(const uint8_t& reg)
//{
//	A = ADD_ADC_subFunctionFlag(A, F.CY);
//	A = ADD_ADC_subFunctionFlag(A, reg);
//	pc++;
//}
//
//void Cpu::ADC_A_d8_CY()
//{
//	pc++;
//	A = ADD_ADC_subFunctionFlag(A, F.CY);
//	A = ADD_ADC_subFunctionFlag(A, memory.read(pc));
//	pc++;
//}
//
//void Cpu::ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	A = ADD_ADC_subFunctionFlag(A, F.CY);
//	A = ADD_ADC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
//	pc++;
//}
//
//
//
//uint8_t Cpu::ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
//{
//	//Variables to use after calculs
//	bool carryBit3 = 0;
//	bool carryBit7 = 0;
//	uint8_t additionValue = binaryAddition(8, reg, value, carryBit3, carryBit7);
//
//	F.Z = !reg;
//	F.H = carryBit3;
//	F.N = 0;
//	F.CY = carryBit7;
//
//	return additionValue;
//}
//
//
//int Cpu::binaryAddition(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7)
//{
//	int value1Temp = value1;
//	int value2Temp = value2;
//	bool carryTemp = 0;
//	int calcResultTemp = 0;
//
//	int additionValue = 0;
//
//	for (int i = 0; i < numberOfBits; i++)
//	{
//		value1Temp = (value1 >> i) & 0b1;
//		value2Temp = (value2 >> i) & 0b1;
//
//		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
//		carryTemp = (value1Temp & value2Temp) | (value1Temp & carryTemp) | (value2Temp & carryTemp);
//
//		if ((i == 3) && carryTemp)
//			carryBit3 = 1;
//
//		if ((i == 7) && carryTemp)
//			carryBit7 = 1;
//
//		additionValue += calcResultTemp << i;
//	}
//
//	return additionValue;
//}
//
//
//
////Page 9	
//
//void Cpu::SUB_A_R(const uint8_t& reg)
//{
//	A = SUB_SBC_subFunctionFlag(A, reg);
//	pc++;
//}
//
//void Cpu::SUB_A_d8()
//{
//	pc++;
//	A = SUB_SBC_subFunctionFlag(A, memory.read(pc));
//	pc++;
//}
//
//void Cpu::SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	A = SUB_SBC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
//	pc++;
//}
//
//
//void Cpu::SBC_A_R_CY(const uint8_t& reg)
//{
//	A = SUB_SBC_subFunctionFlag(A, F.CY);
//	A = SUB_SBC_subFunctionFlag(A, reg);
//}
//
//void Cpu::SBC_A_d8_CY()
//{
//	pc++;
//	A = SUB_SBC_subFunctionFlag(A, F.CY);
//	A = SUB_SBC_subFunctionFlag(A, memory.read(pc));
//	pc++;
//}
//
//void Cpu::SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	A = SUB_SBC_subFunctionFlag(A, F.CY);
//	A = SUB_SBC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
//}
//
//
//
//uint8_t Cpu::SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
//{
//	//Variables to use after calculs
//	bool borrowBit3 = 0;
//	bool borrowBit7 = 0;
//	uint8_t subStractionValue = binarySubstraction(8, reg, value, borrowBit3, borrowBit7);
//
//	F.Z = !reg;
//	F.H = borrowBit3;
//	F.N = 1;
//	F.CY = borrowBit7;
//
//	return subStractionValue;
//}
//
//
//int Cpu::binarySubstraction(const int& numberOfBits, const int& value1, const int& value2, bool& borrowBit3, bool& borrowBit7)
//{
//	int value1Temp = value1;
//	int value2Temp = value2;
//	bool carryTemp = 0;
//	int calcResultTemp = 0;
//
//	int substractionValue = 0;
//
//	for (int i = 0; i < numberOfBits; i++)
//	{
//		value1Temp = (value1 >> i) & 0b1;
//		value2Temp = (value2 >> i) & 0b1;
//
//		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
//		carryTemp = ((!(value1Temp ^ value2Temp)) & carryTemp) || (((!value1Temp) & value2Temp) & (!carryTemp));
//
//		if ((i == 3) && carryTemp)
//			borrowBit3 = 1;
//
//		if ((i == 7) && carryTemp)
//			borrowBit7 = 1;
//
//		substractionValue += calcResultTemp << i;
//	}
//
//	return substractionValue;
//}
//
//
//
////Page 10
//
//void Cpu::AND_R_R(uint8_t& reg1, const uint8_t& reg2)
//{
//	reg1 &= reg2;
//
//	F.Z = (reg1 == 0);
//	F.H = 1;
//	F.N = 0;
//	F.CY = 0;
//
//	pc++;
//}
//
//void Cpu::AND_R_d8(uint8_t& reg1)
//{
//	pc++;
//	reg1 &= memory.read(pc);
//	F.Z = (reg1 == 0);
//	F.H = 1;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//void Cpu::AND_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	reg &= memory.read(pairRegisters(regPair1, regPair2));
//	F.Z = (reg == 0);
//	F.H = 1;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//
//void Cpu::OR_R_R(uint8_t& reg1, const uint8_t& reg2)
//{
//	reg1 |= reg2;
//	F.Z = (reg1 == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//void Cpu::OR_R_d8(uint8_t& reg1)
//{
//	pc++;
//	reg1 |= memory.read(pc);
//	F.Z = (reg1 == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//void Cpu::OR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	reg |= memory.read(pairRegisters(regPair1, regPair2));
//	F.Z = (reg == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//
//void Cpu::XOR_R_R(uint8_t& reg1, const uint8_t& reg2)
//{
//	reg1 ^= reg2;
//	F.Z = (reg1 == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//void Cpu::XOR_R_d8(uint8_t& reg1)
//{
//	pc++;
//	reg1 ^= memory.read(pc);
//	F.Z = (reg1 == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//void Cpu::XOR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	reg ^= memory.read(pairRegisters(regPair1, regPair2));
//	F.Z = (reg == 0);
//	F.H = 0;
//	F.N = 0;
//	F.CY = 0;
//	pc++;
//}
//
//
////Page 11
//void Cpu::CP_R_R(const uint8_t& reg1, const uint8_t& reg2)
//{
//	CP_subFunctionFlag(reg1, reg2);
//	pc++;
//}
//
//void Cpu::CP_R_d8(const uint8_t& reg1)
//{
//	pc++;
//	CP_subFunctionFlag(reg1, memory.read(pc));
//	pc++;
//}
//
//void Cpu::CP_R_aHL(const uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	CP_subFunctionFlag(reg, memory.read(pairRegisters(regPair1, regPair2)));
//	pc++;
//}
//
//void Cpu::CP_subFunctionFlag(const uint8_t& reg1, const uint8_t& reg2)
//{
//	if (reg1 > reg2)
//	{
//		F.Z = 0;
//		F.H = 1;
//		F.CY = 0;
//	}
//	else if (reg1 < reg2)
//	{
//		F.Z = 0;
//		F.H = 0;
//		F.CY = 1;
//	}
//	else
//	{
//		F.Z = 1;
//		F.H = 0;
//		F.CY = 0;
//	}
//
//	F.N = 1;
//}
//
//
//void Cpu::INC_R(uint8_t& reg)
//{
//	INC_subFunctionFlag(reg);
//	pc++;
//}
//
//void Cpu::INC_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	//INC_subFunctionFlag(memory.read(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
//	uint8_t memTemp = memory.read(pairRegisters(regPair1, regPair2));
//	INC_subFunctionFlag(memTemp);
//	pc++;
//}
//
//void Cpu::INC_subFunctionFlag(uint8_t& reg)
//{
//	if (reg == 0xFF)
//	{
//		reg = 0;
//		F.Z = 1;
//		F.H = 1;
//	}
//	else
//	{
//		bool carryBit3 = false, carryBit7 = false;
//		reg = binaryAddition(8, reg, 1, carryBit3, carryBit7);
//		F.Z = 0;
//		F.H = carryBit3;
//	}
//
//	F.N = 0;
//}
//
//
//
//void Cpu::DEC_R(uint8_t& reg)
//{
//	DEC_subFunctionFlag(reg);
//	pc++;
//}
//
//void Cpu::DEC_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
//{
//	//INC_subFunctionFlag(memory.read(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
//	uint8_t memTemp = memory.read(pairRegisters(regPair1, regPair2));
//	DEC_subFunctionFlag(memTemp);
//	pc++;
//}
//
//void Cpu::DEC_subFunctionFlag(uint8_t& reg)
//{
//	if (reg == 0x00)
//	{
//		reg = 0xFF;
//		F.Z = 0;
//		F.H = 1;
//	}
//	else if (reg == 0x01)
//	{
//		reg--;
//		F.Z = 1;
//		F.H = 0;
//	}
//	else
//	{
//		bool borrowBit3 = false, borrowBit7 = false;
//		reg = binarySubstraction(8, reg, 1, borrowBit3, borrowBit7);
//		F.Z = 0;
//		F.H = borrowBit3;
//	}
//
//	F.N = 1;
//}
//
//
///*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/
//
////Page 12
//
//void Cpu::ADD_HL_RP(const uint16_t& regsPair)
//{
//	uint16_t regsPairHL = (H << 8) + L;
//	bool carryBit11 = 0;
//	bool carryBit15 = 0;
//	regsPairHL = binaryAddition16bits(regsPairHL, regsPair, carryBit11, carryBit15);
//	H = regsPairHL >> 8;
//	L = regsPairHL & 0b00001111;
//	F.H = carryBit11;
//	F.N = 0;
//	F.CY = carryBit15;
//	pc++;
//}
//
//void Cpu::ADD_SP_e()
//{
//	pc++;
//	bool carryBit11 = 0;
//	bool carryBit15 = 0;
//	uint16_t e = memory.read(pc);
//	sp = binaryAddition16bits(sp, e, carryBit11, carryBit15);
//	F.H = carryBit11;
//	F.CY = carryBit15;
//	F.N = 0;
//	F.Z = 0;
//	pc++;
//}
//
//void Cpu::INC_RP(uint8_t& regPair1, uint8_t& regPair2)
//{
//	uint16_t regsPair = pairRegisters(regPair1, regPair2);
//	regsPair++;
//	regPair1 = regsPair >> 8;
//	regPair2 = regsPair & 0b00001111;
//	pc++;
//}
//
//void Cpu::INC_RP(uint16_t& regsPair)
//{
//	regsPair++;
//	pc++;
//}
//
//void Cpu::DEC_RP(uint8_t& regPair1, uint8_t& regPair2)
//{
//	uint16_t regsPair = pairRegisters(regPair1, regPair2);
//	regsPair--;
//	regPair1 = regsPair >> 8;
//	regPair2 = regsPair & 0b00001111;
//	pc++;
//}
//
//void Cpu::DEC_RP(uint16_t& regsPair)
//{
//	regsPair--;
//	pc++;
//}
//
//
//int Cpu::binaryAddition16bits(const int& value1, const int& value2, bool& carryBit11, bool& carryBit15)
//{
//	int value1Temp = value1;
//	int value2Temp = value2;
//	bool carryTemp = 0;
//	int calcResultTemp = 0;
//
//	int additionValue = 0;
//
//	for (int i = 0; i < 16; i++)
//	{
//		value1Temp = (value1 >> i) & 0b1;
//		value2Temp = (value2 >> i) & 0b1;
//
//		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
//		carryTemp = (value1Temp & value2Temp) | (value1Temp & carryTemp) | (value2Temp & carryTemp);
//
//		if ((i == 11) && carryTemp)
//			carryBit11 = 1;
//
//		if ((i == 15) && carryTemp)
//			carryBit15 = 1;
//
//		additionValue += calcResultTemp << i;
//	}
//
//	return additionValue;
//}
//
//
//
///*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
////Page 13	(p98)
//
//
//void Cpu::RLCA()
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	F.CY = A >> 7;
//	A <<= 1;
//	A &= 0b11111110;
//	A |= F.CY;
//	pc++;
//}
//
//void Cpu::RLA()
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	bool oldCarry = F.CY;
//	F.CY = A >> 7;
//	A <<= 1;
//	A &= 0b11111110;
//	A |= oldCarry;
//	pc++;
//}
//
//
//void Cpu::RRCA()
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	F.CY = A & 0x1;
//	A >>= 1;
//	A &= 0b01111111;
//	A |= (F.CY << 7);
//	pc++;
//}
//
//void Cpu::RRA()
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	bool oldCarry = F.CY;
//	F.CY = A & 0x1;
//	A >>= 1;
//	A &= 0b01111111;
//	A |= (oldCarry << 7);
//	pc++;
//}
//
//
///*-----------------------------------------CB OPCODES OPERATIONS-----------------------------------------------*/
//
////Page 14	(p99)
//void Cpu::RLC_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	F.CY = reg >> 7;
//	reg <<= 1;
//	reg &= 0b11111110;
//	reg |= F.CY;
//	pc++;
//}
//
//void Cpu::RLC_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	F.CY = temp >> 7;
//	temp <<= 1;
//	temp &= 0b11111110;
//	temp |= F.CY;
//	memory.write(pairRegisters(H, L), temp);
//	pc++;
//}
//
//
//void Cpu::RL_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	bool oldCarry = F.CY;
//	F.CY = reg >> 7;
//	reg <<= 1;
//	reg &= 0b11111110;
//	reg |= oldCarry;
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::RL_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	F.H = 0;
//	F.N = 0;
//	bool oldCarry = F.CY;
//	F.CY = temp >> 7;
//	temp <<= 1;
//	temp &= 0b11111110;
//	temp |= oldCarry;
//	memory.write(pairRegisters(H, L), temp);
//	F.Z = (temp == 0);
//	pc++;
//}
//
//
////Page 15
//void Cpu::RRC_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.CY = reg & 0x1;
//	reg >>= 1;
//	reg &= 0b01111111;
//	reg |= (F.CY << 7);
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::RRC_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	F.CY = temp & 0x1;
//	temp >>= 1;
//	temp &= 0b01111111;
//	temp |= (F.CY << 7);
//	memory.write(pairRegisters(H, L), temp);
//	F.Z = (temp == 0);
//	pc++;
//}
//
//void Cpu::RR_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	bool oldCarry = F.CY;
//	F.CY = reg & 0x1;
//	reg >>= 1;
//	reg &= 0b01111111;
//	reg |= (oldCarry << 7);
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::RR_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	F.H = 0;
//	F.N = 0;
//	F.Z = 0;
//	bool oldCarry = F.CY;
//	F.CY = temp & 0x1;
//	temp >>= 1;
//	temp &= 0b01111111;
//	temp |= (oldCarry << 7);
//	memory.write(pairRegisters(H, L), temp);
//	F.Z = (temp == 0);
//	pc++;
//}
//
//
////Page 16
//
//void Cpu::SLA_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.CY = reg >> 7;
//	reg <<= 1;
//	reg &= 0b11111110;
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::SLA_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SLA_R(temp);
//	memory.write(pairRegisters(H, L), temp);
//}
//
//
//void Cpu::SRA_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.CY = reg & 0x1;
//	bool bit7 = reg >> 7;
//	reg >>= 1;
//	reg &= 0b01111111;
//	reg |= (bit7 << 7);
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::SRA_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SRA_R(temp);
//	memory.write(pairRegisters(H, L), temp);
//}
//
//
////Page 17
//void Cpu::SRL_R(uint8_t& reg)
//{
//	F.H = 0;
//	F.N = 0;
//	F.CY = reg & 0x1;
//	reg >>= 1;
//	reg &= 0b01111111;
//	F.Z = (reg == 0);
//	pc++;
//}
//
//void Cpu::SRL_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SRL_R(temp);
//	memory.write(pairRegisters(H, L), temp);
//}
//
//void Cpu::SWAP_R(uint8_t& reg)
//{
//	F.CY = 0;
//	F.H = 0;
//	F.N = 0;
//	uint8_t nibbleL = reg & 0x0F;
//	reg >>= 4;
//	reg &= 0x0F;
//	reg |= (nibbleL << 4);
//	F.Z = (reg == 0);
//	pc++;
//}
//void Cpu::SWAP_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SWAP_R(temp);
//	memory.write(pairRegisters(H, L), temp);
//}
//
////Page 18
//void Cpu::BIT_R(const uint8_t& reg)
//{
//	pc++;
//	F.H = 1;
//	F.N = 0;
//	uint8_t date8Bits = memory.read(pc);//Get the data byte
//	uint8_t indexBit = (date8Bits & 0b00111000) >> 3;//Get index of bit to put value in F.Z
//	F.Z = !((reg & (0b00000001 << indexBit)) >> (indexBit));//Attribute to F.Z the bit's complement of the reg pointed by the index calculated previously
//	pc++;
//}
//
//void Cpu::BIT_aHL()
//{
//	BIT_R(memory.read(pairRegisters(H, L)));
//}
//
//void Cpu::SET_R(uint8_t& reg)
//{
//	pc++;
//	uint8_t date8Bits = memory.read(pc);//Get the data byte
//	uint8_t indexBit = (date8Bits & 0b00111000) >> 3;//Get index of bit to set in register
//	reg |= (0b00000001 << indexBit);//Se the bit pointed by the index calculated previously
//	pc++;
//}
//
//
////Page 17
//void Cpu::SET_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SET_R(temp);
//}
//
//
//void Cpu::RES_R(uint8_t& reg)
//{
//	pc++;
//	uint8_t date8Bits = memory.read(pc);//Get the data byte
//	uint8_t indexBit = (date8Bits & 0b00111000) >> 3;//Get index of bit to set in register
//	uint8_t masque = (0b11111110 << indexBit);//Set the bit pointed by the index calculated previously
//	for (int i = 0; i < indexBit; i++)//Set the bits put to 0 during the bit shifting above
//	{
//		masque += (0x1 << i);
//	}
//	reg &= masque;
//	pc++;
//}
//
//void Cpu::RES_aHL()
//{
//	uint8_t temp = memory.read(pairRegisters(H, L));
//	SET_R(temp);
//}
//
///*-------------------------------------JUMP INSTRUCTIONS---------------------------------------*/
////Page 18
//
//void Cpu::JP_d16()
//{
//	pc++;
//	pc = (memory.read(pc + 1) << 8) + (memory.read(pc));
//}
//
//void Cpu::JP_cc()
//{
//	uint8_t opcode = memory.read(pc);
//	uint8_t condition = ((opcode & 0b00011000) >> 3);
//	pc++;
//	uint8_t lowByte = memory.read(pc);
//	pc++;
//	uint8_t highByte = memory.read(pc);
//
//	switch (condition)
//	{
//	case(0b00)://NZ
//	{
//		if (!F.Z)
//		{
//			pc = (highByte << 8) + lowByte;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b01)://Z
//	{
//		if (F.Z)
//		{
//			pc = (highByte << 8) + lowByte;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b10)://NC
//	{
//		if (!F.CY)
//		{
//			pc = (highByte << 8) + lowByte;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b11)://C
//	{
//		if (F.CY)
//		{
//			pc = (highByte << 8) + lowByte;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	}
//}
//
//void Cpu::JR()
//{
//	pc++;
//	int8_t e = memory.read(pc);
//	pc += e + 2;
//}
//
//
//void Cpu::JR_cc()
//{
//	uint8_t opcode = memory.read(pc);
//	uint8_t condition = ((opcode & 0b00011000) >> 3);
//	pc++;
//	int8_t e = memory.read(pc);
//
//	switch (condition)
//	{
//	case(0b00)://NZ
//	{
//		if (!F.Z)
//		{
//			pc += e + 2;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b01)://Z
//	{
//		if (F.Z)
//		{
//			pc += e + 2;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b10)://NC
//	{
//		if (!F.CY)
//		{
//			pc += e + 2;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b11)://C
//	{
//		if (F.CY)
//		{
//			pc += e + 2;
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	}
//}
//
//void Cpu::JP_HL()
//{
//	pc = pairRegisters(H, L);
//}
//
//void Cpu::CALL()
//{
//	memory.write(sp - 1, ((pc + 3) >> 8));
//	memory.write(sp - 2, ((pc + 3) & 0x0F));
//	pc = (memory.read(pc + 1) << 8) + memory.read(pc + 2);
//	sp -= 2;
//}
//
//void Cpu::CALL_cc()
//{
//	uint8_t opcode = memory.read(pc);
//	uint8_t condition = ((opcode & 0b00011000) >> 3);
//
//	switch (condition)
//	{
//	case(0b00)://NZ
//	{
//		if (!F.Z)
//		{
//			CALL();
//		}
//		else
//		{
//			pc += 3;
//		}
//		break;
//	}
//	case(0b01)://Z
//	{
//		if (F.Z)
//		{
//			CALL();
//		}
//		else
//		{
//			pc += 3;
//		}
//		break;
//	}
//	case(0b10)://NC
//	{
//		if (!F.CY)
//		{
//			CALL();
//		}
//		else
//		{
//			pc += 3;
//		}
//		break;
//	}
//	case(0b11)://C
//	{
//		if (F.CY)
//		{
//			CALL();
//		}
//		else
//		{
//			pc += 3;
//		}
//		break;
//	}
//	}
//}
//
//void Cpu::RET()
//{
//	pc = (memory.read(sp + 1) << 8) + memory.read(sp);
//	sp += 2;
//}
//
//void Cpu::RETI()
//{
//	pc = (memory.read(sp + 1) << 8) + memory.read(sp);
//	sp += 2;
//}
//
//
//void Cpu::RET_cc()
//{
//	uint8_t opcode = memory.read(pc);
//	uint8_t condition = ((opcode & 0b00011000) >> 3);
//
//	switch (condition)
//	{
//	case(0b00)://NZ
//	{
//		if (!F.Z)
//		{
//			RET();
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b01)://Z
//	{
//		if (F.Z)
//		{
//			RET();
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b10)://NC
//	{
//		if (!F.CY)
//		{
//			RET();
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	case(0b11)://C
//	{
//		if (F.CY)
//		{
//			RET();
//		}
//		else
//		{
//			pc++;
//		}
//		break;
//	}
//	}
//}
//
////Page 21
//void Cpu::RST()
//{
//	uint8_t opcode = memory.read(pc);
//	pc++;
//	memory.write(sp - 1, (pc >> 8));
//	memory.write(sp - 2, (pc & 0x0F));
//	sp -= 2;
//
//	uint8_t condition = ((opcode & 0b00111000) >> 3);
//
//	switch (condition)
//	{
//	case(0b000):
//	{
//		pc = 0x0000;
//		break;
//	}
//	case(0b001):
//	{
//		pc = 0x0008;
//		break;
//	}
//	case(0b010):
//	{
//		pc = 0x0010;
//		break;
//	}
//	case(0b011):
//	{
//		pc = 0x0018;
//	}
//	case(0b100):
//	{
//		pc = 0x0020;
//		break;
//	}
//	case(0b101):
//	{
//		pc = 0x0028;
//		break;
//	}
//	case(0b110):
//	{
//		pc = 0x0030;
//		break;
//	}
//	case(0b111):
//	{
//		pc = 0x0038;
//		break;
//	}
//	}
//}
//
//
///*-------------------------------------GENERAL-PURPOSE ARITHMETIC OPERATIONS AND CPU CONTROL INSTRUCTIONS---------------------------------------*/
////Page 20
//void Cpu::DAA()
//{
//	if (!F.N)//If previsous opcode is one of the ADD opcodes
//	{
//		if (((A & 0xF0) > 0x90) || F.CY)
//		{
//			A += 0x60;
//			F.CY = 1;
//		}
//		else
//		{
//			F.CY = 0;
//		}
//
//		if (((A & 0x0F) > 0x09) || F.H)
//		{
//			A += 0x06;
//		}
//	}
//	else//If previsous opcode is one of the SUB opcodes
//	{
//		if (((A & 0xF0) > 0x90) || F.CY)
//		{
//			A -= 0x60;
//			F.CY = 1;
//		}
//		else
//		{
//			F.CY = 0;
//		}
//
//		if (((A & 0x0F) > 0x09) || F.H)
//		{
//			A -= 0x06;
//		}
//	}
//
//	F.H = 0;
//	F.Z = (A == 0);
//	pc++;
//}
//
//
//void Cpu::CPL()
//{
//	A = ~A;
//	F.H = 1;
//	F.N = 1;
//	pc++;
//}
//
//
//void Cpu::NOP()
//{
//	pc++;
//}
//
////Page 21
//void Cpu::HALT()//NOT IMPLEMENTED
//{
//	pc++;
//}
//
//void Cpu::STOP()//NOT IMPLEMENTED
//{
//	pc++;
//}
//
//void Cpu::EI()
//{
//	pc++;
//}
//
//void Cpu::DI()
//{
//	pc++;
//}
//
