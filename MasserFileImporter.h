#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

struct MasserData
{
	string species;
	int diameter;
	int height1;
};

class MasserFileImporter
{
	const static char* species[];

private:
	vector<MasserData> measuredData;
	string parseSpecies(string *buffer);
	int parseDiameter(string* buffer);
	int parseHeight(string* buffer);

public:
	MasserFileImporter();
	~MasserFileImporter();

	bool importTXTFile(char *filename);
};

