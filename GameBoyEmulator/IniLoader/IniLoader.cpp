#include "IniLoader.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../GameBoy.h"

using namespace std;

IniLoader::IniLoader(const std::string& iniFileNamePath)
{
	this->iniFileNamePath = iniFileNamePath;
	struct stat buffer;
	if (stat(iniFileNamePath.c_str(), &buffer) == 0)
		readingIniFile();
	else
		createIniFile();

	printSettings();
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

	ifstream myfile;
	myfile.open(iniFileNamePath, ios::in);
	string line;

	while (getline(myfile, line))
	{
		string label, value;
		try
		{
			label = getStringHeaderLine(line, '=');
			value = getStringSuroundedBy(line, "'");

			if (label == "startBios")
			{
				biosAvailable = stoi(value);
			}

			if (label == "biosPath")
				biosPath = value;

			if (label == "width")
				width = stoi(value);

			if (label == "height")
				height = stoi(value);

			if (label == "colorMode")
				colorModeCode = stoi(value);
		}
		catch (exception e)
		{
			cerr << "Error settings: " << label << " with value: " << value << " is not set correctly" << endl;
		}
	}

	myfile.close();
}

void IniLoader::printSettings()
{
	cout << "Settings from .ini file" << endl
		<< "biosAvailable=" << biosAvailable << endl
		<< "biosPath=" << biosPath << endl
		<< "width=" << width << endl
		<< "height=" << height << endl
		<< "colorCode=" << colorModeCode << endl;
}

bool IniLoader::getBiosAvailable() const
{
	return biosAvailable;
}

void IniLoader::setGameBoyParams(GameBoy* gameBoy)
{
	if (biosAvailable)
		gameBoy->loadBios(biosPath);

	gameBoy->setWidthHeight(width, height);

	gameBoy->setColorMode(colorModeCode);
}


std::string IniLoader::getStringHeaderLine(std::string text, const char& endCharacter) const
{
	return text.substr(0, text.find_last_of(endCharacter));
}


std::string IniLoader::getStringSuroundedBy(std::string text, string delimiter) const
{
	int first = text.find(delimiter);
	int last = text.find_last_of(delimiter);
	return text.substr(first+1, last - first-1);
}
