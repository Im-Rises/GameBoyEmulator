#include "Cpu.h"

Cpu::Cpu()
{
	A = 0;
	B = C = D = E = H = L = 0;
	pc = USER_PROGRAM_AREA;
	sp = CPU_WORK_RAM_OR_AND_STACK_END;
	F.Z = F.N = F.H = F.CY = 0;
}

void Cpu::readOpcode()
{

}

Cpu::~Cpu()
{

}

void Cpu::executeOpcode(uint8_t opcode)
{
	/// <summary>
	/// Opcode issue with number 0x7A and 0x7D because D and L have the same three bits
	/// </summary>
	/// <param name="opcode"></param>
	switch (opcode) {
	case(0x00): {break; }
	case(0x01): {opcodeOperation16bits_LD_RP_d16(B, C); break; }
	case(0x02): {opcodeOperation_LD_aRP_R(B, C, A); break; }
	case(0x03): {operationOpcode16bits_INC_RP(B, C); break; }
	case(0x04): {operationOpcode_INC_R(B); break; }
	case(0x05): {operationOpcode_DEC_R(B); break; }
	case(0x06): {opcodeOperation_LD_R_d8(B); break; }
	case(0x07): {operationOpcode_RLCA(); break; }
	case(0x08): {opcodeOperation16bits_LD_a8_SP(); break; }
	case(0x09): {operationOpcode16bits_ADD_HL_RP(pairRegisters(B, C)); break; }
	case(0x0A): {opcodeOperation_LD_R_aRP(A, B, C); break; }
	case(0x0B): {operationOpcode16bits_DEC_RP(B, C); break; }
	case(0x0C): {operationOpcode_INC_R(C); break; }
	case(0x0D): {operationOpcode_DEC_R(C); break; }
	case(0x0E): {opcodeOperation_LD_R_d8(C); break; }
	case(0x0F): {operationOpcode_RRCA(); break; }
	case(0x10): {break; }
	case(0x11): {opcodeOperation16bits_LD_RP_d16(D, D); break; }
	case(0x12): {opcodeOperation_LD_aRP_R(D, E, A); break; }
	case(0x13): {operationOpcode16bits_INC_RP(D, E); break; }
	case(0x14): {operationOpcode_INC_R(D); break; }
	case(0x15): {operationOpcode_DEC_R(D); break; }
	case(0x16): {opcodeOperation_LD_R_d8(D); break; }
	case(0x17): {operationOpcode_RLA(); break; }
	case(0x18): {break; }
	case(0x19): {operationOpcode16bits_ADD_HL_RP(pairRegisters(D, E)); break; }
	case(0x1A): {opcodeOperation_LD_R_aRP(A, D, E); break; }
	case(0x1B): {operationOpcode16bits_DEC_RP(D, E); break; }
	case(0x1C): {operationOpcode_INC_R(E); break; }
	case(0x1D): {operationOpcode_DEC_R(E); break; }
	case(0x1E): {opcodeOperation_LD_R_d8(E); break; }
	case(0x1F): {operationOpcode_RRA(); break; }
	case(0x20): {break; }
	case(0x21): {opcodeOperation16bits_LD_RP_d16(H, L); break; }
	case(0x22): {opcodeOperation_LD_aRP_R_RPI(H, L, A); break; }
	case(0x23): {operationOpcode16bits_INC_RP(H, L); break; }
	case(0x24): {operationOpcode_INC_R(H); break; }
	case(0x25): {operationOpcode_DEC_R(H); break; }
	case(0x26): {opcodeOperation_LD_R_d8(H); break; }
	case(0x27): {break; }
	case(0x28): {break; }
	case(0x29): {operationOpcode16bits_ADD_HL_RP(pairRegisters(H, L)); break; }
	case(0x2A): {opcodeOperation_LD_R_aRP_RPI(A, H, L); break; }
	case(0x2B): {operationOpcode16bits_DEC_RP(H, L); break; }
	case(0x2C): {operationOpcode_INC_R(L); break; }
	case(0x2D): {operationOpcode_DEC_R(L); break; }
	case(0x2E): {opcodeOperation_LD_R_d8(L); break; }
	case(0x2F): {break; }
	case(0x30): {break; }
	case(0x31): {opcodeOperation16bits_LD_RP_d16(sp); break; }
	case(0x32): {break; }
	case(0x33): {operationOpcode16bits_INC_RP(sp); break; }
	case(0x34): {operationOpcode_INC_aHL(H, L); break; }
	case(0x35): {operationOpcode_DEC_aHL(H, L); break; }
	case(0x36): {opcodeOperation_LD_aRP_d8(H, L); break; }
	case(0x37): {break; }
	case(0x38): {break; }
	case(0x39): {operationOpcode16bits_ADD_HL_RP(sp); break; }
	case(0x3A): {opcodeOperation_LD_R_aRP_RPD(A, H, L); break; }
	case(0x3B): {operationOpcode16bits_DEC_RP(sp); break; }
	case(0x3C): {operationOpcode_INC_R(A); break; }
	case(0x3D): {operationOpcode_DEC_R(A); break; }
	case(0x3E): {opcodeOperation_LD_R_d8(A); break; }
	case(0x3F): {break; }
	case(0x40): {opcodeOperation_LD_R_R(B, B); break; }
	case(0x41): {opcodeOperation_LD_R_R(B, C); break; }
	case(0x42): {opcodeOperation_LD_R_R(B, D); break; }
	case(0x43): {opcodeOperation_LD_R_R(B, E); break; }
	case(0x44): {opcodeOperation_LD_R_R(B, H); break; }
	case(0x45): {opcodeOperation_LD_R_R(B, L); break; }
	case(0x46): {opcodeOperation_LD_R_aRP(B, H, L); break; }
	case(0x47): {opcodeOperation_LD_R_R(B, A); break; }
	case(0x48): {opcodeOperation_LD_R_R(C, B); break; }
	case(0x49): {opcodeOperation_LD_R_R(C, C); break; }
	case(0x4A): {opcodeOperation_LD_R_R(C, D); break; }
	case(0x4B): {opcodeOperation_LD_R_R(C, E); break; }
	case(0x4C): {opcodeOperation_LD_R_R(C, H); break; }
	case(0x4D): {opcodeOperation_LD_R_R(C, L); break; }
	case(0x4E): {opcodeOperation_LD_R_aRP(C, H, L); break; }
	case(0x4F): {opcodeOperation_LD_R_R(C, A); break; }
	case(0x50): {opcodeOperation_LD_R_R(D, B); break; }
	case(0x51): {opcodeOperation_LD_R_R(D, C); break; }
	case(0x52): {opcodeOperation_LD_R_R(D, D); break; }
	case(0x53): {opcodeOperation_LD_R_R(D, E); break; }
	case(0x54): {opcodeOperation_LD_R_R(D, H); break; }
	case(0x55): {opcodeOperation_LD_R_R(D, L); break; }
	case(0x56): {opcodeOperation_LD_R_aRP(D, H, L); break; }
	case(0x57): {opcodeOperation_LD_R_R(D, A); break; }
	case(0x58): {opcodeOperation_LD_R_R(E, B); break; }
	case(0x59): {opcodeOperation_LD_R_R(E, C); break; }
	case(0x5A): {opcodeOperation_LD_R_R(E, D); break; }
	case(0x5B): {opcodeOperation_LD_R_R(E, E); break; }
	case(0x5C): {opcodeOperation_LD_R_R(E, H); break; }
	case(0x5D): {opcodeOperation_LD_R_R(E, L); break; }
	case(0x5E): {opcodeOperation_LD_R_aRP(E, H, L); break; }
	case(0x5F): {opcodeOperation_LD_R_R(E, A); break; }
	case(0x60): {opcodeOperation_LD_R_R(H, B); break; }
	case(0x61): {opcodeOperation_LD_R_R(H, C); break; }
	case(0x62): {opcodeOperation_LD_R_R(H, D); break; }
	case(0x63): {opcodeOperation_LD_R_R(H, E); break; }
	case(0x64): {opcodeOperation_LD_R_R(H, H); break; }
	case(0x65): {opcodeOperation_LD_R_R(H, L); break; }
	case(0x66): {opcodeOperation_LD_R_aRP(H, H, L); break; }
	case(0x67): {opcodeOperation_LD_R_R(H, A); break; }
	case(0x68): {opcodeOperation_LD_R_R(L, B); break; }
	case(0x69): {opcodeOperation_LD_R_R(L, C); break; }
	case(0x6A): {opcodeOperation_LD_R_R(L, D); break; }
	case(0x6B): {opcodeOperation_LD_R_R(L, E); break; }
	case(0x6C): {opcodeOperation_LD_R_R(L, H); break; }
	case(0x6D): {opcodeOperation_LD_R_R(L, L); break; }
	case(0x6E): {opcodeOperation_LD_R_aRP(L, H, L); break; }
	case(0x6F): {opcodeOperation_LD_R_R(L, A); break; }
	case(0x70): {opcodeOperation_LD_aRP_R(H, L, B); break; }
	case(0x71): {opcodeOperation_LD_aRP_R(H, L, C); break; }
	case(0x72): {opcodeOperation_LD_aRP_R(H, L, D); break; }
	case(0x73): {opcodeOperation_LD_aRP_R(H, L, E); break; }
	case(0x74): {opcodeOperation_LD_aRP_R(H, L, H); break; }
	case(0x75): {opcodeOperation_LD_aRP_R(H, L, L); break; }
	case(0x76): {break; }
	case(0x77): {opcodeOperation_LD_aRP_R(H, L, A); break; }
	case(0x78): {opcodeOperation_LD_R_R(A, B); break; }
	case(0x79): {opcodeOperation_LD_R_R(A, C); break; }
	case(0x7A): {opcodeOperation_LD_R_R(A, D); break; }
	case(0x7B): {opcodeOperation_LD_R_R(A, E); break; }
	case(0x7C): {opcodeOperation_LD_R_R(A, H); break; }
	case(0x7D): {opcodeOperation_LD_R_R(A, L); break; }
	case(0x7E): {opcodeOperation_LD_R_aRP(A, H, L); break; }
	case(0x7F): {opcodeOperation_LD_R_R(A, A); break; }
	case(0x80): {operationOpcode_ADD_R_R(A, B); break; }
	case(0x81): {operationOpcode_ADD_R_R(A, C); break; }
	case(0x82): {operationOpcode_ADD_R_R(A, D); break; }
	case(0x83): {operationOpcode_ADD_R_R(A, E); break; }
	case(0x84): {operationOpcode_ADD_R_R(A, H); break; }
	case(0x85): {operationOpcode_ADD_R_R(A, L); break; }
	case(0x86): {operationOpcode_ADD_R_aRP(A, H, L); break; }
	case(0x87): {operationOpcode_ADD_R_R(A, A); break; }
	case(0x88): {operationOpcode_ADC_A_R_CY(B); break; }
	case(0x89): {operationOpcode_ADC_A_R_CY(C); break; }
	case(0x8A): {operationOpcode_ADC_A_R_CY(D); break; }
	case(0x8B): {operationOpcode_ADC_A_R_CY(E); break; }
	case(0x8C): {operationOpcode_ADC_A_R_CY(H); break; }
	case(0x8D): {operationOpcode_ADC_A_R_CY(L); break; }
	case(0x8E): {operationOpcode_ADC_A_aHL_CY(H, L); break; }
	case(0x8F): {operationOpcode_ADC_A_R_CY(A); break; }
	case(0x90): {operationOpcode_SUB_A_R(B); break; }
	case(0x91): {operationOpcode_SUB_A_R(C); break; }
	case(0x92): {operationOpcode_SUB_A_R(D); break; }
	case(0x93): {operationOpcode_SUB_A_R(E); break; }
	case(0x94): {operationOpcode_SUB_A_R(H); break; }
	case(0x95): {operationOpcode_SUB_A_R(L); break; }
	case(0x96): {operationOpcode_SUB_A_aHL(H, L); break; }
	case(0x97): {operationOpcode_SUB_A_R(A); break; }
	case(0x98): {operationOpcode_SBC_A_R_CY(B); break; }
	case(0x99): {operationOpcode_SBC_A_R_CY(C); break; }
	case(0x9A): {operationOpcode_SBC_A_R_CY(D); break; }
	case(0x9B): {operationOpcode_SBC_A_R_CY(E); break; }
	case(0x9C): {operationOpcode_SBC_A_R_CY(H); break; }
	case(0x9D): {operationOpcode_SBC_A_R_CY(L); break; }
	case(0x9E): {operationOpcode_SBC_A_aHL_CY(H, L); break; }
	case(0x9F): {operationOpcode_SBC_A_R_CY(A); break; }
	case(0xA0): {operationOpcode_AND_R_R(A, B); break; }
	case(0xA1): {operationOpcode_AND_R_R(A, C); break; }
	case(0xA2): {operationOpcode_AND_R_R(A, D); break; }
	case(0xA3): {operationOpcode_AND_R_R(A, E); break; }
	case(0xA4): {operationOpcode_AND_R_R(A, H); break; }
	case(0xA5): {operationOpcode_AND_R_R(A, L); break; }
	case(0xA6): {operationOpcode_AND_R_aHL(A, H, L); break; }
	case(0xA7): {operationOpcode_AND_R_R(A, A); break; }
	case(0xA8): {operationOpcode_XOR_R_R(A, B); break; }
	case(0xA9): {operationOpcode_XOR_R_R(A, C); break; }
	case(0xAA): {operationOpcode_XOR_R_R(A, D); break; }
	case(0xAB): {operationOpcode_XOR_R_R(A, E); break; }
	case(0xAC): {operationOpcode_XOR_R_R(A, H); break; }
	case(0xAD): {operationOpcode_XOR_R_R(A, L); break; }
	case(0xAE): {operationOpcode_XOR_R_aHL(A, H, L); break; }
	case(0xAF): {operationOpcode_XOR_R_R(A, A); break; }
	case(0xB0): {operationOpcode_OR_R_R(A, B); break; }
	case(0xB1): {operationOpcode_OR_R_R(A, C); break; }
	case(0xB2): {operationOpcode_OR_R_R(A, D); break; }
	case(0xB3): {operationOpcode_OR_R_R(A, E); break; }
	case(0xB4): {operationOpcode_OR_R_R(A, H); break; }
	case(0xB5): {operationOpcode_OR_R_R(A, L); break; }
	case(0xB6): {operationOpcode_OR_R_aHL(A, H, L); break; }
	case(0xB7): {operationOpcode_OR_R_R(A, A); break; }
	case(0xB8): {operationOpcode_CP_R_R(A, B); break; }
	case(0xB9): {operationOpcode_CP_R_R(A, C); break; }
	case(0xBA): {operationOpcode_CP_R_R(A, D); break; }
	case(0xBB): {operationOpcode_CP_R_R(A, E); break; }
	case(0xBC): {operationOpcode_CP_R_R(A, H); break; }
	case(0xBD): {operationOpcode_CP_R_R(A, L); break; }
	case(0xBE): {operationOpcode_CP_R_aHL(A, H, L); break; }
	case(0xBF): {operationOpcode_CP_R_R(A, A); break; }
	case(0xC0): {operationOpcode_CP_R_R(A, B); break; }
	case(0xC1): {opcodeOperation16bits_POP_RP(B, C); break; }
	case(0xC2): {break; }
	case(0xC3): {break; }
	case(0xC4): {break; }
	case(0xC5): {opcodeOperation16bits_PUSH_RP(B, C); break; }
	case(0xC6): {operationOpcode_ADD_R_d8(A); break; }
	case(0xC7): {break; }
	case(0xC8): {break; }
	case(0xC9): {break; }
	case(0xCA): {break; }
	case(0xCB): {executeOpcodeFollowingCB(); break; }
	case(0xCC): {break; }
	case(0xCD): {break; }
	case(0xCE): {operationOpcode_ADC_A_d8_CY(); break; }
	case(0xCF): {break; }
	case(0xD0): {break; }
	case(0xD1): {opcodeOperation16bits_POP_RP(D, E); break; }
	case(0xD2): {break; }
	case(0xD3): {break; }
	case(0xD4): {break; }
	case(0xD5): {opcodeOperation16bits_PUSH_RP(D, E); break; }
	case(0xD6): {operationOpcode_SUB_A_d8(); break; }
	case(0xD7): {break; }
	case(0xD8): {break; }
	case(0xD9): {break; }
	case(0xDA): {break; }
	case(0xDB): {break; }
	case(0xDC): {break; }
	case(0xDD): {break; }
	case(0xDE): {break; }
	case(0xDF): {break; }
	case(0xE0): {opcodeOperation_LD_a8o_R(A); break; }
	case(0xE1): {opcodeOperation16bits_POP_RP(H, L); break; }
	case(0xE2): {opcodeOperation_LD_aRo_R(C, A); break; }
	case(0xE3): {break; }
	case(0xE4): {break; }
	case(0xE5): {opcodeOperation16bits_PUSH_RP(H, L); break; }
	case(0xE6): {operationOpcode_AND_R_d8(A); break; }
	case(0xE7): {break; }
	case(0xE8): {operationOpcode16bits_ADD_SP_e(); break; }
	case(0xE9): {break; }
	case(0xEA): {opcodeOperation_LD_a16_R(A); break; }
	case(0xEB): {break; }
	case(0xEC): {break; }
	case(0xED): {break; }
	case(0xEE): {operationOpcode_XOR_R_d8(A); break; }
	case(0xEF): {break; }
	case(0xF0): {opcodeOperation_LD_R_a8o(A); break; }
	case(0xF1): {opcodeOperation16bits_POP_RP(A, F); break; }
	case(0xF2): {opcodeOperation_LD_R_aRo(A, C); break; }
	case(0xF3): {break; }
	case(0xF4): {break; }
	case(0xF5): {opcodeOperation16bits_PUSH_RP(A, F); break; }
	case(0xF6): {operationOpcode_OR_R_d8(A); break; }
	case(0xF7): {break; }
	case(0xF8): {opcodeOperation16bits_LDHL_SP_e(); break; }
	case(0xF9): {opcodeOperation16bits_LD_RP_RP(sp, H, L); break; }
	case(0xFA): {opcodeOperation_LD_R_a16(A); break; }
	case(0xFB): {break; }
	case(0xFC): {break; }
	case(0xFD): {break; }
	case(0xFE): {operationOpcode_CP_R_d8(A); break; }
	case(0xFF): {break; }
	}
}

