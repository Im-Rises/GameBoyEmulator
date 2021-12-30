#ifndef DEF_SETTINGS
#define DEF_SETTINGS

#define FULL_SCREEN false
#define USE_SAVE_FILE true


void readInitFile();

/*------------------------------------------SAVESTATE AND SAVEFILE--------------------------------*/

void writeSaveGame();
void loadSaveGame();

void writeSaveState();
void loadSaveState();

#endif

