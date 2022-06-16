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

void MasserFileImporter::open(const char* filename)
{
	QFile txtfile(filename);
	txtfile.open(QFile::ReadOnly);

	//ifstream txtFile(filename);

	string species, diameter;

	MeasuredData entry;

	QTextStream stream(&txtfile);
	while (!stream.atEnd())
	{
		QString buffer = stream.readLine();

		// entry is not empty

		switch (buffer.front().toLatin1())
		{

		// parse data header
		case 'P':
			// create current measuring
			// MASSER with 4 digit long measuring identifier
			this->changeMeasuring(buffer.mid(5, 4));
			break;

		// parse only BHD data
		case 'B':
			entry.species = this->parseSpecies(&buffer);
			entry.diameter = this->parseDiameter(&buffer);
			entry.length = 0; // always 0

			this->hasMeasured(entry);
			break;

		// parse BHD and height data
		// not useful
		case 'H':
			//entry.species = this->parseSpecies(&buffer);
			//entry.diameter = this->parseDiameter(&buffer);
			//entry.height1 = this->parseHeight(&buffer);

			//this->measuredData.push_back(entry);
			break;

		default:
			// kann eventuell weggelassen werden
			break;
		}

	}

	txtfile.close();

	return;
}

QString MasserFileImporter::parseSpecies(QString *buffer)
{
	QString species;
	species = MasserFileImporter::species[buffer->mid(1, 2).toInt() - 1];

	return species;
}

int MasserFileImporter::parseDiameter(QString* buffer)
{
	int diameter;
	diameter = floor(buffer->mid(3, 3).toInt() / 10);

	return diameter;
}

int MasserFileImporter::parseHeight(string* buffer)
{
	int height = 0;
	//height = floor(stol(buffer->substr(3, 3)) / 10);

	return height;
}
