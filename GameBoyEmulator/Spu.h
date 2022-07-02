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
	void reset();
	void doSounds(const int& cycles);

private:
	int samplePerSecond = 44100;

	int cycleCounter = 0;

	float volume = 0.5;

	/*
		SC1	Square
		- Wave Channel
		– Sweep
		– Volume Envelope
		– Length Counter

		SC2	Square - Wave Channel
		– Volume Envelope
		– Length Counter

		SC3	Waveform Channel
		– Length Counter

		SC4	Noise Channel
		– Volume Envelope
	*/

	// Buffers that will store for a certain cyles all sounds data for all 4 channels
	queue<float> channel1buffer;
	queue<float> channel2buffer;
	queue<float> channel3buffer;
	queue<float> channel4buffer;

	vector<float> audioMixer;

	//Wave format duty for channels
	bool waveFormDuty[4][8] = {
		{0, 0, 0, 0, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 1, 1},
		{0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 0}
	};

	// Variables for all 4 channels

	//ch1
	uint16 sc1FScounter;
	uint8 sc1FS;
	uint8 sc1len;
	bool sc1Enabled;
	uint8 sc1SweepPeriod;
	bool sc1SweepEnabled;
	uint32 sc1SweepBuffer;
	uint32 sc1Timer;
	uint8 sc1WaveDutyIndex;
	int16 sc1Frequency;
	int16 sc1Amplitude;
	uint8 sc1Envelope;
	bool sc1EnvelopeEnabled;
	uint8 sc1pc;

	//ch2
	uint32 sc2timer;
	uint8 sc2WaveDutyIndex;
	uint16 sc2FScounter;
	uint8 sc2FS;
	uint8 sc2len;
	bool sc2Enabled;
	bool sc2EnvelopeEnabled;
	uint8 sc2Envelope;
	int16 sc2Amplitude;
	uint8 sc2pc;

	//ch3
	uint32 sc3timer;
	uint8 sc3WaveDutyIndex;
	uint8 sc3pc;
	bool sc3Enabled;
	uint16 sc3FScounter;
	uint8 sc3FS;
	uint8 sc3len;

	//ch4
	uint16 sc4FScounter;
	uint8 sc4FS;
	uint8 sc4len;
	bool sc4Enabled;
	uint8 sc4envelope;
	int16 sc4Amplitude;
	uint32 sc4timer;
	const uint8 sc4divisor[8] = { 8, 16, 32, 48, 64, 80, 96, 112 };
	uint16 sc4lfsr = 0;
	uint8 sc4pc;
	bool sc4EnvelopeEnabled;

private:

	void doSound1(int cycles);
	void doSound2(int cycles);
	void doSound3(int cycles);
	void doSound4(int cycles);

public:
	void resetSound1(uint8 val);
	void resetSound2(uint8 val);
	void resetSound3(uint8 val);
	void resetSound4(uint8 val);
};

#endif
