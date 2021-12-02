#include <iostream>

#include "Memory.h"
#include "Cpu.h"

//struct Flag {				//Flag structure:
//	bool Z;					//Set to 1 when the result of an operation is 0
//	bool N;					//Set to 1 following execution of the substraction instruction, regardless of the result
//	bool H;					//Set to 1 when an operation results in carrying from or borrowing to bit 3
//	bool CY;				//Set to 1 when an operation results in carrying from or borrowing to bit 7
//};

int main(int argc, char* argv[])
{
	//Flag flagPair;
	//uint8_t temp = 0b10101010;
	//flagPair.Z = (temp >> 7) & 0x1;
	//flagPair.N = (temp >> 6) & 0x1;
	//flagPair.H = (temp >> 5) & 0x1;
	//flagPair.CY = (temp >> 4) & 0x1;


	//Algorithm to calculate the carry of bit 3 and 7
	int trueValue1 = 0b10101010, trueValue2 = 0b11001100;//Estimated result 101110110
	int result = 0;
	int trueResult = 0;
	bool carry = 0;
	for (int i = 0; i < 8; i++)
	{
		int value1 = ((trueValue1 & (0x00000001 << i)) >> i);
		int value2 = ((trueValue2 & (0x00000001 << i)) >> i);
		//if (value1 > 1)
		//	value1 = 1;
		//if (value2 > 2)
		//	value2 = 1;

		if (((value1 & 0x1)) && ((value2 & 0x1)))//1+1
		{
			if (carry)
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			carry = 1;
		}
		else if ((((value1 & 0b1) == 1) && ((value2 & 0b1) == 0)) || (((value1 & 0b1) == 0) && ((value2 & 0b1) == 1)))//0+1 OR 1+0
		{
			if (carry)
			{
				result = 0;
				carry = 1;
			}
			else
			{
				result = 1;
				carry = 0;
			}
		}
		else//0+0
		{
			if (carry)
			{
				result = 1;
			}
			else
			{
				result = 0;
			}
			carry = 0;
		}
		trueResult = result << i;
		std::cout << "Bit:" << i << " value:" << result << " Carry:" << carry << std::endl;
		//std::cout << "TrueResult: " << trueResult << std::endl;
		//std::cout << value1 << std::endl;
	}

	//std::cout << "Emulator of the Nintedo GameBoy" << std::endl;

	//Cpu cpu;

	return 0;
}