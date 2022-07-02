#include "Spu.h"

#include "SDL2/include/SDL.h"

/*
* Explanation:
*
*
* Frequency:
* The Spu seems to be working with machine cycles not clock cycles according to the formula below.
* To make a counter for the cycle accuracy, we need to divide the cpu frequency by the one from the timer/frequency of the element.
* Seeing the formula of the frequency below ;
* f = 4194304 / (4 x 2 x (2048 - X)) Hz
* If we divide the CPU M-Cycles frequency by the frequency of the timer thant we obtain
* scTimer = 2 * (2048 - freqData)
*
*	4194304 / 4 = M-Cycles
*
*
* Frame Sequencer FS:
* 512Hz
* so counter = 8192
*
*/


/*
Thanks a lot to this tutorial !!!
https://emudev.de/gameboy-emulator/bleeding-ears-time-to-add-audio/
*/


Spu::Spu(Memory* memory)
{
	this->memory = memory;

	SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
	SDL_Init(SDL_INIT_AUDIO);
	SDL_AudioSpec AudioSettings = {0};
	AudioSettings.freq = 44100;
	AudioSettings.format = AUDIO_F32SYS;
	AudioSettings.channels = 2;
	AudioSettings.samples = 1024;
	SDL_OpenAudio(&AudioSettings, 0);
	SDL_PauseAudio(0);

	volume = 1;

	//SC1
	sc1FScounter = 0;
	sc1FS = 0;
	sc1len = 0;
	sc1Enabled = false;
	sc1SweepPeriod = 0;
	sc1SweepEnabled = false;
	sc1SweepBuffer = 0;
	sc1Timer = 0;
	sc1WaveDutyIndex = 0;
	sc1Frequency = 0;
	sc1Amplitude = 0;
	sc1Envelope = 0;
	sc1EnvelopeEnabled = false;
	sc1pc = 95;

	//SC2
	sc2timer = 0;
	sc2WaveDutyIndex = 0;
	sc2FScounter = 0;
	sc2FS = 0;
	sc2len = 0;
	sc2Enabled = false;
	sc2EnvelopeEnabled = false;
	sc2Envelope = 0;
	sc2Amplitude = 0;
	sc2pc = 95;

	//SC3
	sc3timer=0;
	sc3WaveDutyIndex=0;
	sc3pc = 95;
	sc3Enabled=false;
	sc3FScounter=0;
	sc3FS=0;
	sc3len=0;

	//SC4
	sc4FScounter=0;
	sc4FS = 0;
	sc4len = 0;
	sc4Enabled = false;
	sc4envelope = 0;
	sc4Amplitude = 0;
	sc4timer = 0;
	sc4lfsr = 0;
	sc4pc = 95;
	sc4EnvelopeEnabled=false;
}

Spu::~Spu()
{
	SDL_Quit();
}

void Spu::doSounds(const int& cycles)
{
	doSound1(cycles);
	doSound2(cycles);
	doSound3(cycles);
	doSound4(cycles);

	if (channel1buffer.size() >= 100 && channel2buffer.size() >= 100 && channel3buffer.size() >= 100 && channel4buffer.size() >= 100)
	{
		for (int i = 0; i < 100; i++)
		{
			float res = 0;
			res += channel1buffer.front() * volume;
			res += channel2buffer.front() * volume;
			res += channel3buffer.front() * volume;
			res += channel4buffer.front() * volume;

			channel1buffer.pop();
			channel2buffer.pop();
			channel3buffer.pop();
			channel4buffer.pop();

			audioMixer.push_back(res);
		}

		SDL_QueueAudio(1, audioMixer.data(), audioMixer.size() * sizeof(float)); // Need to receive the size in byte!

		audioMixer.clear();

		while (SDL_GetQueuedAudioSize(1) > 4096 * 4) {}
	}
}


