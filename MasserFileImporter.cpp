// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "MasserFileImporter.h"

const char* MasserFileImporter::species[] = {
	"Fichte",
	"Tanne",
	"Douglasie",
	"Fichte/Tanne",
	"Fichte/Tanne/Douglasie",
	"Kiefer",
	"Lärche",
	"Kiefer/Lärche",
	"Kiefer/sNb",
	"sNb",
	"Buche",
	"Eiche",
	"Buche/sLb",
	"Eiche/sLb",
	"Esche",
	"Ahorn",
	"Roteiche",
	"Pappel",
	"Hlb",
	"Wlb",
};


MasserFileImporter::MasserFileImporter()
{
	// nothing to do
}

MasserFileImporter::~MasserFileImporter()
{
	// nothing to do
}

bool MasserFileImporter::importTXTFile(char *filename)
{
	ifstream txtFile(filename);
	string buffer;

	string species, diameter;

	MasserData entry;

	while (getline(txtFile, buffer))
	{
		// entry is not empty

		switch (buffer.front())
		{

		// parse data header
		case 'P':
			break;

		// parse only BHD data
		case 'B':
			entry.species = this->parseSpecies(&buffer);
			entry.diameter = this->parseDiameter(&buffer);
			entry.height1 = 0; // always 0

			this->measuredData.push_back(entry);
			break;

		// parse BHD and height data
		case 'H':
			entry.species = this->parseSpecies(&buffer);
			entry.diameter = this->parseDiameter(&buffer);
			entry.height1 = this->parseHeight(&buffer);

			this->measuredData.push_back(entry);
			break;

		default:
			// kann eventuell weggelassen werden
			break;
		}

	}

	txtFile.close();

	return TRUE;
}

string MasserFileImporter::parseSpecies(string *buffer)
{
	string species;
	species = MasserFileImporter::species[stoi(buffer->substr(1, 2)) - 1];

	return species;
}

int MasserFileImporter::parseDiameter(string* buffer)
{
	int diameter;
	diameter = floor(stol(buffer->substr(3, 3)) / 10);

	return diameter;
}

int MasserFileImporter::parseHeight(string* buffer)
{
	int height = 0;
	//height = floor(stol(buffer->substr(3, 3)) / 10);

	return height;
}
