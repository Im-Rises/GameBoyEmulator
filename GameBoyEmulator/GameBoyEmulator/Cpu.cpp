#include "Cpu.h"

//Cpu::Cpu(Memory* memory)
Cpu::Cpu()
{
	//this->memory = memory;
	//ERROR NEED TO SET AN INIT VALUE FOR THE REGISTERS AFTER THE BIOS
	reset();
	pc = ROM_DATA_AREA;
	sp = CPU_WORK_RAM_OR_AND_STACK_END;
	IME = 0;
}


Cpu::Cpu(const string& biosPath)
{
	reset();
	pc = 0x0000;
	sp = 0x0000;
	IME = 0;
	loadBios(biosPath);
}

Cpu::~Cpu()
{

}

void Cpu::reset()
{
	cycles = 0;
	halted = 0;
	resetTerminal = 1;
	onOff = 1;
	stopped = 0;
	A = 0;
	B = C = D = E = H = L = 0;
	F.Z = F.N = F.H = F.CY = 0;
	memory.reset();
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
	while (onOff)
	{
		//Wait the number of cycles
		cycles = 0;
		//sleap the amount of the cycle variable


		if (true)//DEBUG
		{
			if (pc == 0x64)
				cout << "Arret pc = " << hex << pc << endl;
			cout << "pc = 0x" << hex << pc << endl;
		}


		if (!halted && !stopped)//If CPU is not in halt mode neither stop mode
		{
			readOpcode();
		}
		else if (halted)//If halt mode is enable
		{
			cycles++;
			//HALT mode is canceled by the following events, which have the starting addresses
			//	indicated.
			//	1) A LOW signal to the / RESET terminal
			//	Starting address : 0000h
			//	2) The interrupt - enable flag and its corresponding interrupt request flag are set
			//	IME = 0 (Interrupt Master Enable flag disabled)
			//	Starting address : address following that of the HALT instruction
			//	IME = 1 (Interrupt Master Enable flag enabled)
			//	Starting address : each interrupt starting address

			if ()
			{
				halted = false;
				if (IME)
				{
					halted = false;
					//pc=interrupt starting address
				}
				//else
				//{
				//	pc = pc;
				//}
			}
		}
		else//If stop mode is enable
		{
			cycles++;
			//STOP Mode
			//	Game Boy switches to STOP mode when a STOP instruction is executed.
			//	The system clockand oscillation circuitry between the CK1and CK2 terminals are halted in
			//	this mode.Thus, all operation is halted except that of the SI0 external clock.STOP mode is
			//	canceled by the following events, and started from the starting address.
			//	3) A LOW signal to the / RESET terminal
			//	Starting address : 0000h
			//	4) A LOW signal to terminal P10, P11, P12, or P13
			//	Starting address : address following that of STOP instruction
			//	When STOP mode is canceled, the system clock is restored after 217 times the oscillation
			//	clock(DMG : 4 MHz, CGB : 4 MHz / 8 MHz), and the CPU resumes operation.
			//	When STOP mode is entered, the STOP instruction should be executed after all interruptenable
			//	flags are reset, and meanwhile, terminals P10 - P13 are all in a HIGH period.
		}

		if (!resetTerminal)
		{
			reset();
		}
	}
}

void Cpu::readOpcode()
{
	//Do sometinh here//Wait the number of cycle following the value of variable "cycles"
	executeOpcode(memory.read(pc));//Execute opcode
}


