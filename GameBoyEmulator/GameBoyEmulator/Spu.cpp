#include "Spu.h"

#include "SDL2/include/SDL.h"

Spu::Spu(Memory* memory)
{
	this->memory = memory;
	sc1PreviousFreq = 0;
	sc3Step = 0;
	outputSc3 = 0;
}

void Spu::doSounds(const int& cycles)
{

	doSound1(cycles);
	doSound2(cycles);
	doSound3(cycles);
	doSound4(cycles);

}


void Spu::doSound1(const int& cycles)
{
	uint8 nr10 = memory->read(0xFF10);

	uint8 sweepShiftnumber = nr10 & 0b00000111;
	bool sweepIncreaseDecrease = testBit(nr10, 3);//0:Addition		1:Substraction

	uint16 frequency = sc1PreviousFreq + sc1PreviousFreq / 2;

	sc1PreviousFreq = sweepShiftnumber;
}

void Spu::doSound2(const int& cycles)
{

}

void Spu::doSound3(const int& cycles)
{
	if (testBit(memory->read(0xFF1A), 7))//If sound is enable
	{
		uint8 soundLength = 256 - memory->read(0xFF1B);

		uint8 nr34 = memory->read(0xFF1E);
		uint16_t frequency = memory->read(0xFF1D) + ((nr34 & 0b00000111) << 8);
		bool doSound = false;

		if (testBit(nr34, 7))
		{
			sc3Reset();
			return;
		}

		if (testBit(nr34, 6))
		{
			soundLength--;
			memory->write(0xFF1B, soundLength);
		}
		else
		{
			doSound = true;
		}

		if (soundLength > 0 || doSound)
		{
			uint8 stepAmplitude;

			if ((sc3Step % 2) == 0)
			{
				stepAmplitude = (memory->read(0xFF30) & 0xF0) >> 4;
			}
			else
			{
				stepAmplitude = memory->read(0xFF30) & 0x0F;
				sc3Step++;
			}


			switch (memory->read(0xFF1C))
			{
			case(0b00000000):
			{
				outputSc3 = 0;
				break;
			}
			case(0b00100000):
			{
				outputSc3 = stepAmplitude * frequency;
				break;
			}
			case(0b01000000):
			{
				outputSc3 = (stepAmplitude >> 1) * frequency;
				break;
			}
			case(0b01100000):
			{
				outputSc3 = (stepAmplitude >> 2) * frequency;
				break;
			}
			}



			//Do sound



		}
		else
		{
			sc3Reset();
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
