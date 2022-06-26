#ifndef DEF_SPU
#define DEF_SPU

#include "binaryLib.h"
#include "Memory.h"
#include <queue>

class Spu
{
private:
	Memory* memory = nullptr;
	bool soundOnOff = false;

public:
	Spu(Memory* memory);
	~Spu();
	void doSounds(const int& cycles);

private:
	int samplePerSecond = 44100;

	int cycleCounter = 0;

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
	int16 sc1Amplitude;
	int16 sc1Frequency;
	uint8 sc1WaveFormDutyIndex;


	//ch2
	uint16 sc2Counter;
	int16 sc2Amplitude;
	int16 sc2Frequency;
	uint8 sc2WaveFormDutyIndex;
	
	bool sc2Enabled;
	bool sc2EnvelopeEnabled;
	uint8 sc2Envelope;
	uint16 sc2Length;
	uint16 sc2FsCounter;
	uint8 sc2Fs;
	uint8 sc2WaveDutyPosition;
	uint8 sc3WaveFormDutyIndex;

	//ch3
	uint16 sc3Counter;
	int16 sc3Amplitude;
	int16 sc3Frequency;

	uint16 sc3PreviousFreq;
	uint8 sc3Step;
	int outputSc3;

	//ch4
	uint16 sc4Counter;
	int16 sc4Amplitude;
	int16 sc4Frequency;

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