void Cpu::executeOpcode(uint8_t opcode)
{
	switch (opcode) {
	case(0x00): {NOP(); break; }
	case(0x01): {LD_RP_d16(B, C); break; }
	case(0x02): {LD_aBC_A(); break; }
	case(0x03): {INC_RP(B, C); break; }
	case(0x04): {INC_R(B); break; }
	case(0x05): {DEC_R(B); break; }
	case(0x06): {LD_R_d8(B); break; }
	case(0x07): {RLCA(); break; }
	case(0x08): {LD_a16_SP(); break; }
	case(0x09): {ADD_HL_RP(B, C); break; }
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
	case(0x18): {JR_e(); break; }
	case(0x19): {ADD_HL_RP(D, E); break; }
	case(0x1A): {LD_A_aDE(); break; }
	case(0x1B): {DEC_RP(D, E); break; }
	case(0x1C): {INC_R(E); break; }
	case(0x1D): {DEC_R(E); break; }
	case(0x1E): {LD_R_d8(E); break; }
	case(0x1F): {RRA(); break; }
	case(0x20): {JR_cc_e(); break; }
	case(0x21): {LD_RP_d16(H, L); break; }
	case(0x22): {LD_aHL_A_HLI(); break; }
	case(0x23): {INC_RP(H, L); break; }
	case(0x24): {INC_R(H); break; }
	case(0x25): {DEC_R(H); break; }
	case(0x26): {LD_R_d8(H); break; }
	case(0x27): {DAA(); break; }
	case(0x28): {JR_cc_e(); break; }
	case(0x29): {ADD_HL_RP(H, L); break; }
	case(0x2A): {LD_A_aHL_HLI(); break; }
	case(0x2B): {DEC_RP(H, L); break; }
	case(0x2C): {INC_R(L); break; }
	case(0x2D): {DEC_R(L); break; }
	case(0x2E): {LD_R_d8(L); break; }
	case(0x2F): {CPL(); break; }
	case(0x30): {JR_cc_e(); break; }
	case(0x31): {LD_RP_d16(sp); break; }
	case(0x32): {LD_aHL_A_HLD(); break; }
	case(0x33): {INC_RP(sp); break; }
	case(0x34): {INC_aHL(); break; }
	case(0x35): {DEC_aHL(); break; }
	case(0x36): {LD_aHL_d8(); break; }
	case(0x37): {SCF(); break; }
	case(0x38): {JR_cc_e(); break; }
	case(0x39): {ADD_HL_RP(sp); break; }
	case(0x3A): {LD_A_aHL_HLD(); break; }
	case(0x3B): {DEC_RP(sp); break; }
	case(0x3C): {INC_R(A); break; }
	case(0x3D): {DEC_R(A); break; }
	case(0x3E): {LD_R_d8(A); break; }
	case(0x3F): {CCF(); break; }
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
	case(0x76): {HALT(); break; }
	case(0x77): {LD_aHL_R(A);  break; }
	case(0x78): {LD_R_R(A, B); break; }
	case(0x79): {LD_R_R(A, C); break; }
	case(0x7A): {LD_R_R(A, D); break; }
	case(0x7B): {LD_R_R(A, E); break; }
	case(0x7C): {LD_R_R(A, H); break; }
	case(0x7D): {LD_R_R(A, L); break; }
	case(0x7E): {LD_R_aHL(A); break; }
	case(0x7F): {LD_R_R(A, A); break; }
	case(0x80): {ADD_A_R(B); break; }
	case(0x81): {ADD_A_R(C); break; }
	case(0x82): {ADD_A_R(D); break; }
	case(0x83): {ADD_A_R(E); break; }
	case(0x84): {ADD_A_R(H); break; }
	case(0x85): {ADD_A_R(L); break; }
	case(0x86): {ADD_A_aHL(); break; }
	case(0x87): {ADD_A_R(A); break; }
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
	case(0xA0): {AND_A_R(B); break; }
	case(0xA1): {AND_A_R(C); break; }
	case(0xA2): {AND_A_R(D); break; }
	case(0xA3): {AND_A_R(E); break; }
	case(0xA4): {AND_A_R(H); break; }
	case(0xA5): {AND_A_R(L); break; }
	case(0xA6): {AND_A_aHL(); break; }
	case(0xA7): {AND_A_R(A); break; }
	case(0xA8): {XOR_A_R(B); break; }
	case(0xA9): {XOR_A_R(C); break; }
	case(0xAA): {XOR_A_R(D); break; }
	case(0xAB): {XOR_A_R(E); break; }
	case(0xAC): {XOR_A_R(H); break; }
	case(0xAD): {XOR_A_R(L); break; }
	case(0xAE): {XOR_A_aHL(); break; }
	case(0xAF): {XOR_A_R(A); break; }
	case(0xB0): {OR_A_R(B); break; }
	case(0xB1): {OR_A_R(C); break; }
	case(0xB2): {OR_A_R(D); break; }
	case(0xB3): {OR_A_R(E); break; }
	case(0xB4): {OR_A_R(H); break; }
	case(0xB5): {OR_A_R(L); break; }
	case(0xB6): {OR_A_aHL(); break; }
	case(0xB7): {OR_A_R(A);  break; }
	case(0xB8): {CP_A_R(B); break; }
	case(0xB9): {CP_A_R(C); break; }
	case(0xBA): {CP_A_R(D); break; }
	case(0xBB): {CP_A_R(E); break; }
	case(0xBC): {CP_A_R(H); break; }
	case(0xBD): {CP_A_R(L); break; }
	case(0xBE): {CP_A_aHL(); break; }
	case(0xBF): {CP_A_R(A); break; }
	case(0xC0): {RET_cc(); break; }
	case(0xC1): {POP_RP(B, C); break; }
	case(0xC2): {JP_cc_d16(); break; }
	case(0xC3): {JP_d16(); break; }
	case(0xC4): {CALL_cc(); break; }
	case(0xC5): {PUSH_RP(B, C); break; }
	case(0xC6): {ADD_A_d8(); break; }
	case(0xC7): {RST(); break; }
	case(0xC8): {RET_cc(); break; }
	case(0xC9): {RET(); break; }
	case(0xCA): {JP_cc_d16(); break; }
	case(0xCB): {executeOpcodeFollowingCB(); break; }
	case(0xCC): {CALL_cc(); break; }
	case(0xCD): {CALL(); break; }
	case(0xCE): {ADC_A_d8_CY(); break; }
	case(0xCF): {RST(); break; }
	case(0xD0): {RET_cc(); break; }
	case(0xD1): {POP_RP(D, E); break; }
	case(0xD2): {JP_cc_d16(); break; }
	case(0xD4): {CALL_cc(); break; }
	case(0xD5): {PUSH_RP(D, E); break; }
	case(0xD6): {SUB_A_d8(); break; }
	case(0xD7): {RST(); break; }
	case(0xD8): {RET_cc(); break; }
	case(0xD9): {RETI(); break; }
	case(0xDA): {JP_cc_d16(); break; }
	case(0xDC): {CALL_cc(); break; }
	case(0xDE): {SBC_A_d8_CY(); break; }
	case(0xDF): {RST(); break; }
	case(0xE0): {LD_a8o_A(); break; }
	case(0xE1): {POP_RP(H, L); break; }
	case(0xE2): {LD_aCo_A(); break; }
	case(0xE5): {PUSH_RP(H, L); break; }
	case(0xE6): {AND_A_d8(); break; }
	case(0xE7): {RST(); break; }
	case(0xE8): {ADD_SP_e(); break; }
	case(0xE9): {JP_HL(); break; }
	case(0xEA): {LD_a16_A(); break; }
	case(0xEE): {XOR_A_d8(); break; }
	case(0xEF): {RST(); break; }
	case(0xF0): {LD_A_a8o(); break; }
	case(0xF1): {POP_RP(A, F); break; }
	case(0xF2): {LD_A_aCo(); break; }
	case(0xF3): {DI(); break; }
	case(0xF5): {PUSH_RP(A, F); break; }
	case(0xF6): {OR_A_d8(); break; }
	case(0xF7): {RST(); break; }
	case(0xF8): {LDHL_SP_e(); break; }
	case(0xF9): {LD_SP_HL(); break; }
	case(0xFA): {LD_A_a16(); break; }
	case(0xFB): {EI(); break; }
	case(0xFE): {CP_A_d8(); break; }
	case(0xFF): {RST(); break; }
	default: {cout << "Error opcode 0x" << opcode << " unknown at pc = 0x" << hex << pc << endl; exit(1); break; }
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
	case(0x40): {BIT_b_R(0, B); break; }
	case(0x41): {BIT_b_R(0, C); break; }
	case(0x42): {BIT_b_R(0, D); break; }
	case(0x43): {BIT_b_R(0, E); break; }
	case(0x44): {BIT_b_R(0, H); break; }
	case(0x45): {BIT_b_R(0, L); break; }
	case(0x46): {BIT_b_aHL(0); break; }
	case(0x47): {BIT_b_R(0, A); break; }
	case(0x48): {BIT_b_R(1, B); break; }
	case(0x49): {BIT_b_R(1, C); break; }
	case(0x4A): {BIT_b_R(1, D); break; }
	case(0x4B): {BIT_b_R(1, E); break; }
	case(0x4C): {BIT_b_R(1, H); break; }
	case(0x4D): {BIT_b_R(1, L); break; }
	case(0x4E): {BIT_b_aHL(1); break; }
	case(0x4F): {BIT_b_R(1, A); break; }
	case(0x50): {BIT_b_R(2, B); break; }
	case(0x51): {BIT_b_R(2, C); break; }
	case(0x52): {BIT_b_R(2, D); break; }
	case(0x53): {BIT_b_R(2, E); break; }
	case(0x54): {BIT_b_R(2, H); break; }
	case(0x55): {BIT_b_R(2, L); break; }
	case(0x56): {BIT_b_aHL(2); break; }
	case(0x57): {BIT_b_R(2, A); break; }
	case(0x58): {BIT_b_R(3, B); break; }
	case(0x59): {BIT_b_R(3, C); break; }
	case(0x5A): {BIT_b_R(3, D); break; }
	case(0x5B): {BIT_b_R(3, E); break; }
	case(0x5C): {BIT_b_R(3, H); break; }
	case(0x5D): {BIT_b_R(3, L); break; }
	case(0x5E): {BIT_b_aHL(3); break; }
	case(0x5F): {BIT_b_R(3, A); break; }
	case(0x60): {BIT_b_R(4, B); break; }
	case(0x61): {BIT_b_R(4, C); break; }
	case(0x62): {BIT_b_R(4, D); break; }
	case(0x63): {BIT_b_R(4, E); break; }
	case(0x64): {BIT_b_R(4, H); break; }
	case(0x65): {BIT_b_R(4, L); break; }
	case(0x66): {BIT_b_aHL(4); break; }
	case(0x67): {BIT_b_R(4, A); break; }
	case(0x68): {BIT_b_R(5, B); break; }
	case(0x69): {BIT_b_R(5, C); break; }
	case(0x6A): {BIT_b_R(5, D); break; }
	case(0x6B): {BIT_b_R(5, E); break; }
	case(0x6C): {BIT_b_R(5, H); break; }
	case(0x6D): {BIT_b_R(5, L); break; }
	case(0x6E): {BIT_b_aHL(5); break; }
	case(0x6F): {BIT_b_R(5, A); break; }
	case(0x70): {BIT_b_R(6, B); break; }
	case(0x71): {BIT_b_R(6, C); break; }
	case(0x72): {BIT_b_R(6, D); break; }
	case(0x73): {BIT_b_R(6, E); break; }
	case(0x74): {BIT_b_R(6, H); break; }
	case(0x75): {BIT_b_R(6, L); break; }
	case(0x76): {BIT_b_aHL(6); break; }
	case(0x77): {BIT_b_R(6, A); break; }
	case(0x78): {BIT_b_R(7, B); break; }
	case(0x79): {BIT_b_R(7, C); break; }
	case(0x7A): {BIT_b_R(7, D); break; }
	case(0x7B): {BIT_b_R(7, E); break; }
	case(0x7C): {BIT_b_R(7, H); break; }
	case(0x7D): {BIT_b_R(7, L); break; }
	case(0x7E): {BIT_b_aHL(7); break; }
	case(0x7F): {BIT_b_R(7, A); break; }
	case(0x80): {RES_b_R(0, B); break; }
	case(0x81): {RES_b_R(0, C); break; }
	case(0x82): {RES_b_R(0, D); break; }
	case(0x83): {RES_b_R(0, E); break; }
	case(0x84): {RES_b_R(0, H); break; }
	case(0x85): {RES_b_R(0, L); break; }
	case(0x86): {RES_b_aHL(0); break; }
	case(0x87): {RES_b_R(0, A); break; }
	case(0x88): {RES_b_R(1, B); break; }
	case(0x89): {RES_b_R(1, C); break; }
	case(0x8A): {RES_b_R(1, D); break; }
	case(0x8B): {RES_b_R(1, E); break; }
	case(0x8C): {RES_b_R(1, H); break; }
	case(0x8D): {RES_b_R(1, L); break; }
	case(0x8E): {RES_b_aHL(1); break; }
	case(0x8F): {RES_b_R(1, A); break; }
	case(0x90): {RES_b_R(2, B); break; }
	case(0x91): {RES_b_R(2, C); break; }
	case(0x92): {RES_b_R(2, D); break; }
	case(0x93): {RES_b_R(2, E); break; }
	case(0x94): {RES_b_R(2, H); break; }
	case(0x95): {RES_b_R(2, L); break; }
	case(0x96): {RES_b_aHL(2); break; }
	case(0x97): {RES_b_R(2, A); break; }
	case(0x98): {RES_b_R(3, B); break; }
	case(0x99): {RES_b_R(3, C); break; }
	case(0x9A): {RES_b_R(3, D); break; }
	case(0x9B): {RES_b_R(3, E); break; }
	case(0x9C): {RES_b_R(3, H); break; }
	case(0x9D): {RES_b_R(3, L); break; }
	case(0x9E): {RES_b_aHL(3); break; }
	case(0x9F): {RES_b_R(3, A); break; }
	case(0xA0): {RES_b_R(4, B); break; }
	case(0xA1): {RES_b_R(4, C); break; }
	case(0xA2): {RES_b_R(4, D); break; }
	case(0xA3): {RES_b_R(4, E); break; }
	case(0xA4): {RES_b_R(4, H); break; }
	case(0xA5): {RES_b_R(4, L); break; }
	case(0xA6): {RES_b_aHL(4); break; }
	case(0xA7): {RES_b_R(4, A); break; }
	case(0xA8): {RES_b_R(5, B); break; }
	case(0xA9): {RES_b_R(5, C); break; }
	case(0xAA): {RES_b_R(5, D); break; }
	case(0xAB): {RES_b_R(5, E); break; }
	case(0xAC): {RES_b_R(5, H); break; }
	case(0xAD): {RES_b_R(5, L); break; }
	case(0xAE): {RES_b_aHL(5); break; }
	case(0xAF): {RES_b_R(5, A); break; }
	case(0xB0): {RES_b_R(6, B); break; }
	case(0xB1): {RES_b_R(6, C); break; }
	case(0xB2): {RES_b_R(6, D); break; }
	case(0xB3): {RES_b_R(6, E); break; }
	case(0xB4): {RES_b_R(6, H); break; }
	case(0xB5): {RES_b_R(6, L); break; }
	case(0xB6): {RES_b_aHL(6); break; }
	case(0xB7): {RES_b_R(6, A); break; }
	case(0xB8): {RES_b_R(7, B); break; }
	case(0xB9): {RES_b_R(7, C); break; }
	case(0xBA): {RES_b_R(7, D); break; }
	case(0xBB): {RES_b_R(7, E); break; }
	case(0xBC): {RES_b_R(7, H); break; }
	case(0xBD): {RES_b_R(7, L); break; }
	case(0xBE): {RES_b_aHL(7); break; }
	case(0xBF): {RES_b_R(7, A); break; }
	case(0xC0): {SET_b_R(0, B); break; }
	case(0xC1): {SET_b_R(0, C); break; }
	case(0xC2): {SET_b_R(0, D); break; }
	case(0xC3): {SET_b_R(0, E); break; }
	case(0xC4): {SET_b_R(0, H); break; }
	case(0xC5): {SET_b_R(0, L); break; }
	case(0xC6): {SET_b_aHL(0); break; }
	case(0xC7): {SET_b_R(0, A); break; }
	case(0xC8): {SET_b_R(1, B); break; }
	case(0xC9): {SET_b_R(1, C); break; }
	case(0xCA): {SET_b_R(1, D); break; }
	case(0xCB): {SET_b_R(1, E); break; }
	case(0xCC): {SET_b_R(1, H); break; }
	case(0xCD): {SET_b_R(1, L); break; }
	case(0xCE): {SET_b_aHL(1); break; }
	case(0xCF): {SET_b_R(1, A); break; }
	case(0xD0): {SET_b_R(2, B); break; }
	case(0xD1): {SET_b_R(2, C); break; }
	case(0xD2): {SET_b_R(2, D); break; }
	case(0xD3): {SET_b_R(2, E); break; }
	case(0xD4): {SET_b_R(2, H); break; }
	case(0xD5): {SET_b_R(2, L); break; }
	case(0xD6): {SET_b_aHL(2); break; }
	case(0xD7): {SET_b_R(2, A); break; }
	case(0xD8): {SET_b_R(3, B); break; }
	case(0xD9): {SET_b_R(3, C); break; }
	case(0xDA): {SET_b_R(3, D); break; }
	case(0xDB): {SET_b_R(3, E); break; }
	case(0xDC): {SET_b_R(3, H); break; }
	case(0xDD): {SET_b_R(3, L); break; }
	case(0xDE): {SET_b_aHL(3); break; }
	case(0xDF): {SET_b_R(3, A); break; }
	case(0xE0): {SET_b_R(4, B); break; }
	case(0xE1): {SET_b_R(4, C); break; }
	case(0xE2): {SET_b_R(4, D); break; }
	case(0xE3): {SET_b_R(4, E); break; }
	case(0xE4): {SET_b_R(4, H); break; }
	case(0xE5): {SET_b_R(4, L); break; }
	case(0xE6): {SET_b_aHL(4); break; }
	case(0xE7): {SET_b_R(4, A); break; }
	case(0xE8): {SET_b_R(5, B); break; }
	case(0xE9): {SET_b_R(5, C); break; }
	case(0xEA): {SET_b_R(5, D); break; }
	case(0xEB): {SET_b_R(5, E); break; }
	case(0xEC): {SET_b_R(5, H); break; }
	case(0xED): {SET_b_R(5, L); break; }
	case(0xEE): {SET_b_aHL(5); break; }
	case(0xEF): {SET_b_R(5, A); break; }
	case(0xF0): {SET_b_R(6, B); break; }
	case(0xF1): {SET_b_R(6, C); break; }
	case(0xF2): {SET_b_R(6, D); break; }
	case(0xF3): {SET_b_R(6, E); break; }
	case(0xF4): {SET_b_R(6, H); break; }
	case(0xF5): {SET_b_R(6, L); break; }
	case(0xF6): {SET_b_aHL(6); break; }
	case(0xF7): {SET_b_R(6, A); break; }
	case(0xF8): {SET_b_R(7, B); break; }
	case(0xF9): {SET_b_R(7, C); break; }
	case(0xFA): {SET_b_R(7, D); break; }
	case(0xFB): {SET_b_R(7, E); break; }
	case(0xFC): {SET_b_R(7, H); break; }
	case(0xFD): {SET_b_R(7, L); break; }
	case(0xFE): {SET_b_aHL(7); break; }
	case(0xFF): {SET_b_R(7, A);  break; }
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

int Cpu::binaryAddition(const int& numberOfBits, const int& value1, const int& value2, bool& carryBit3, bool& carryBit7)
{
	int value1Temp = value1;
	int value2Temp = value2;
	bool carryTemp = 0;
	int calcResultTemp = 0;

	int additionValue = 0;

	for (int i = 0; i < numberOfBits; i++)
	{
		value1Temp = (value1 >> i) & 0b1;
		value2Temp = (value2 >> i) & 0b1;

		calcResultTemp = (value1Temp ^ value2Temp) ^ (carryTemp & 0x1);
		carryTemp = (value1Temp & value2Temp) | (value1Temp & (carryTemp & 0x1)) | (value2Temp & (carryTemp & 0x1));

		if ((i == 3) && carryTemp)
			carryBit3 = 1;

		if ((i == 7) && carryTemp)
			carryBit7 = 1;

		additionValue += calcResultTemp << i;
	}

	return additionValue;
}

int Cpu::binarySubstraction(const int& numberOfBits, const int& value1, const int& value2, bool& borrowBit3, bool& borrowBit7)
{
	int value1Temp = value1;
	int value2Temp = value2;
	bool carryTemp = 0;
	int calcResultTemp = 0;

	int substractionValue = 0;

	for (int i = 0; i < numberOfBits; i++)
	{
		value1Temp = (value1 >> i) & 0b1;
		value2Temp = (value2 >> i) & 0b1;

		calcResultTemp = (value1Temp ^ value2Temp) ^ (carryTemp & 0x1);
		carryTemp = ((!(value1Temp ^ value2Temp)) & carryTemp) || (((!value1Temp) & value2Temp) & (!carryTemp));

		if ((i == 3) && carryTemp)
			borrowBit3 = 1;

		if ((i == 7) && carryTemp)
			borrowBit7 = 1;

		substractionValue += calcResultTemp << i;
	}

	return substractionValue;
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
	cout << "LDHL OPCODE MAY CAUSE ISSUE" << endl;
	pc++;
	int8_t e = memory.read(pc);

	if (e >= 0)//WORKING
	{
		F.CY = ((sp & 0xFFFF) + e) > 0xFFFF;
		F.H = ((sp & 0xFFF) + (e & 0xFFF)) > 0xFFF;
	}
	else//NOT WORKING
	{
		cout << "NEGATIVE VALUE MAY CAUSE ISSUE" << endl;
		F.CY = (((sp + e) & 0xFFFF)) <= (sp & 0xFFFF);
		F.H = (((sp + e) & 0xFFF) <= (sp & 0xFFF));

		//Solution 1
		//F.CY = (((sp + e) & 0xFF)) <= (sp & 0xFF);
		//F.H = (((sp + e) & 0xF) <= (sp & 0xF));

		//Solution 2
		//uint8_t tempU8Bits = ((~e) + 1);//Convert int8_t in uint8_t
		//uint16_t tempU16Bits = tempU8Bits;//Convert uint8_t in uint16_t
		//int16_t temp16SBits = ((~tempU16Bits) + 1);//Convert uint16_t in int16_t
		//result = binaryAddition(16, sp, e, carryBit3, carryBit7);//Addiction of SP (uint16_t) + e (uint16_t)

		//Solution 3
		//int16_t e16bits = (int16_t)e;
		//result = binaryAddition(16, sp, e, carryBit3, carryBit7);
	}

	unpairRegisters(H, L, (sp + e));
	F.Z = 0;
	F.N = 0;
	cycles += 3;
	pc++;
}

void Cpu::LD_a16_SP()
{
	pc++;
	uint16_t nnBits = (memory.read(pc + 1) << 8) + memory.read(pc);
	memory.write(nnBits, (sp & 0x00FF));
	memory.write(nnBits + 1, ((sp & 0xFF00) >> 8));
	cycles += 5;
	pc += 2;
}


void Cpu::ADD_A_R(const uint8_t& reg)
{
	A = ADD_ADC_subFunctionFlag(A, reg);
	cycles++;
	pc++;
}

void Cpu::ADD_A_d8()
{
	pc++;
	A = ADD_ADC_subFunctionFlag(A, memory.read(pc));
	cycles += 2;
	pc++;
}


void Cpu::ADD_A_aHL()
{
	A = ADD_ADC_subFunctionFlag(A, memory.read(pairRegisters(H, L)));
	cycles += 2;
	pc++;
}


void Cpu::ADC_A_R_CY(const uint8_t& reg)
{
	A = ADD_ADC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = ADD_ADC_subFunctionFlag(A, reg);
	F.CY |= tempCY;
	F.H |= tempH;
	cycles++;
	pc++;
}

void Cpu::ADC_A_d8_CY()
{
	pc++;
	A = ADD_ADC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = ADD_ADC_subFunctionFlag(A, memory.read(pc));
	F.CY |= tempCY;
	F.H |= tempH;
	cycles += 2;
	pc++;
}

void Cpu::ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = ADD_ADC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = ADD_ADC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
	F.CY |= tempCY;
	F.H |= tempH;
	cycles += 2;
	pc++;
}

uint8_t Cpu::ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
{
	//Variables to use after calculs
	bool carryBit3 = 0;
	bool carryBit7 = 0;
	uint8_t additionValue = binaryAddition(8, reg, value, carryBit3, carryBit7);

	F.Z = !reg;
	F.H = carryBit3;
	F.N = 0;
	F.CY = carryBit7;

	return additionValue;
}


void Cpu::SUB_A_R(const uint8_t& reg)
{
	A = SUB_SBC_subFunctionFlag(A, reg);
	cycles++;
	pc++;
}

void Cpu::SUB_A_d8()
{
	pc++;
	A = SUB_SBC_subFunctionFlag(A, memory.read(pc));
	cycles += 2;
	pc++;
}

void Cpu::SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = SUB_SBC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
	cycles += 2;
	pc++;
}