void Spu::doSound1(int cycles)
{
	while (cycles--)
	{
		sc1FScounter++;
		if (sc1FScounter == 8192)
		{
			sc1FScounter = 0;
			++sc1FS %= 8;
			
			if ((sc1FS % 2 == 0) && sc1len && ((memory->read(0xff14) >> 6) & 1))
			{
				sc1len--;
				if (sc1len <= 0)
				{
					sc1Enabled = false;
				}
			}
		}
		
		if ((sc1FS == 2 || sc1FS == 6) && sc1FScounter == 0 && ((memory->read(0xff10) >> 4) & 7) && (
			memory->read(0xff10) & 7))
		{
			--sc1SweepPeriod;
			if (sc1SweepPeriod <= 0)
			{
				sc1SweepPeriod = (memory->read(0xff10) >> 4) & 7;
				if (sc1SweepPeriod == 0)
					sc1SweepPeriod = 8;
				if (((memory->read(0xff10) >> 4) & 7) && sc1SweepEnabled && (memory->read(0xff10) & 7))
				{
					int SC1sweepShift = memory->read(0xff10) & 7;
					int SC1sweepNegate = ((memory->read(0xff10) >> 3) & 1) ? -1 : 1;
					uint16_t newfreq = sc1SweepBuffer + ((sc1SweepBuffer >> SC1sweepShift) * SC1sweepNegate);
					if (newfreq < 2048 && SC1sweepShift)
					{
						sc1SweepBuffer = newfreq;
						memory->directWrite(0xff13, sc1SweepBuffer & 0xff);
						memory->directWrite(0xff14, (sc1SweepBuffer >> 8) & 7);
						if ((sc1SweepBuffer + ((sc1SweepBuffer >> SC1sweepShift) * SC1sweepNegate)) > 2047)
						{
							sc1Enabled = false;
							sc1SweepEnabled = false;
						}
					}
					if (newfreq > 2047)
					{
						sc1Enabled = false;
						sc1SweepEnabled = false;
					}
					if ((sc1SweepBuffer + ((sc1SweepBuffer >> SC1sweepShift) * SC1sweepNegate)) > 2047)
					{
						sc1Enabled = false;
						sc1SweepEnabled = false;
					}
				}
			}
		}
		
		if (sc1Timer <= 0x00)
		{
			uint16_t r = (((memory->read(0xff14) & 7) << 8) | memory->read(0xff13));
			sc1Timer = (2048 - r) * 4;
			
			++sc1WaveDutyIndex %= 8;
		}
		else
			sc1Timer--;
		
		int duty = memory->read(0xff11) >> 6;
		if (waveFormDuty[duty][sc1WaveDutyIndex] == 1)
			sc1Frequency = sc1Amplitude;
		else
			sc1Frequency = 0;
		
		if (sc1FS == 7 && sc1FScounter == 0 && (memory->read(0xff12) & 7) && sc1EnvelopeEnabled)
		{
			--sc1Envelope;
			if (sc1Envelope <= 0)
			{
				sc1Envelope = memory->read(0xff12) & 7;
				uint8_t newamp = sc1Amplitude + (((memory->read(0xff12) >> 3) & 1) ? 1 : -1);
				if (newamp <= 15)
				{
					sc1Amplitude = newamp;
					sc1Frequency = sc1Amplitude;
				}
				else
					sc1EnvelopeEnabled = false;
			}
		}

		if (!--sc1pc)
		{
			sc1pc = 95;
			if (sc1Enabled && (memory->read(0xff26) & 1) && (memory->read(0xff25) & 0x11))
			{
				channel1buffer.push((static_cast<float>(sc1Frequency)) / 100);
				channel1buffer.push((static_cast<float>(sc1Frequency)) / 100);
			}
			else
			{
				channel1buffer.push(0);
				channel1buffer.push(0);
			}
		}
	}
}

