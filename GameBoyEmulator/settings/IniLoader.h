#ifndef DEF_INILOADER
#define DEF_INILOADER

#include <string>

class IniLoader
{
private:
	bool biosAvailable;
	std::string biosPath;

	bool winResolution;
	int width;
	int height;

	bool colorMode;
	int colorModeCode;

public:
	IniLoader();

};

#endif
