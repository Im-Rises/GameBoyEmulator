#include "Spu.h"

#include "SDL2/include/SDL.h"

/*
* Explications:
*
*
* Frequency:
* The Spu seems to be working with machine cycles not clock cycles according to the formula below:
* To make a counter for the cycle accuracy, we need to divide the cpu frequency by the one from the timer/frequency of the element.
* Seeing the formulato of the frequency below ;
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
*
*/

Spu::Spu(Memory* memory)
{
	this->memory = memory;

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		cerr << "Error SDL audio init.\n" << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}




	///* Allocate a desired SDL_AudioSpec */
	//SDL_AudioSpec* desired = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec));

	///* Allocate space for the obtained SDL_AudioSpec */
	//SDL_AudioSpec* obtained = (SDL_AudioSpec*)malloc(sizeof(SDL_AudioSpec));

	///* 22050Hz - FM Radio quality */
	//desired->freq = 44100;

	///* 16-bit signed audio */
	//desired->format = AUDIO_S16LSB;

	///* Mono */
	//desired->channels = 0;

	///* Large audio buffer reduces risk of dropouts but increases response time */
	//desired->samples = 8192;

	///* Our callback function */
	//desired->callback = NULL;//Null because using SDL_QueueAudio()

	//desired->userdata = NULL;

	///* Open the audio device */
	//if (SDL_OpenAudio(desired, obtained) < 0) {
	//	cerr << "Couldn't open audio: %s\n" << SDL_GetError() << endl;
	//	exit(-1);
	//}
	///* desired spec is no longer needed */
	//free(desired);

	//SDL_AudioSpec* hardware_spec = obtained;

	//SDL_PauseAudio(0);



	sc2Enabled = false;
	sc2EnvelopeEnabled = false;
	sc2Envelope = 0;
	sc2Counter = 0;
	sc2FsCounter = 0;
	sc2Fs = 0;
	sc2WaveDutyPosition = 0;
	sc2Length = 0;





	sc1Counter = 0;
	sc3Counter = 0;
	sc4Counter = 0;
	sc2WaveDutyPosition = 0;
	sc3Counter = 0;
	sc3PreviousFreq = 0;
	sc3Step = 0;
	outputSc3 = 0;
}

Spu::~Spu()
{
	SDL_Quit();
}

void Spu::doSounds(const int& cycles)
{
	uint8 nr50 = memory->read(0xFF24);
	uint8 nr51 = memory->read(0xFF25);
	uint8 nr52 = memory->read(0xFF26);

	if (testBit(nr52, 7))//If sound is enable
	{
		if (testBit(nr52, 0))//if sound 1 is enable...
			doSound1(cycles);
		if (testBit(nr52, 1))
			doSound2(cycles);
		if (testBit(nr52, 2))
			doSound3(cycles);
		if (testBit(nr52, 3))
			doSound4(cycles);

		//Handle sound with nr50 and nr51

	}
}


void Spu::doSound1(const int& cycles)
{
	//uint8 nr10 = memory->read(0xFF10);

	//uint8 sweepShiftnumber = nr10 & 0b00000111;
	//bool sweepIncreaseDecrease = testBit(nr10, 3);//0:Addition		1:Substraction

	//uint16 frequency = sc1PreviousFreq + sc1PreviousFreq / 2;

	//sc1PreviousFreq = sweepShiftnumber;
}

void Spu::doSound2(const int& cycles)
{
	uint8 nr21 = memory->read(0xFF16);
	uint8 nr22 = memory->read(0xFF17);
	uint8 nr24 = memory->read(0xFF19);

	uint8 waveFormDutyPattern = (nr21 >> 6);

	if (sc2Counter <= 0)
	{
		uint16 frequency = ((nr24 & 0b00000111) << 8) | memory->read(0xFF18);
		sc2Counter = 2 * (frequency - 2048);
		sc2WaveDutyPosition++;
		sc2WaveDutyPosition %= 8;
	}
	else
	{
		sc2Counter--;
	}

	sc2FsCounter++;

	if (sc2FsCounter == 8192)
	{
		sc2FsCounter = 0;
		sc2Fs++;
		sc2Fs %= 8;


		//Handle length

		if (((sc2Fs % 2) == 0) && testBit(nr24, 6) && (sc2Length > 0))
		{
			sc2Length--;
			memory->write(0xFF19, (nr21 & 0b11000000) | (sc2Length & 0b00111111));

			if (sc2Length <= 0)
			{
				sc2Enabled = false;
			}
		}

		//Handle enveloppe
		if (sc2Fs == 7 && sc2EnvelopeEnabled && ((nr22 & 0b00000111) > 0)) {
			sc2Envelope--;
			if (sc2Envelope <= 0) {
				sc2Envelope = nr22 & 0b00000111;
				sc2Amplitude += (testBit(nr22, 3) ? 1 : -1);

				if (sc2Amplitude >= 0 && sc2Amplitude <= 15)
				{
					
				}
				else
				{
					sc2EnvelopeEnabled = false;
				}

			}
		}

	}

}

void Spu::doSound3(const int& cycles)
{
	if (testBit(memory->read(0xFF1A), 7))//If sound is enable
	{
		uint8 soundLength = 256 - memory->read(0xFF1B);

		uint8 nr34 = memory->read(0xFF1E);
		bool doSound = false;

		if (testBit(nr34, 6))//If counter enable
		{
			soundLength--;
			memory->write(0xFF1B, soundLength);
			sc3Reset();
		}
		else//if counter disbale
		{
			doSound = true;
		}

		if (soundLength > 0 || doSound)
		{
			uint8 stepAmplitude = memory->read(0xFF30 + sc3Step / 2);

			if ((sc3Step % 2) == 0)
			{
				stepAmplitude >>= 4;
			}
			else
			{
				stepAmplitude &= 0x0F;
			}

			sc3Step++;
			sc3Step %= 32;


			uint16_t frequency = memory->read(0xFF1D) + ((nr34 & 0b00000111) << 8);

			switch (memory->read(0xFF1C))//Output Waveform's form
			{
			case(0b00000000):
			{
				outputSc3 = 0;
				break;
			}
			case(0b00100000):
			{
				outputSc3 = stepAmplitude;
				break;
			}
			case(0b01000000):
			{
				outputSc3 = stepAmplitude >> 1;
				break;
			}
			case(0b01100000):
			{
				outputSc3 = stepAmplitude >> 2;
				break;
			}
			}



			//Do sound


			sc3PreviousFreq = frequency;
		}
		else
		{
			if (testBit(nr34, 7))
			{
				sc3Reset();
			}
		}
	}
}

void Spu::sc3Reset()
{
	sc3Step = 0;
}



void Spu::doSound4(const int& cycles)
{

}