void Spu::doSound2(int cycles)
{
	while (cycles--)
	{
		if (sc2timer <= 0x00)
		{
			uint16_t r = (((memory->directRead(0xff19) & 7) << 8) | memory->directRead(0xff18));
			sc2timer = (2048 - r) * 4;
			++sc2WaveDutyIndex %= 8;
		}
		else
			sc2timer--;
		
		sc2FScounter++;
		if (sc2FScounter == 8192)
		{
			sc2FScounter = 0;
			++sc2FS %= 8;
			
			if (sc2FS % 2 == 0 && ((memory->directRead(0xff19) >> 6) & 1) && sc2len)
			{
				sc2len--;
				if (sc2len <= 0)
				{
					sc2Enabled = false;
				}
			}
			
			if (sc2FS == 7 && sc2EnvelopeEnabled && (memory->directRead(0xff17) & 7))
			{
				--sc2Envelope;
				if (sc2Envelope <= 0)
				{
					sc2Envelope = memory->directRead(0xff17) & 7;
					int8_t newamp = sc2Amplitude + (((memory->directRead(0xff17) >> 3) & 1) ? 1 : -1);
					if (newamp >= 0 && newamp <= 15)
						sc2Amplitude = newamp;
					else
						sc2EnvelopeEnabled = false;
				}
			}
		}

		if (!--sc2pc)
		{
			sc2pc = 95;
			if (sc2Enabled && (memory->directRead(0xff25) & 0x22) && (memory->directRead(0xff26) & 2))
			{
				int duty = memory->directRead(0xff16) >> 6;
				channel2buffer.push((waveFormDuty[duty][sc2WaveDutyIndex] == 1) ? ((float)sc2Amplitude / 100) : 0);
				channel2buffer.push((waveFormDuty[duty][sc2WaveDutyIndex] == 1) ? ((float)sc2Amplitude / 100) : 0);
			}
			else
			{
				channel2buffer.push(0);
				channel2buffer.push(0);
			}
		}
	}
}

void Spu::doSound3(int cycles)
{
	while (cycles--)
	{
		if (sc3timer <= 0x00)
		{
			uint16_t r = (((memory->directRead(0xff1e) & 7) << 8) | memory->directRead(0xff1d));
			sc3timer = (2048 - r) * 2;
			
			++sc3WaveDutyIndex %= 32;
		}
		else
			sc3timer--;

		if (!--sc3pc)
		{
			sc3pc = 95;
			if (sc3Enabled)
			{
				uint8_t wave = memory->directRead(0xff30 + (sc3WaveDutyIndex / 2));
				if (sc3WaveDutyIndex % 2)
				{
					wave = wave & 0xf;
				}
				else
				{
					wave = wave >> 4;
				}

				uint8_t vol = (memory->directRead(0xff1c) >> 5) & 3;
				if (vol)
					wave = wave >> (vol - 1);
				else
					wave = wave >> 4;
				
				if (memory->directRead(0xff1a) >> 7 && (memory->directRead(0xff25) & 0x44))
				{
					channel3buffer.push((float)wave / 100);
					channel3buffer.push((float)wave / 100);
				}
				else
				{
					channel3buffer.push(0);
					channel3buffer.push(0);
				}
			}
			else
			{
				channel3buffer.push(0);
				channel3buffer.push(0);
			}
		}
		
		sc3FScounter++;
		if (sc3FScounter == 8192)
		{
			sc3FScounter = 0;
			++sc3FS %= 8;
			
			if (sc3FS % 2 == 0 && ((memory->directRead(0xff1e) >> 6) & 1) && sc3len)
			{
				sc3len--;
				if (sc3len == 0)
				{
					sc3Enabled = false;
				}
			}
		}
	}
}


