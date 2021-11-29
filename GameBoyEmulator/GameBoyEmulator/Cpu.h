#ifndef DEF_CPU
#define DEF_CPU

#include <iostream>
//using namespace std;

class Cpu {

private:

	uint8_t A;					//Accumulator A
	uint8_t B, C, D, E, H, L;	//Auxiliary registers of the accumulator A
	uint16_t pc;				//Program counter
	uint16_t sp;				//Stack pointer

	struct Flag {
		bool Z;					//Set to 1 when the result of an operation is 0
		bool N;					//Set to 1 following execution of the substraction instruction, regardless of the result
		bool H;					//Set to 1 when an operation results in carrying from or borrowing to bit 3
		bool CY;				//Set to 1 when an operation results in carrying from or borrowing to bit 7
	} F;						//Auxiliary register of the accumulator, consist of 4 flags that are set and reset according to the results of instruction execution

public:
	Cpu();
	void readOpcode();
	void executeOpcode();
	//Continue p85
};

#endif
