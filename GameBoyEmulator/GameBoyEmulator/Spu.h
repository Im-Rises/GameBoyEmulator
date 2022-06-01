#ifndef DEF_SPU
#define DEF_SPU

#include "binaryLib.h"
#include "Memory.h"
#include <queue>

class Spu
{
private:
	Memory* memory = nullptr;

public:
	Spu(Memory* memory);
	~Spu();
	void doSounds(const int& cycles);

private:
	// Buffers that will store for a certain cyles all sounds data for all 4 channels
	queue<float> channer1buffer;
	queue<float> channer2buffer;
	queue<float> channer3buffer;
	queue<float> channer4buffer;

	//Wave format duty for channels
	bool waveFormDuty[4][8] = {
		{0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 0}
	};

	// Variables for all 4 channels

	//ch1
	uint16 sc1Counter;

	//ch2
	bool sc2Enabled;
	bool sc2EnvelopeEnabled;
	uint8 sc2Envelope;
	int16 sc2Amplitude;
	uint16 sc2Counter;
	uint16 sc2Length;
	uint16 sc2FsCounter;
	uint8 sc2Fs;
	uint8 sc2WaveDutyPosition;

	//ch3
	uint16 sc3Counter;
	uint16 sc3PreviousFreq;
	uint8 sc3Step;
	int outputSc3;

	//ch4
	uint16 sc4Counter;

private:
	void doSound1(const int& cycles);
	void doSound2(const int& cycles);
	void doSound3(const int& cycles);
	void doSound4(const int& cycles);

public:
	void resetSound1();
	void resetSound2();
	void resetSound3();
	void resetSound4();
};

#endif