void Cpu::executeOpcodeFollowingCB()
{
	pc++;
	switch (memory.getMemoryOfIndex(pc)) {
	case(0x00): {operationOpcode_RLC_R(B); break; }
	case(0x01): {operationOpcode_RLC_R(C); break; }
	case(0x02): {operationOpcode_RLC_R(D); break; }
	case(0x03): {operationOpcode_RLC_R(E); break; }
	case(0x04): {operationOpcode_RLC_R(H); break; }
	case(0x05): {operationOpcode_RLC_R(L); break; }
	case(0x06): {operationOpcode_RLC_aHL(); break; }
	case(0x07): {operationOpcode_RLC_R(A); break; }
	case(0x08): {operationOpcode_RRC_R(B); break; }
	case(0x09): {operationOpcode_RRC_R(C); break; }
	case(0x0A): {operationOpcode_RRC_R(D); break; }
	case(0x0B): {operationOpcode_RRC_R(E); break; }
	case(0x0C): {operationOpcode_RRC_R(H); break; }
	case(0x0D): {operationOpcode_RRC_R(L); break; }
	case(0x0E): {operationOpcode_RRC_aHL(); break; }
	case(0x0F): {operationOpcode_RRC_R(A); break; }
	case(0x10): {operationOpcode_RL_R(B); break; }
	case(0x11): {operationOpcode_RL_R(C); break; }
	case(0x12): {operationOpcode_RL_R(D); break; }
	case(0x13): {operationOpcode_RL_R(E); break; }
	case(0x14): {operationOpcode_RL_R(H); break; }
	case(0x15): {operationOpcode_RL_R(L); break; }
	case(0x16): {operationOpcode_RL_aHL(); break; }
	case(0x17): {operationOpcode_RL_R(A); break; }
	case(0x18): {operationOpcode_RR_R(B); break; }
	case(0x19): {operationOpcode_RR_R(C); break; }
	case(0x1A): {operationOpcode_RR_R(D); break; }
	case(0x1B): {operationOpcode_RR_R(E); break; }
	case(0x1C): {operationOpcode_RR_R(H); break; }
	case(0x1D): {operationOpcode_RR_R(L); break; }
	case(0x1E): {operationOpcode_RR_aHL(); break; }
	case(0x1F): {operationOpcode_RR_R(A); break; }
	case(0x20): {break; }
	case(0x21): {break; }
	case(0x22): {break; }
	case(0x23): {break; }
	case(0x24): {break; }
	case(0x25): {break; }
	case(0x26): {break; }
	case(0x27): {break; }
	case(0x28): {break; }
	case(0x29): {break; }
	case(0x2A): {break; }
	case(0x2B): {break; }
	case(0x2C): {break; }
	case(0x2D): {break; }
	case(0x2E): {break; }
	case(0x2F): {break; }
	case(0x30): {break; }
	case(0x31): {break; }
	case(0x32): {break; }
	case(0x33): {break; }
	case(0x34): {break; }
	case(0x35): {break; }
	case(0x36): {break; }
	case(0x37): {break; }
	case(0x38): {break; }
	case(0x39): {break; }
	case(0x3A): {break; }
	case(0x3B): {break; }
	case(0x3C): {break; }
	case(0x3D): {break; }
	case(0x3E): {break; }
	case(0x3F): {break; }
	case(0x40): {break; }
	case(0x41): {break; }
	case(0x42): {break; }
	case(0x43): {break; }
	case(0x44): {break; }
	case(0x45): {break; }
	case(0x46): {break; }
	case(0x47): {break; }
	case(0x48): {break; }
	case(0x49): {break; }
	case(0x4A): {break; }
	case(0x4B): {break; }
	case(0x4C): {break; }
	case(0x4D): {break; }
	case(0x4E): {break; }
	case(0x4F): {break; }
	case(0x50): {break; }
	case(0x51): {break; }
	case(0x52): {break; }
	case(0x53): {break; }
	case(0x54): {break; }
	case(0x55): {break; }
	case(0x56): {break; }
	case(0x57): {break; }
	case(0x58): {break; }
	case(0x59): {break; }
	case(0x5A): {break; }
	case(0x5B): {break; }
	case(0x5C): {break; }
	case(0x5D): {break; }
	case(0x5E): {break; }
	case(0x5F): {break; }
	case(0x60): {break; }
	case(0x61): {break; }
	case(0x62): {break; }
	case(0x63): {break; }
	case(0x64): {break; }
	case(0x65): {break; }
	case(0x66): {break; }
	case(0x67): {break; }
	case(0x68): {break; }
	case(0x69): {break; }
	case(0x6A): {break; }
	case(0x6B): {break; }
	case(0x6C): {break; }
	case(0x6D): {break; }
	case(0x6E): {break; }
	case(0x6F): {break; }
	case(0x70): {break; }
	case(0x71): {break; }
	case(0x72): {break; }
	case(0x73): {break; }
	case(0x74): {break; }
	case(0x75): {break; }
	case(0x76): {break; }
	case(0x77): {break; }
	case(0x78): {break; }
	case(0x79): {break; }
	case(0x7A): {break; }
	case(0x7B): {break; }
	case(0x7C): {break; }
	case(0x7D): {break; }
	case(0x7E): {break; }
	case(0x7F): {break; }
	case(0x80): {break; }
	case(0x81): {break; }
	case(0x82): {break; }
	case(0x83): {break; }
	case(0x84): {break; }
	case(0x85): {break; }
	case(0x86): {break; }
	case(0x87): {break; }
	case(0x88): {break; }
	case(0x89): {break; }
	case(0x8A): {break; }
	case(0x8B): {break; }
	case(0x8C): {break; }
	case(0x8D): {break; }
	case(0x8E): {break; }
	case(0x8F): {break; }
	case(0x90): {break; }
	case(0x91): {break; }
	case(0x92): {break; }
	case(0x93): {break; }
	case(0x94): {break; }
	case(0x95): {break; }
	case(0x96): {break; }
	case(0x97): {break; }
	case(0x98): {break; }
	case(0x99): {break; }
	case(0x9A): {break; }
	case(0x9B): {break; }
	case(0x9C): {break; }
	case(0x9D): {break; }
	case(0x9E): {break; }
	case(0x9F): {break; }
	case(0xA0): {break; }
	case(0xA1): {break; }
	case(0xA2): {break; }
	case(0xA3): {break; }
	case(0xA4): {break; }
	case(0xA5): {break; }
	case(0xA6): {break; }
	case(0xA7): {break; }
	case(0xA8): {break; }
	case(0xA9): {break; }
	case(0xAA): {break; }
	case(0xAB): {break; }
	case(0xAC): {break; }
	case(0xAD): {break; }
	case(0xAE): {break; }
	case(0xAF): {break; }
	case(0xB0): {break; }
	case(0xB1): {break; }
	case(0xB2): {break; }
	case(0xB3): {break; }
	case(0xB4): {break; }
	case(0xB5): {break; }
	case(0xB6): {break; }
	case(0xB7): {break; }
	case(0xB8): {break; }
	case(0xB9): {break; }
	case(0xBA): {break; }
	case(0xBB): {break; }
	case(0xBC): {break; }
	case(0xBD): {break; }
	case(0xBE): {break; }
	case(0xBF): {break; }
	case(0xC0): {break; }
	case(0xC1): {break; }
	case(0xC2): {break; }
	case(0xC3): {break; }
	case(0xC4): {break; }
	case(0xC5): {break; }
	case(0xC6): {break; }
	case(0xC7): {break; }
	case(0xC8): {break; }
	case(0xC9): {break; }
	case(0xCA): {break; }
	case(0xCB): {break; }
	case(0xCC): {break; }
	case(0xCD): {break; }
	case(0xCE): {break; }
	case(0xCF): {break; }
	case(0xD0): {break; }
	case(0xD1): {break; }
	case(0xD2): {break; }
	case(0xD3): {break; }
	case(0xD4): {break; }
	case(0xD5): {break; }
	case(0xD6): {break; }
	case(0xD7): {break; }
	case(0xD8): {break; }
	case(0xD9): {break; }
	case(0xDA): {break; }
	case(0xDB): {break; }
	case(0xDC): {break; }
	case(0xDD): {break; }
	case(0xDE): {break; }
	case(0xDF): {break; }
	case(0xE0): {break; }
	case(0xE1): {break; }
	case(0xE2): {break; }
	case(0xE3): {break; }
	case(0xE4): {break; }
	case(0xE5): {break; }
	case(0xE6): {break; }
	case(0xE7): {break; }
	case(0xE8): {break; }
	case(0xE9): {break; }
	case(0xEA): {break; }
	case(0xEB): {break; }
	case(0xEC): {break; }
	case(0xED): {break; }
	case(0xEE): {break; }
	case(0xEF): {break; }
	case(0xF0): {break; }
	case(0xF1): {break; }
	case(0xF2): {break; }
	case(0xF3): {break; }
	case(0xF4): {break; }
	case(0xF5): {break; }
	case(0xF6): {break; }
	case(0xF7): {break; }
	case(0xF8): {break; }
	case(0xF9): {break; }
	case(0xFA): {break; }
	case(0xFB): {break; }
	case(0xFC): {break; }
	case(0xFD): {break; }
	case(0xFE): {break; }
	case(0xFF): {break; }
	}
}


