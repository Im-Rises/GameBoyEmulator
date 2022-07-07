#include "IniLoader.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

IniLoader::IniLoader(const std::string& iniFileNamePath)
{
	this->iniFileNamePath = iniFileNamePath;
	struct stat buffer;
	if (stat(iniFileNamePath.c_str(), &buffer) == 0)
		readingIniFile();
	else
		createIniFile();
}

void IniLoader::createIniFile()
{
	cout << "No ini file, creating it" << endl;

	ofstream myfile;
	myfile.open(iniFileNamePath, ios::out);
	myfile << "startBios='" << biosAvailable << "'" << endl;
	myfile << "biosPath='" << biosPath << "'" << endl;
	myfile << "width='" << width << "'" << endl;
	myfile << "height='" << height << "'" << endl;
	myfile << "colorMode='" << colorModeCode << "'" << endl;
	myfile.close();
}

void IniLoader::readingIniFile()
{
	cout << "Reading ini file" << endl;

	ofstream myfile;
	myfile.open(iniFileNamePath, ios::in);

	for (getline(myfile))

	myfile.close();

}

std::string IniLoader::getStringSuroundedBy(std::string text, const char& character) const
{
	return text.substr(text.find_first_of(character), text.find_last_of(character));
}

