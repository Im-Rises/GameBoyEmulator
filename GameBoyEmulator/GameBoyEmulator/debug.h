#ifndef DEBUG
#define DEBUG


#include <fstream>

#include <iostream>

#include "binaryLib.h"

using namespace std;

bool readInitFile();

static bool debug;
void writeScreenToFile();
void writeAllTiles();

#endif