/*-----------------------------------------SUB FUNCTIONS------------------------------------------*/

uint16_t Cpu::pairRegisters(const uint8_t reg1, const uint8_t reg2)const
{
	return ((reg1 << 8) + reg2);
}

uint8_t Cpu::flagToByte(const Flag& flag)const
{
	uint8_t temp = (flag.Z << 7) + (flag.N << 6) + (flag.H << 5) + (flag.CY << 4);
	return temp;
}


/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

/*-------------------------------------8bits TRANSFER AND INPUT/OUTPUT INSTRUCTIONS---------------------------------------*/

//Page 1
void Cpu::opcodeOperation_LD_R_R(uint8_t& reg1, const uint8_t& reg2) {
	reg1 = reg2;
	pc++;
}

void Cpu::opcodeOperation_LD_R_d8(uint8_t& reg)
{
	pc++;
	reg = memory.getMemoryOfIndex(pc);
	pc++;
}

void Cpu::opcodeOperation_LD_R_aRP(uint8_t& reg, const uint8_t regPair1, const uint8_t regPair2)
{
	reg = memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	pc++;
}


//Page 2
void Cpu::opcodeOperation_LD_aRP_R(const uint8_t& registerPair1, const uint8_t& registerPair2, const uint8_t& reg)
{
	memory.setMemoryOfIndex(pairRegisters(registerPair1, registerPair2), reg);
	pc++;
}

