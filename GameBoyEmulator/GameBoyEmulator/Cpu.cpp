#include "Cpu.h"

Cpu::Cpu()
{
	A = 0;
	B = C = D = E = H = L = 0;
	pc = 0;
	sp = USER_PROGRAM_AREA;
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
	case(0x01): {break; }
	case(0x02): {break; }
	case(0x03): {break; }
	case(0x04): {break; }
	case(0x05): {break; }
	case(0x06): {opcodeOperation_LD_R_d8(B); break; }
	case(0x07): {break; }
	case(0x08): {break; }
	case(0x09): {break; }
	case(0x0A): {break; }
	case(0x0B): {break; }
	case(0x0C): {break; }
	case(0x0D): {break; }
	case(0x0E): {opcodeOperation_LD_R_d8(C); break; }
	case(0x0F): {break; }
	case(0x10): {break; }
	case(0x11): {break; }
	case(0x12): {break; }
	case(0x13): {break; }
	case(0x14): {break; }
	case(0x15): {break; }
	case(0x16): {opcodeOperation_LD_R_d8(D); break; }
	case(0x17): {break; }
	case(0x18): {break; }
	case(0x19): {break; }
	case(0x1A): {break; }
	case(0x1B): {break; }
	case(0x1C): {break; }
	case(0x1D): {break; }
	case(0x1E): {opcodeOperation_LD_R_d8(E); break; }
	case(0x1F): {break; }
	case(0x20): {break; }
	case(0x21): {break; }
	case(0x22): {break; }
	case(0x23): {break; }
	case(0x24): {break; }
	case(0x25): {break; }
	case(0x26): {opcodeOperation_LD_R_d8(H); break; }
	case(0x27): {break; }
	case(0x28): {break; }
	case(0x29): {break; }
	case(0x2A): {break; }
	case(0x2B): {break; }
	case(0x2C): {break; }
	case(0x2D): {break; }
	case(0x2E): {opcodeOperation_LD_R_d8(L); break; }
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
	case(0x3E): {opcodeOperation_LD_R_d8(A); break; }
	case(0x3F): {break; }
	case(0x40): {opcodeOperation_LD_R_R(B, B); break; }
	case(0x41): {opcodeOperation_LD_R_R(B, C); break; }
	case(0x42): {opcodeOperation_LD_R_R(B, D); break; }
	case(0x43): {opcodeOperation_LD_R_R(B, E); break; }
	case(0x44): {opcodeOperation_LD_R_R(B, H); break; }
	case(0x45): {opcodeOperation_LD_R_R(B, L); break; }
	case(0x46): {opcodeOperation_LD_R_RP(B, pairRegisters(H, L)); break; }
	case(0x47): {opcodeOperation_LD_R_R(B, A); break; }
	case(0x48): {opcodeOperation_LD_R_R(C, B); break; }
	case(0x49): {opcodeOperation_LD_R_R(C, C); break; }
	case(0x4A): {opcodeOperation_LD_R_R(C, D); break; }
	case(0x4B): {opcodeOperation_LD_R_R(C, E); break; }
	case(0x4C): {opcodeOperation_LD_R_R(C, H); break; }
	case(0x4D): {opcodeOperation_LD_R_R(C, L); break; }
	case(0x4E): {opcodeOperation_LD_R_RP(C, pairRegisters(H, L)); break; }
	case(0x4F): {opcodeOperation_LD_R_R(C, A); break; }
	case(0x50): {opcodeOperation_LD_R_R(D, B); break; }
	case(0x51): {opcodeOperation_LD_R_R(D, C); break; }
	case(0x52): {opcodeOperation_LD_R_R(D, D); break; }
	case(0x53): {opcodeOperation_LD_R_R(D, E); break; }
	case(0x54): {opcodeOperation_LD_R_R(D, H); break; }
	case(0x55): {opcodeOperation_LD_R_R(D, L); break; }
	case(0x56): {opcodeOperation_LD_R_RP(D, pairRegisters(H, L)); break; }
	case(0x57): {opcodeOperation_LD_R_R(D, A); break; }
	case(0x58): {opcodeOperation_LD_R_R(E, B); break; }
	case(0x59): {opcodeOperation_LD_R_R(E, C); break; }
	case(0x5A): {opcodeOperation_LD_R_R(E, D); break; }
	case(0x5B): {opcodeOperation_LD_R_R(E, E); break; }
	case(0x5C): {opcodeOperation_LD_R_R(E, H); break; }
	case(0x5D): {opcodeOperation_LD_R_R(E, L); break; }
	case(0x5E): {opcodeOperation_LD_R_RP(E, pairRegisters(H, L)); break; }
	case(0x5F): {opcodeOperation_LD_R_R(E, A); break; }
	case(0x60): {opcodeOperation_LD_R_R(H, B); break; }
	case(0x61): {opcodeOperation_LD_R_R(H, C); break; }
	case(0x62): {opcodeOperation_LD_R_R(H, D); break; }
	case(0x63): {opcodeOperation_LD_R_R(H, E); break; }
	case(0x64): {opcodeOperation_LD_R_R(H, H); break; }
	case(0x65): {opcodeOperation_LD_R_R(H, L); break; }
	case(0x66): {opcodeOperation_LD_R_RP(H, pairRegisters(H, L)); break; }
	case(0x67): {opcodeOperation_LD_R_R(H, A); break; }
	case(0x68): {opcodeOperation_LD_R_R(L, B); break; }
	case(0x69): {opcodeOperation_LD_R_R(L, C); break; }
	case(0x6A): {opcodeOperation_LD_R_R(L, D); break; }
	case(0x6B): {opcodeOperation_LD_R_R(L, E); break; }
	case(0x6C): {opcodeOperation_LD_R_R(L, H); break; }
	case(0x6D): {opcodeOperation_LD_R_R(L, L); break; }
	case(0x6E): {opcodeOperation_LD_R_RP(L, pairRegisters(H, L)); break; }
	case(0x6F): {opcodeOperation_LD_R_R(L, A); break; }
	case(0x70): {opcodeOperation_LD_RP_R(pairRegisters(H, L), B); break; }//REPRENDRE ICI
	case(0x71): {break; }
	case(0x72): {break; }
	case(0x73): {break; }
	case(0x74): {break; }
	case(0x75): {break; }
	case(0x76): {break; }
	case(0x77): {break; }
	case(0x78): {opcodeOperation_LD_R_R(A, B); break; }
	case(0x79): {opcodeOperation_LD_R_R(A, C); break; }
	case(0x7A): {opcodeOperation_LD_R_R(A, D); break; }
	case(0x7B): {opcodeOperation_LD_R_R(A, E); break; }
	case(0x7C): {opcodeOperation_LD_R_R(A, H); break; }
	case(0x7D): {opcodeOperation_LD_R_R(A, L); break; }
	case(0x7E): {opcodeOperation_LD_R_RP(A, pairRegisters(H, L)); break; }
	case(0x7F): {opcodeOperation_LD_R_R(A, A); break; }
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
	case(0xCB): {executeOpcodeFollowingCB(); break; }
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

void Cpu::executeOpcodeFollowingCB()
{
	switch (memory.getMemoryOfIndex(pc++)) {
	case(0x00): {break; }
	case(0x01): {break; }
	case(0x02): {break; }
	case(0x03): {break; }
	case(0x04): {break; }
	case(0x05): {break; }
	case(0x06): {break; }
	case(0x07): {break; }
	case(0x08): {break; }
	case(0x09): {break; }
	case(0x0A): {break; }
	case(0x0B): {break; }
	case(0x0C): {break; }
	case(0x0D): {break; }
	case(0x0E): {break; }
	case(0x0F): {break; }
	case(0x10): {break; }
	case(0x11): {break; }
	case(0x12): {break; }
	case(0x13): {break; }
	case(0x14): {break; }
	case(0x15): {break; }
	case(0x16): {break; }
	case(0x17): {break; }
	case(0x18): {break; }
	case(0x19): {break; }
	case(0x1A): {break; }
	case(0x1B): {break; }
	case(0x1C): {break; }
	case(0x1D): {break; }
	case(0x1E): {break; }
	case(0x1F): {break; }
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

uint16_t Cpu::pairRegisters(uint8_t reg1, uint8_t reg2)
{
	return ((reg1 << 8) + reg2);
}

/*-----------------------------------------NORMAL OPCODES OPERATIONS------------------------------------------*/

void Cpu::opcodeOperation_LD_R_R(uint8_t& reg1, const uint8_t& reg2) {
	reg1 = reg2;
}

void Cpu::opcodeOperation_LD_R_d8(uint8_t& reg)
{
	pc++;
	reg = memory.getMemoryOfIndex(pc);
}

void Cpu::opcodeOperation_LD_R_RP(uint8_t& reg, const uint16_t& registersPair)
{
	reg = registersPair;
}

void Cpu::opcodeOperation_LD_RP_R(uint16_t& registersPair, const uint8_t& reg)
{
	registersPair = reg;
}

/*-----------------------------------------CB OPCODES OPERATIONS-----------------------------------------------*/