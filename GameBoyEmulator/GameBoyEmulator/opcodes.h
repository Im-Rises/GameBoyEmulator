#ifndef DEF_OPOCDES
#define DEF_OPOCDES

#include <iostream>

using namespace std;

struct Opcode {
	string name;
	uint8_t value;
	uint8_t cycle;
};

static const Opcode oneByeOpcode[0XFF] = {
	{"NOP",0x00,1},
	{}
};

static const Opcode twoByesOpcode[0XFF] = {

};

#endif