void Cpu::opcodeOperation_LD_aRP_d8(uint8_t& registerPair1, uint8_t& registerPair2)
{
	pc++;
	memory.setMemoryOfIndex(memory.getMemoryOfIndex(pairRegisters(H, L)), memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::opcodeOperation_LD_R_aRo(uint8_t& reg1, const uint8_t& reg2)
{
	reg1 = memory.getMemoryOfIndex(0xFF00 + reg2);
	pc++;
}


//Page 3
void Cpu::opcodeOperation_LD_aRo_R(const uint8_t& reg1, const uint8_t& reg2)
{
	memory.setMemoryOfIndex((0xFF00 + reg1), reg2);
	pc++;
}

void Cpu::opcodeOperation_LD_R_a8o(uint8_t& reg)
{
	pc++;
	reg = memory.getMemoryOfIndex(0xFF00 + memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::opcodeOperation_LD_a8o_R(const uint8_t& reg)
{
	pc++;
	memory.setMemoryOfIndex(0xFF00 + pc, A);
	pc++;
}

void Cpu::opcodeOperation_LD_R_a16(uint8_t& reg)
{
	pc++;
	reg = memory.getMemoryOfIndex(((memory.getMemoryOfIndex(pc) << 8) + memory.getMemoryOfIndex(pc + 1)));
	pc += 2;
}


//Page 4
void Cpu::opcodeOperation_LD_a16_R(const uint8_t& reg)
{
	pc++;
	memory.setMemoryOfIndex(((memory.getMemoryOfIndex(pc) << 8) + memory.getMemoryOfIndex(pc + 1)), reg);
	pc += 2;
}

void Cpu::opcodeOperation_LD_R_aRP_RPI(uint8_t& reg, uint8_t regPair1, uint8_t regPair2)
{
	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
	reg = memory.getMemoryOfIndex(registersPairTemp);
	registersPairTemp++;
	regPair1 = registersPairTemp >> 8;
	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
	pc++;
}

void Cpu::opcodeOperation_LD_R_aRP_RPD(uint8_t& reg, uint8_t regPair1, uint8_t regPair2)
{
	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
	reg = memory.getMemoryOfIndex(registersPairTemp);
	registersPairTemp--;
	regPair1 = registersPairTemp >> 8;
	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
	pc++;
}


//Page 5
void Cpu::opcodeOperation_LD_aRP_R_RPI(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg)
{
	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
	memory.setMemoryOfIndex(registersPairTemp, reg);
	registersPairTemp++;
	regPair1 = (registersPairTemp >> 8);
	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
	pc++;
}

void Cpu::opcodeOperation_LD_aRP_R_RPD(uint8_t& regPair1, uint8_t& regPair2, const uint8_t& reg)
{
	uint16_t registersPairTemp = pairRegisters(regPair1, regPair2);
	memory.setMemoryOfIndex(registersPairTemp, reg);
	registersPairTemp--;
	regPair1 = (registersPairTemp >> 8);
	regPair2 = registersPairTemp & 0xFF;//HERE CONVERSION ISSUE
	pc++;
}


/*-------------------------------------16bits TRANSFER INSTRUCTIONS---------------------------------------*/

//Page 6 
void Cpu::opcodeOperation16bits_LD_RP_d16(uint8_t& regPair1, uint8_t& regPair2)
{
	pc++;
	regPair1 = memory.getMemoryOfIndex(pc + 1);
	regPair2 = memory.getMemoryOfIndex(pc);
	pc += 2;
}

void Cpu::opcodeOperation16bits_LD_RP_d16(uint16_t& registersPair)
{
	uint8_t regPair1 = registersPair >> 8;
	uint8_t regpair2 = registersPair & 0xFF;//HERE CONVERSION ISSUE
	opcodeOperation16bits_LD_RP_d16(regPair1, regpair2);
	registersPair = (regPair1 << 8) + regpair2;
	pc += 2;
}

void Cpu::opcodeOperation16bits_LD_RP_RP(uint16_t& registersPair, const uint8_t& regPairB1, const uint8_t& regPairB2)
{
	registersPair = (regPairB1 << 8);
	registersPair = regPairB2;
	pc++;
}

void Cpu::opcodeOperation16bits_PUSH_RP(const uint8_t& regPair1, const uint8_t& regPair2)
{
	memory.setMemoryOfIndex(sp - 1, regPair1);
	memory.setMemoryOfIndex(sp - 2, regPair2);
	sp -= 2;
	pc++;
}

void Cpu::opcodeOperation16bits_PUSH_RP(const uint8_t& regPair1, const Flag& flag)
{
	uint8_t flagTemp = flagToByte(flag);
	opcodeOperation16bits_PUSH_RP(regPair1, flagTemp);
}


//Page 7
void Cpu::opcodeOperation16bits_POP_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	regPair2 = memory.getMemoryOfIndex(sp);
	regPair1 = memory.getMemoryOfIndex(sp + 1);
	sp += 2;
	pc++;
}

void Cpu::opcodeOperation16bits_POP_RP(uint8_t& regPair1, Flag& flagPair)
{
	uint8_t temp = memory.getMemoryOfIndex(sp);
	flagPair.Z = (temp >> 7) & 0x1;
	flagPair.N = (temp >> 6) & 0x1;
	flagPair.H = (temp >> 5) & 0x1;
	flagPair.CY = (temp >> 4) & 0x1;
	regPair1 = memory.getMemoryOfIndex(sp + 1);
	sp += 2;
	pc++;
}

void Cpu::opcodeOperation16bits_LDHL_SP_e()
{
	int8_t e = memory.getMemoryOfIndex(pc + 1);//Is casting working (from uint8_t to int8_t)

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

	pc++;
}

void Cpu::opcodeOperation16bits_LD_a8_SP()
{
	pc++;
	memory.setMemoryOfIndex(memory.getMemoryOfIndex(pc), sp & 0xFF);;//HERE CONVERSION ISSUE
	memory.setMemoryOfIndex(memory.getMemoryOfIndex(pc + 1), (sp >> 8));
	pc += 2;
}


/*-------------------------------------8bits ARITHMETIC AND LOGICAL OPERATION INSTRUCTIONS---------------------------------------*/

//Page 8
void Cpu::operationOpcode_ADD_R_R(uint8_t& reg1, const uint8_t& reg2)
{
	reg1 = operationOpcode_ADD_ADC_subFunctionFlag(reg1, reg2);
	pc++;
}

void Cpu::operationOpcode_ADD_R_d8(uint8_t& reg)
{
	pc++;
	reg = operationOpcode_ADD_ADC_subFunctionFlag(reg, memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::operationOpcode_ADD_R_aRP(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
{
	reg = operationOpcode_ADD_ADC_subFunctionFlag(reg, memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));
	pc++;
}

void Cpu::operationOpcode_ADC_A_R_CY(const uint8_t& reg)
{
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, F.CY);
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, reg);
	pc++;
}

void Cpu::operationOpcode_ADC_A_d8_CY()
{
	pc++;
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, F.CY);
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::operationOpcode_ADC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, F.CY);
	A = operationOpcode_ADD_ADC_subFunctionFlag(A, memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));
	pc++;
}



