#include "debug.h"

bool readInitFile()
{
	return 0;
}

/*-----------------------------------------DEBUG----------------------------------------------*/

//bool debug = false;
//
//void writeScreenToFile()
//{
//	string const nomFichier("screenDebug.txt");
//	ofstream monFlux(nomFichier.c_str());
//
//	if (monFlux)
//	{
//		for (int i = 0; i < 144; i++)
//		{
//			for (int j = 0; j < 160; j++)
//			{
//				monFlux << (int)ppu.getLcdScreenPixel(j, i) << " ";
//			}
//			monFlux << endl;
//		}
//		cout << "Debug file created" << endl;
//	}
//	else
//	{
//		cout << "Error debug file not created." << endl;
//	}
//}
//
//void writeAllTiles()
//{
//	string const nomFichier("tilesDebug.txt");
//	ofstream monFlux(nomFichier.c_str());
//
//	if (monFlux)
//	{
//		for (int i = 0; i < 0x2000; i++)
//		{
//			uint8 line1 = memory.read(i + 0x8000);
//			uint8 line2 = memory.read(i + 1 + 0x8000);
//			i++;
//
//			for (int j = 0; j < 16; j++)
//			{
//				uint8 bitLine1 = getBit(line1, j);
//				uint8 bitLine2 = getBit(line2, j);
//				monFlux << (bitLine1 + (bitLine2 << 1));
//			}
//
//			monFlux << endl;
//			if (!(((i + 1) % 16) > 0))
//				monFlux << endl;
//		}
//		cout << "Debug file created" << endl;
//	}
//	else
//	{
//		cout << "Error debug file not created." << endl;
//	}
//}