void Spu::doSound4(int cycles)
{
	while (cycles--)
	{
		sc4FScounter++;
		if (sc4FScounter == 8192)
		{
			sc4FScounter = 0;
			++sc4FS %= 8;
			
			if (sc4FS % 2 == 0 && ((memory->directRead(0xff23) >> 6) & 1) && sc4len)
			{
				sc4len--;
				if (sc4len == 0)
				{
					sc4Enabled= false;
				}
			}
			
			if (sc4FS== 7)
			{
				--sc4envelope;
				if (sc4envelope <= 0)
				{
					sc4envelope = memory->directRead(0xff21) & 7;
					if ((memory->directRead(0xff21) & 7) != 0)
					{
						int8_t newamp = sc4Amplitude + (((memory->directRead(0xff21) >> 3) & 1) ? 1 : -1);
						if (newamp >= 0 && newamp <= 15)
							sc4Amplitude= newamp;
					}
				}
			}
		}

		if (sc4timer <= 0x00)
		{
			sc4timer = sc4divisor[memory->directRead(0xff22) & 7] << (memory->directRead(0xff22) >> 4);
			
			uint8_t xor_res = (sc4lfsr & 0x1) ^ ((sc4lfsr & 0x2) >> 1);
			sc4lfsr >>= 1;
			sc4lfsr |= (xor_res << 14);
			if ((memory->directRead(0xff22) >> 3) & 0x1)
			{
				sc4lfsr |= (xor_res << 6);
				sc4lfsr &= 0x7f;
			}
		}
		else
			sc4timer--;

		if (!--sc4pc)
		{
			sc4pc = 95;
			if (sc4Enabled&& ((memory->directRead(0xff26) >> 3) & 1) && (memory->directRead(0xff21) & 0xf8) && (memory->directRead(0xff25) &
				0x88))
			{
				channel4buffer.push((sc4lfsr & 0x1) ? 0 : (float)sc4Amplitude / 100);
				channel4buffer.push((sc4lfsr & 0x1) ? 0 : (float)sc4Amplitude / 100);
			}
			else
			{
				channel4buffer.push(0);
				channel4buffer.push(0);
			}
		}
	}
}


void Spu::resetSound1(uint8 val)
{
	if (sc1len == 0)
		sc1len = 64 - val;
	
	sc1Enabled = true;
	
	sc1Amplitude = memory->read(0xff12) >> 4;
	
	sc1Envelope = memory->read(0xff12) & 7;
	sc1EnvelopeEnabled = true;
	
	uint16_t r = (((memory->read(0xff14) & 7) << 8) | memory->read(0xff13));
	sc1Timer = (2048 - r) * 4;
	
	sc1SweepPeriod = (memory->read(0xff10) >> 4) & 7;
	int SC1sweepShift = memory->read(0xff10) & 7;
	int SC1sweepNegate = ((memory->read(0xff10) >> 3) & 1) ? -1 : 1;
	if (sc1SweepPeriod && SC1sweepShift)
		sc1SweepEnabled = true;
	else
		sc1SweepEnabled = false;
	sc1SweepBuffer = (((memory->read(0xff14) & 7) << 8) | memory->read(0xff13));
	if (SC1sweepShift)
	{
		if ((sc1SweepBuffer + ((sc1SweepBuffer >> SC1sweepShift) * SC1sweepNegate)) > 2047)
		{
			sc1SweepEnabled = false;
			sc1Enabled = false;
		}
	}
	
	if ((memory->read(0xff12) >> 3) == 0x0)
		sc1Enabled = false;
}

void Spu::resetSound2(uint8 val)
{
	if (!sc2len)
		sc2len = 64 - val;
	sc2Enabled = true;
	sc2Amplitude = memory->directRead(0xff17) >> 4;
	sc2Envelope = memory->directRead(0xff17) & 7;
	sc2EnvelopeEnabled = true;
	
	if ((memory->directRead(0xff17) >> 3) == 0x0)
		sc2Enabled = false;
}

void Spu::resetSound3(uint8 val)
{
	uint16_t r = (((memory->directRead(0xff1e) & 7) << 8) | memory->directRead(0xff1d));
	sc3timer = (2048 - r) * 2;
	if (!sc3len)
		sc3len = 256 - val;
	sc3Enabled = true;
	sc3WaveDutyIndex = 0;
	
	if ((memory->directRead(0xff1a) >> 6) == 0x0)
		sc3Enabled = false;
}

void Spu::resetSound4(uint8 val)
{
	if (!sc4len)
		sc4len = 64 - val;
	sc4Enabled= true;
	sc4timer= sc4divisor[memory->directRead(0xff22) & 0x7] << (memory->directRead(0xff22) >> 4);
	sc4lfsr = 0x7fff;
	sc4Amplitude = memory->directRead(0xff21) >> 4;
	sc4envelope = memory->directRead(0xff21) & 7;
	sc4EnvelopeEnabled = true;
	
	if ((memory->directRead(0xff21) >> 3) == 0x0)
		sc4Enabled= false;
}
