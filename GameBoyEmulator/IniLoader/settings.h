#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#define FULL_SCREEN false
#define USE_SAVE_FILE true

/*
* File to look at the .ini file
* 
*/

void createInitFile();

void readInitFile();

/*------------------------------------------SAVESTATE AND SAVEFILE--------------------------------*/

void writeSaveGame();
void loadSaveGame();

void writeSaveState();
void loadSaveState();

#endif

