#ifndef DEF_SPU
#define DEF_SPU

#include "binaryLib.h"
#include "Memory.h"

class Spu
{
private:
	Memory* memory;

public:
	Spu(Memory* memory);
	void doSounds(const int& cycles);

private:
	void doSound1(const int& cycles);
	uint8 sc1PreviousFreq;


	void doSound2(const int& cycles);


	void doSound3(const int& cycles);
	uint8 sc3Step;
	uint16 outputSc3;
	void sc3Reset();
	
	void doSound4(const int& cycles);
};

#endif