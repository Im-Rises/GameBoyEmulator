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
	~Spu();
	void doSounds(const int& cycles);

private:
	bool waveFormDuty[4][8] = {
		{0,0,0,0,0,0,0,1},
		{0,0,0,0,0,0,1,1},
		{0,0,0,0,1,1,1,1},
		{1,1,1,1,1,1,0,0}
	};

	uint16 sc1Counter;


	bool sc2Enabled;
	bool sc2EnvelopeEnabled;
	uint8 sc2Envelope;
	int16 sc2Amplitude;
	uint16 sc2Counter;
	uint16 sc2Length;
	uint16 sc2FsCounter;
	uint8 sc2Fs;
	uint8 sc2WaveDutyPosition;



	uint16 sc3Counter;
	uint16 sc4Counter;


	uint16 sc3PreviousFreq;
	uint8 sc3Step;
	int outputSc3;

private:
	void doSound1(const int& cycles);


	void doSound2(const int& cycles);


	void doSound3(const int& cycles);
	void sc3Reset();

	void doSound4(const int& cycles);
};

#endif