uint8_t Cpu::operationOpcode_ADD_ADC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
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

		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
		carryTemp = (value1Temp & value2Temp) | (value1Temp & carryTemp) | (value2Temp & carryTemp);

		if ((i == 3) && carryTemp)
			carryBit3 = 1;

		if ((i == 7) && carryTemp)
			carryBit7 = 1;

		additionValue += calcResultTemp << i;
	}

	return additionValue;
}



//Page 9	

void Cpu::operationOpcode_SUB_A_R(const uint8_t& reg)
{
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, reg);
	pc++;
}

void Cpu::operationOpcode_SUB_A_d8()
{
	pc++;
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::operationOpcode_SUB_A_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));
	pc++;
}


void Cpu::operationOpcode_SBC_A_R_CY(const uint8_t& reg)
{
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, F.CY);
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, reg);
}

void Cpu::operationOpcode_SBC_A_d8_CY()
{
	pc++;
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, F.CY);
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::operationOpcode_SBC_A_aHL_CY(const uint8_t& regPair1, const uint8_t& regPair2)
{
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, F.CY);
	A = operationOpcode_SUB_SBC_subFunctionFlag(A, memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));
}



uint8_t Cpu::operationOpcode_SUB_SBC_subFunctionFlag(const uint8_t& reg, const uint8_t& value)
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

		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
		carryTemp = ((!(value1Temp ^ value2Temp)) & carryTemp) || (((!value1Temp) & value2Temp) & (!carryTemp));

		if ((i == 3) && carryTemp)
			borrowBit3 = 1;

		if ((i == 7) && carryTemp)
			borrowBit7 = 1;

		substractionValue += calcResultTemp << i;
	}

	return substractionValue;
}



