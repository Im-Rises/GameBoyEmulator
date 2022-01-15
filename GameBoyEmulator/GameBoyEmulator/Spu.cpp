#include "Spu.h"

#include "SDL2/include/SDL.h"

Spu::Spu(Memory* memory)
{
	this->memory = memory;
	sound1PreviousFreq = 0;
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

	uint16 frequency = sound1PreviousFreq + sound1PreviousFreq / 2;

	sound1PreviousFreq = sweepShiftnumber;
}

void Spu::doSound2(const int& cycles)
{

}

void Spu::doSound3(const int& cycles)
{

}

void Spu::doSound4(const int& cycles)
{

}


