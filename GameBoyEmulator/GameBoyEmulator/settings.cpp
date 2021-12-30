#include "settings.h"

void readInitFile()
{

}


/*------------------------------------------SAVESTATE AND SAVEFILE--------------------------------*/

//void GameBoy::writeSaveGame()
//{
//	string fileLocation = "test.gb";
//	fileLocation = fileLocation.substr(0, fileLocation.find('.')) + ".sav";
//	ofstream monFlux(fileLocation.c_str());
//
//	if (monFlux)
//	{
//		for (int i = 0; i < 0x2000; i++)
//		{
//			monFlux << memory.read(ETERNAL_EXPANSION_WORKING_RAM + i) << endl;
//		}
//		cout << "Save file created" << endl;
//	}
//	else
//	{
//		cout << "Error save file not created." << endl;
//	}
//}
//
//void GameBoy::loadSaveGame()
//{
//	string fileLocation = "test.gb";
//	fileLocation = fileLocation.substr(0, fileLocation.find('.')) + ".sav";
//	ifstream monFlux(fileLocation.c_str());
//
//	if (monFlux)
//	{
//		uint8 line;
//		for (int i = 0; i < 0x2000; i++)
//		{
//			monFlux >> line;
//			//memory.write(ETERNAL_EXPANSION_WORKING_RAM + i, );
//		}
//		cout << "Save file loaded" << endl;
//	}
//	else
//	{
//		cout << "Error save file not loaded" << endl;
//	}
//}
//
//void GameBoy::writeSaveState()
//{
//	//cpu.dump();
//	//memory.dump;
//	//Write data to file
//}
//
//void GameBoy::loadSaveState()
//{
//	//Read savestate
//	//Set every data
//}