//RESUME HERE

void Cpu::SBC_A_R_CY(const uint8_t& reg)
{
	A = SUB_SBC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = SUB_SBC_subFunctionFlag(A, reg);
	F.CY |= tempCY;
	F.H |= tempH;
	cycles++;
	pc++;
}

void Cpu::SBC_A_d8_CY()
{
	pc++;
	A = SUB_SBC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = SUB_SBC_subFunctionFlag(A, memory.read(pc));
	F.CY |= tempCY;
	F.H |= tempH;
	cycles += 2;
	pc++;
}

void Cpu::SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = SUB_SBC_subFunctionFlag(A, F.CY);
	bool tempCY = F.CY;
	bool tempH = F.H;
	A = SUB_SBC_subFunctionFlag(A, memory.read(pairRegisters(regPair1, regPair2)));
	F.CY |= tempCY;
	F.H |= tempH;
	cycles += 2;
	pc++;
}

uint8_t Cpu::SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
{
	//Variables to use after calculs
	bool borrowBit3 = 0;
	bool borrowBit7 = 0;
	uint8_t subStractionValue = binarySubstraction(8, reg, value, borrowBit3, borrowBit7);

	F.Z = !reg;
	F.H = borrowBit3;
	F.N = 1;
	F.CY = borrowBit7;

	return subStractionValue;
}



