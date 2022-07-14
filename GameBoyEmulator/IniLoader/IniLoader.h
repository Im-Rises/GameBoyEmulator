#ifndef DEF_INILOADER
#define DEF_INILOADER

#include <string>

class GameBoy;

class IniLoader
{
private:
	std::string iniFileNamePath;

	bool biosAvailable = false;
	std::string biosPath = "./dmg_boot.bin";

	int width = 640;
	int height = 576;

	int colorModeCode = 0;

public:
	IniLoader(const std::string& iniFileNamePath = "Emulator.ini");
	void createIniFile();
	void readingIniFile();
	void printSettings();

	bool getBiosAvailable() const;

	void setGameBoyParams(GameBoy* gameBoy);

private:
	std::string getStringHeaderLine(std::string text, const char& endCharacter) const;
	std::string getStringSuroundedBy(std::string text, std::string delimiter) const;
};

#endif