//Page 10

void Cpu::operationOpcode_AND_R_R(uint8_t& reg1, const uint8_t& reg2)
{
	reg1 &= reg2;

	F.Z = (reg1 == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;

	pc++;
}

void Cpu::operationOpcode_AND_R_d8(uint8_t& reg1)
{
	pc++;
	reg1 &= memory.getMemoryOfIndex(pc);
	F.Z = (reg1 == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;
	pc++;
}

void Cpu::operationOpcode_AND_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
{
	reg &= memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	F.Z = (reg == 0);
	F.H = 1;
	F.N = 0;
	F.CY = 0;
	pc++;
}


void Cpu::operationOpcode_OR_R_R(uint8_t& reg1, const uint8_t& reg2)
{
	reg1 |= reg2;
	F.Z = (reg1 == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}

void Cpu::operationOpcode_OR_R_d8(uint8_t& reg1)
{
	pc++;
	reg1 |= memory.getMemoryOfIndex(pc);
	F.Z = (reg1 == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}

void Cpu::operationOpcode_OR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
{
	reg |= memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	F.Z = (reg == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}


void Cpu::operationOpcode_XOR_R_R(uint8_t& reg1, const uint8_t& reg2)
{
	reg1 ^= reg2;
	F.Z = (reg1 == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}

void Cpu::operationOpcode_XOR_R_d8(uint8_t& reg1)
{
	pc++;
	reg1 ^= memory.getMemoryOfIndex(pc);
	F.Z = (reg1 == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}

void Cpu::operationOpcode_XOR_R_aHL(uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
{
	reg ^= memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	F.Z = (reg == 0);
	F.H = 0;
	F.N = 0;
	F.CY = 0;
	pc++;
}


//Page 11
void Cpu::operationOpcode_CP_R_R(const uint8_t& reg1, const uint8_t& reg2)
{
	operationOpcode_CP_subFunctionFlag(reg1, reg2);
	pc++;
}

void Cpu::operationOpcode_CP_R_d8(const uint8_t& reg1)
{
	pc++;
	operationOpcode_CP_subFunctionFlag(reg1, memory.getMemoryOfIndex(pc));
	pc++;
}

void Cpu::operationOpcode_CP_R_aHL(const uint8_t& reg, const uint8_t& regPair1, const uint8_t& regPair2)
{
	operationOpcode_CP_subFunctionFlag(reg, memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));
	pc++;
}

void Cpu::operationOpcode_CP_subFunctionFlag(const uint8_t& reg1, const uint8_t& reg2)
{
	if (reg1 > reg2)
	{
		F.Z = 0;
		F.H = 1;
		F.CY = 0;
	}
	else if (reg1 < reg2)
	{
		F.Z = 0;
		F.H = 0;
		F.CY = 1;
	}
	else
	{
		F.Z = 1;
		F.H = 0;
		F.CY = 0;
	}

	F.N = 1;
}


void Cpu::operationOpcode_INC_R(uint8_t& reg)
{
	operationOpcode_INC_subFunctionFlag(reg);
	pc++;
}

void Cpu::operationOpcode_INC_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
{
	//operationOpcode_INC_subFunctionFlag(memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
	uint8_t memTemp = memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	operationOpcode_INC_subFunctionFlag(memTemp);
	pc++;
}

void Cpu::operationOpcode_INC_subFunctionFlag(uint8_t& reg)
{
	if (reg == 0xFF)
	{
		reg = 0;
		F.Z = 1;
		F.H = 1;
	}
	else
	{
		bool carryBit3 = false, carryBit7 = false;
		reg = binaryAddition(8, reg, 1, carryBit3, carryBit7);
		F.Z = 0;
		F.H = carryBit3;
	}

	F.N = 0;
}



void Cpu::operationOpcode_DEC_R(uint8_t& reg)
{
	operationOpcode_DEC_subFunctionFlag(reg);
	pc++;
}

void Cpu::operationOpcode_DEC_aHL(const uint8_t& regPair1, const uint8_t& regPair2)
{
	//operationOpcode_INC_subFunctionFlag(memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2)));//C++ initial value of reference to non-const must be an lvalue
	uint8_t memTemp = memory.getMemoryOfIndex(pairRegisters(regPair1, regPair2));
	operationOpcode_DEC_subFunctionFlag(memTemp);
	pc++;
}

void Cpu::operationOpcode_DEC_subFunctionFlag(uint8_t& reg)
{
	if (reg == 0x00)
	{
		reg = 0xFF;
		F.Z = 0;
		F.H = 1;
	}
	else if (reg == 0x01)
	{
		reg--;
		F.Z = 1;
		F.H = 0;
	}
	else
	{
		bool borrowBit3 = false, borrowBit7 = false;
		reg = binarySubstraction(8, reg, 1, borrowBit3, borrowBit7);
		F.Z = 0;
		F.H = borrowBit3;
	}

	F.N = 1;
}


/*-------------------------------------16bits ARITHMETIC OPERATION INSTRUCTIONS---------------------------------------*/

//Page 12

void Cpu::operationOpcode16bits_ADD_HL_RP(const uint16_t& regsPair)
{
	uint16_t regsPairHL = (H << 8) + L;
	bool carryBit11 = 0;
	bool carryBit15 = 0;
	regsPairHL = binaryAddition16bits(regsPairHL, regsPair, carryBit11, carryBit15);
	H = regsPairHL >> 8;
	L = regsPairHL & 0b00001111;
	F.H = carryBit11;
	F.N = 0;
	F.CY = carryBit15;
	pc++;
}

void Cpu::operationOpcode16bits_ADD_SP_e()
{
	pc++;
	bool carryBit11 = 0;
	bool carryBit15 = 0;
	uint16_t e = memory.getMemoryOfIndex(pc);
	sp = binaryAddition16bits(sp, e, carryBit11, carryBit15);
	F.H = carryBit11;
	F.CY = carryBit15;
	F.N = 0;
	F.Z = 0;
	pc++;
}

void Cpu::operationOpcode16bits_INC_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	uint16_t regsPair = pairRegisters(regPair1, regPair2);
	regsPair++;
	regPair1 = regsPair >> 8;
	regPair2 = regsPair & 0b00001111;
	pc++;
}

void Cpu::operationOpcode16bits_INC_RP(uint16_t& regsPair)
{
	regsPair++;
	pc++;
}

void Cpu::operationOpcode16bits_DEC_RP(uint8_t& regPair1, uint8_t& regPair2)
{
	uint16_t regsPair = pairRegisters(regPair1, regPair2);
	regsPair--;
	regPair1 = regsPair >> 8;
	regPair2 = regsPair & 0b00001111;
	pc++;
}

void Cpu::operationOpcode16bits_DEC_RP(uint16_t& regsPair)
{
	regsPair--;
	pc++;
}


int Cpu::binaryAddition16bits(const int& value1, const int& value2, bool& carryBit11, bool& carryBit15)
{
	int value1Temp = value1;
	int value2Temp = value2;
	bool carryTemp = 0;
	int calcResultTemp = 0;

	int additionValue = 0;

	for (int i = 0; i < 16; i++)
	{
		value1Temp = (value1 >> i) & 0b1;
		value2Temp = (value2 >> i) & 0b1;

		calcResultTemp = (value1Temp ^ value2Temp) ^ carryTemp;
		carryTemp = (value1Temp & value2Temp) | (value1Temp & carryTemp) | (value2Temp & carryTemp);

		if ((i == 11) && carryTemp)
			carryBit11 = 1;

		if ((i == 15) && carryTemp)
			carryBit15 = 1;

		additionValue += calcResultTemp << i;
	}

	return additionValue;
}



/*-------------------------------------ROTATE SHIFT INSTRUCTION---------------------------------------*/
//Page 13	(p98)


void Cpu::operationOpcode_RLCA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = A >> 7;
	A <<= 1;
	A &= 0b11111110;
	A |= F.CY;
	pc++;
}

void Cpu::operationOpcode_RLA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = A >> 7;
	A <<= 1;
	A &= 0b11111110;
	A |= oldCarry;
	pc++;
}


void Cpu::operationOpcode_RRCA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = A & 0x1;
	A >>= 1;
	A &= 0b01111111;
	A |= (F.CY << 7);
	pc++;
}

void Cpu::operationOpcode_RRA()
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = A & 0x1;
	A >>= 1;
	A &= 0b01111111;
	A |= (oldCarry << 7);
	pc++;
}


/*-----------------------------------------CB OPCODES OPERATIONS-----------------------------------------------*/

//Page 14	(p99)
void Cpu::operationOpcode_RLC_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = reg >> 7;
	reg <<= 1;
	reg &= 0b11111110;
	reg |= F.CY;
	pc++;
}

void Cpu::operationOpcode_RLC_aHL()
{
	uint8_t temp = memory.getMemoryOfIndex(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = temp >> 7;
	temp <<= 1;
	temp &= 0b11111110;
	temp |= F.CY;
	memory.setMemoryOfIndex(pairRegisters(H, L), temp);
	pc++;
}


void Cpu::operationOpcode_RL_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	bool oldCarry = F.CY;
	F.CY = reg >> 7;
	reg <<= 1;
	reg &= 0b11111110;
	reg |= oldCarry;
	F.Z = (reg == 0);
	pc++;
}

void Cpu::operationOpcode_RL_aHL()
{
	uint8_t temp = memory.getMemoryOfIndex(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	bool oldCarry = F.CY;
	F.CY = temp >> 7;
	temp <<= 1;
	temp &= 0b11111110;
	temp |= oldCarry;
	memory.setMemoryOfIndex(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	pc++;
}


//Page 15
void Cpu::operationOpcode_RRC_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.CY = reg & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	reg |= (F.CY << 7);
	F.Z = (reg == 0);
	pc++;
}

void Cpu::operationOpcode_RRC_aHL()
{
	uint8_t temp = memory.getMemoryOfIndex(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	F.CY = temp & 0x1;
	temp >>= 1;
	temp &= 0b01111111;
	temp |= (F.CY << 7);
	memory.setMemoryOfIndex(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	pc++;
}

void Cpu::operationOpcode_RR_R(uint8_t& reg)
{
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = reg & 0x1;
	reg >>= 1;
	reg &= 0b01111111;
	reg |= (oldCarry << 7);
	F.Z = (reg == 0);
	pc++;
}

void Cpu::operationOpcode_RR_aHL()
{
	uint8_t temp = memory.getMemoryOfIndex(pairRegisters(H, L));
	F.H = 0;
	F.N = 0;
	F.Z = 0;
	bool oldCarry = F.CY;
	F.CY = temp & 0x1;
	temp >>= 1;
	temp &= 0b01111111;
	temp |= (oldCarry << 7);
	memory.setMemoryOfIndex(pairRegisters(H, L), temp);
	F.Z = (temp == 0);
	pc++;
}