void Cpu::AND_A_R(const uint8_t& reg)
{
	A &= reg;
	F.Z = (A == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;
	cycles++;
	pc++;
}

void Cpu::AND_A_d8()
{
	pc++;
	A &= memory.read(pc);
	F.Z = (A == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}

void Cpu::AND_A_aHL()
{
	A &= memory.read(pairRegisters(H, L));
	F.Z = (A == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}


void Cpu::OR_A_R(const uint8_t& reg)
{
	A |= reg;
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles++;
	pc++;
}

void Cpu::OR_A_d8()
{
	pc++;
	A |= memory.read(pc);
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}

void Cpu::OR_A_aHL()
{
	A |= memory.read(pairRegisters(H, L));
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}




void Cpu::XOR_A_R(const uint8_t& reg)
{
	A ^= reg;
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles++;
	pc++;
}

void Cpu::XOR_A_d8()
{
	pc++;
	A ^= memory.read(pc);
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}

void Cpu::XOR_A_aHL()
{
	A ^= memory.read(pairRegisters(H, L));
	F.Z = (A == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	cycles += 2;
	pc++;
}



void Cpu::CP_A_R(const uint8_t& reg)
{
	CP_subFunctionFlag(reg);
	cycles++;
	pc++;
}

void Cpu::CP_A_d8()
{
	pc++;
	CP_subFunctionFlag(memory.read(pc));
	cycles += 2;
	pc++;
}

void Cpu::CP_A_aHL()
{
	CP_subFunctionFlag(memory.read(pairRegisters(H, L)));
	cycles += 2;
	pc++;
}


void Cpu::CP_subFunctionFlag(const uint8_t& reg)
{
	F.Z = (A == reg);
	F.H = (A & 0xF) - (reg & 0xF) < 0;
	F.CY = (A < reg);
	F.N = 1;
}


void Cpu::INC_R(uint8_t& reg)
{
	INC_subFunctionFlag(reg);
	cycles++;
	pc++;
}

void Cpu::INC_aHL()
{
	//INC_subFunctionFlag(memory.read(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
	uint8_t memTemp = memory.read(pairRegisters(H, L));
	INC_subFunctionFlag(memTemp);
	memory.write(pairRegisters(H, L), memTemp);
	cycles += 3;
	pc++;
}

void Cpu::INC_subFunctionFlag(uint8_t& reg)
{
	reg++;
	F.Z = (reg == 0);
	F.N = 0;
	F.H = ((reg & 0xF) == 0x0);
}



void Cpu::DEC_R(uint8_t& reg)
{
	DEC_subFunctionFlag(reg);
	cycles++;
	pc++;
}

void Cpu::DEC_aHL()
{
	//INC_subFunctionFlag(memory.read(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
	uint8_t memTemp = memory.read(pairRegisters(H, L));
	DEC_subFunctionFlag(memTemp);
	memory.write(pairRegisters(H, L), memTemp);
	cycles += 3;
	pc++;
}

void Cpu::DEC_subFunctionFlag(uint8_t& reg)
{
	reg--;
	F.Z = (reg == 0);
	F.N = 1;
	F.H = ((reg & 0xF) == 0xF);
}


/*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/

//Page 12

void Cpu::ADD_HL_RP(const uint16_t& regsPair)
{
	uint16_t regsPairHL = pairRegisters(H, L);
	F.N = 0;
	F.H = ((regsPairHL & 0xFFF) + (regsPair & 0xFFF)) > 0xFFF;
	F.CY = ((regsPairHL + regsPair) > 0xFFFF);
	unpairRegisters(H, L, (regsPairHL + regsPair));
	cycles += 2;
	pc++;
}

void Cpu::ADD_HL_RP(const uint8_t& regPair1, const uint8_t& regPair2)
{
	ADD_HL_RP(pairRegisters(regPair1, regPair2));
}

void Cpu::ADD_SP_e()
{
	cout << "Program may bug here, thanks to opcode ADD_SP_e" << endl;
	cout << "FOR SURE" << endl;

	pc++;
	int8_t e = memory.read(pc);
	//F.CY = (sp + e) & 0xFFFF;

	sp += e;
	F.Z = 0;
	F.N = 0;
	cycles += 4;
	pc++;
}

void Cpu::INC_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	uint16_t regsPair = pairRegisters(regPair1, regPair2);
	regsPair++;
	unpairRegisters(regPair1, regPair2, regsPair);
	cycles += 2;
	pc++;
}

void Cpu::INC_RP(uint16_t& regsPair)
{
	uint8_t regPair1, regPair2;
	unpairRegisters(regPair1, regPair2, regsPair);
	INC_RP(regPair1, regPair2);
	regsPair = pairRegisters(regPair1, regPair2);
}

void Cpu::DEC_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	uint16_t regsPair = pairRegisters(regPair1, regPair2);
	regsPair--;
	regPair1 = regsPair >> 8;
	regPair2 = regsPair & 0b00001111;
	cycles += 2;
	pc++;
}

void Cpu::DEC_RP(uint16_t& regsPair)
{
	uint8_t regPair1, regPair2;
	unpairRegisters(regPair1, regPair2, regsPair);
	DEC_RP(regPair1, regPair2);
	regsPair = pairRegisters(regPair1, regPair2);
}


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



/*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
//Page 13	(p98)


void Cpu::RLCA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = (A >> 7) & 0x1;
	A <<= 1;
	A &= 0b11111110;
	A += F.CY;
	cycles++;
	pc++;
}

void Cpu::RLA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = (A >> 7) & 0x1;
	A <<= 1;
	A &= 0b11111110;
	A += oldCarry;
	cycles++;
	pc++;
}


void Cpu::RRCA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = A & 0x1;
	A >>= 1;
	A &= 0b01111111;
	A += (F.CY << 7);
	cycles++;
	pc++;
}

void Cpu::RRA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = A & 0x1;
	A >>= 1;
	A &= 0b01111111;
	A |= (oldCarry << 7);
	cycles++;
	pc++;
}


/*-----------------------------------------CB OPCODES OPERATIONS-----------------------------------------------*/

//Page 14	(p99)
void Cpu::RLC_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = (reg >> 7) & 0x1;
	reg <<= 1;
	reg &= 0b11111110;
	reg += F.CY;
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::RLC_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.CY = (temp >> 7) & 0x1;
	temp <<= 1;
	temp &= 0b11111110;
	temp += F.CY;
	memory.write(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	cycles += 4;
	pc++;
}


void Cpu::RL_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	bool oldCarry = F.CY;
	F.CY = (reg >> 7) & 0x1;
	reg <<= 1;
	reg &= 0b11111110;
	reg += oldCarry;
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::RL_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	bool oldCarry = F.CY;
	F.CY = temp >> 7;
	temp <<= 1;
	temp &= 0b11111110;
	temp += oldCarry;
	memory.write(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	cycles += 4;
	pc++;
}


//Page 15
void Cpu::RRC_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = reg & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	reg += (F.CY << 7);
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::RRC_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = temp & 0x1;
	temp >>= 1;
	temp &= 0b01111111;
	temp += (F.CY << 7);
	memory.write(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	cycles += 4;
	pc++;
}

void Cpu::RR_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = reg & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	reg += (oldCarry << 7);
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::RR_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = temp & 0x1;
	temp >>= 1;
	temp &= 0b01111111;
	temp |= (oldCarry << 7);
	memory.write(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	cycles += 4;
	pc++;
}


//Page 16

void Cpu::SLA_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = (reg >> 7) & 0x1;
	reg <<= 1;
	reg &= 0b11111110;
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::SLA_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SLA_R(temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}


void Cpu::SRA_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = reg & 0x1;
	bool bit7 = (reg >> 7) & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	reg += (bit7 << 7);
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::SRA_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SRA_R(temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}


//Page 17
void Cpu::SRL_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = reg & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}

void Cpu::SRL_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SRL_R(temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}


void Cpu::SWAP_R(uint8_t& reg)
{
	F.CY = 0;
	F.H = 0;
	F.N = 0;
	uint8_t nibbleL = reg & 0x0F;
	reg >>= 4;
	reg &= 0x0F;
	reg |= (nibbleL << 4);
	F.Z = (reg == 0);
	cycles += 2;
	pc++;
}
void Cpu::SWAP_aHL()
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SWAP_R(temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}



//Page 18
void Cpu::BIT_b_R(const uint8_t& indexBit, const uint8_t& reg)
{
	F.H = 1;
	F.N = 0;
	uint8_t date8Bits = memory.read(pc);//Get the data byte
	F.Z = !((reg & (0b00000001 << indexBit)) >> (indexBit));//Attribute to F.Z the bit's complement of the reg pointed by the index calculated previously
	cycles += 2;
	pc++;
}

void Cpu::BIT_b_aHL(const uint8_t& indexBit)
{
	BIT_b_R(memory.read(pairRegisters(H, L)), indexBit);
	cycles++;
}

void Cpu::SET_b_R(const uint8_t& indexBit, uint8_t& reg)
{
	uint8_t date8Bits = memory.read(pc);//Get the data byte
	reg |= (0b00000001 << indexBit);//Se the bit pointed by the index calculated previously
	cycles += 2;
	pc++;
}


//Page 17
void Cpu::SET_b_aHL(const uint8_t& indexBit)
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SET_b_R(indexBit, temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}


void Cpu::RES_b_R(const uint8_t& indexBit, uint8_t& reg)
{
	uint8_t date8Bits = memory.read(pc);//Get the data byte
	uint8_t mask = (0b00000001 << indexBit);//Shift the bit to set to 0 to the right position
	mask = ~mask;//Invert the ma
	reg &= mask;
	cycles += 2;
	pc++;
}

void Cpu::RES_b_aHL(const uint8_t& indexBit)
{
	uint8_t temp = memory.read(pairRegisters(H, L));
	SET_b_R(indexBit, temp);
	memory.write(pairRegisters(H, L), temp);
	cycles += 2;
}

/*-------------------------------------JUMP INSTRUCTIONS---------------------------------------*/
//Page 18

void Cpu::JP_d16()
{
	pc++;
	pc = (memory.read(pc + 1) << 8) + (memory.read(pc));
	cycles += 4;
}

void Cpu::JP_cc_d16()
{
	uint8_t condition = ((memory.read(pc) & 0b00011000) >> 3);
	pc++;
	uint8_t lowByte = memory.read(pc);
	pc++;
	uint8_t highByte = memory.read(pc);

	switch (condition)
	{
	case(0b00)://NZ
	{
		if (!F.Z)
		{
			pc = (highByte << 8) + lowByte;
			cycles += 4;
		}
		else
		{
			cycles += 3;
			pc++;
		}
		break;
	}
	case(0b01)://Z
	{
		if (F.Z)
		{
			pc = (highByte << 8) + lowByte;
			cycles += 4;
		}
		else
		{
			cycles += 3;
			pc++;
		}
		break;
	}
	case(0b10)://NC
	{
		if (!F.CY)
		{
			pc = (highByte << 8) + lowByte;
			cycles += 4;
		}
		else
		{
			cycles += 3;
			pc++;
		}
		break;
	}
	case(0b11)://C
	{
		if (F.CY)
		{
			pc = (highByte << 8) + lowByte;
			cycles += 4;
		}
		else
		{
			pc++;
			cycles += 3;
		}
		break;
	}
	}
}


void Cpu::JR_e()
{
	cout << "May have issue now, because of opcode JR e : 0x18" << endl;
	pc++;
	int8_t e = memory.read(pc);//LOOK AT THE Z80 CPU MANUAL
	pc++;
	cycles += 3;
	pc += e;
}


void Cpu::JR_cc_e()
{
	uint8_t condition = ((memory.read(pc) & 0b00011000) >> 3);
	pc++;
	int8_t e = memory.read(pc);
	pc++;
	cycles += 2;

	switch (condition)
	{
	case(0b00)://NZ
	{
		if (!F.Z)
		{
			pc += e;
			cycles++;
		}
		break;
	}
	case(0b01)://Z
	{
		if (F.Z)
		{
			pc += e;
			cycles++;
		}
		break;
	}
	case(0b10)://NC
	{
		if (!F.CY)
		{
			pc += e;
			cycles++;
		}
		break;
	}
	case(0b11)://C
	{
		if (F.CY)
		{
			pc += e;
			cycles++;
		}
		break;
	}
	}
}

void Cpu::JP_HL()
{
	pc = pairRegisters(H, L);
	cycles++;
}


void Cpu::CALL()
{
	pc += 3;
	memory.write(sp - 1, (pc >> 8));
	memory.write(sp - 2, (pc & 0x00FF));
	pc = (memory.read(pc - 1) << 8) + memory.read(pc - 2);
	sp -= 2;
	cycles += 6;
}

void Cpu::CALL_cc()
{
	uint8_t condition = ((memory.read(pc) & 0b00011000) >> 3);
	switch (condition)
	{
	case(0b00)://NZ
	{
		if (!F.Z)
		{
			CALL();
		}
		else
		{
			pc += 3;
			cycles += 3;
		}
		break;
	}
	case(0b01)://Z
	{
		if (F.Z)
		{
			CALL();
		}
		else
		{
			pc += 3;
			cycles += 3;
		}
		break;
	}
	case(0b10)://NC
	{
		if (!F.CY)
		{
			CALL();
		}
		else
		{
			pc += 3;
			cycles += 3;
		}
		break;
	}
	case(0b11)://C
	{
		if (F.CY)
		{
			CALL();
		}
		else
		{
			pc += 3;
			cycles += 3;
		}
		break;
	}
	}
}


void Cpu::RET()
{
	pc = (memory.read(sp + 1) << 8) + memory.read(sp);
	sp += 2;
	cycles += 4;
}

void Cpu::RETI()
{
	pc = (memory.read(sp + 1) << 8) + memory.read(sp);
	sp += 2;
	cycles += 4;
}


void Cpu::RET_cc()
{
	uint8_t condition = ((memory.read(pc) & 0b00011000) >> 3);
	cycles++;
	switch (condition)
	{
	case(0b00)://NZ
	{
		if (!F.Z)
		{
			RET();
		}
		else
		{
			cycles++;
			pc++;
		}
		break;
	}
	case(0b01)://Z
	{
		if (F.Z)
		{
			RET();
		}
		else
		{
			cycles++;
			pc++;
		}
		break;
	}
	case(0b10)://NC
	{
		if (!F.CY)
		{
			RET();
		}
		else
		{
			cycles++;
			pc++;
		}
		break;
	}
	case(0b11)://C
	{
		if (F.CY)
		{
			RET();
		}
		else
		{
			cycles++;
			pc++;
		}
		break;
	}
	}
}

//Page 21
void Cpu::RST()
{
	uint8_t opcode = memory.read(pc);
	pc++;
	memory.write(sp - 1, (pc >> 8));
	memory.write(sp - 2, (pc & 0x00FF));
	sp -= 2;
	cycles += 4;

	uint8_t condition = ((opcode & 0b00111000) >> 3);

	switch (condition)
	{
	case(0b000):
	{
		pc = 0x0000;
		break;
	}
	case(0b001):
	{
		pc = 0x0008;
		break;
	}
	case(0b010):
	{
		pc = 0x0010;
		break;
	}
	case(0b011):
	{
		pc = 0x0018;
	}
	case(0b100):
	{
		pc = 0x0020;
		break;
	}
	case(0b101):
	{
		pc = 0x0028;
		break;
	}
	case(0b110):
	{
		pc = 0x0030;
		break;
	}
	case(0b111):
	{
		pc = 0x0038;
		break;
	}
	}
}


/*-------------------------------------GENERAL-PURPOSE ARITHMETIC OPERATIONS AND CPU CONTROL INSTRUCTIONS---------------------------------------*/

void Cpu::DAA()
{
	cout << "May bug now, because of opcode DAA" << endl;
	cycles += 1;

	if (!F.N)//If previsous opcode is one of the ADD opcodes
	{
		if (((A & 0xF0) > 0x90) || F.CY)
		{
			A += 0x60;
			F.CY = 1;
		}
		else
		{
			F.CY = 0;
		}

		if (((A & 0x0F) > 0x09) || F.H)
		{
			A += 0x06;
		}
	}
	else//If previsous opcode is one of the SUB opcodes
	{
		if (((A & 0xF0) > 0x90) || F.CY)
		{
			A -= 0x60;
			F.CY = 1;
		}
		else
		{
			F.CY = 0;
		}

		if (((A & 0x0F) > 0x09) || F.H)
		{
			A -= 0x06;
		}
	}

	F.H = 0;
	F.Z = (A == 0);
	pc++;
}


void Cpu::CPL()
{
	A = ~A;
	F.H = 1;
	F.N = 1;
	cycles++;
	pc++;
}


void Cpu::NOP()
{
	cycles++;
	pc++;
}

void Cpu::CCF()
{
	F.CY = !F.CY;
	F.H = 0;
	F.N = 0;
	cycles++;
	pc++;
}


void Cpu::SCF()
{
	F.CY = 1;
	F.H = 0;
	F.N = 0;
	cycles++;
	pc++;
}

void Cpu::EI()
{
	IME = 1;
	cycles++;
	pc++;
}

void Cpu::DI()
{
	IME = 0;
	cycles++;
	pc++;
}


//Page 21
void Cpu::HALT()//NOT IMPLEMENTED
{
	halted = 1;
	cycles++;
	pc++;
}

void Cpu::STOP()//NOT IMPLEMENTED
{
	stopped = 1;
	cycles++;
	pc++;
}


