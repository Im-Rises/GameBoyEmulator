#ifndef DEF_LCD
#define DEF_LCD 

#include "Memory.h"

class Ppu
{
private:
	Memory* memory=nullptr;

public:
	Ppu(Memory* memory);

	void drawBackground();
	void drawSrpite();
	void drawWindows();

};

#endif