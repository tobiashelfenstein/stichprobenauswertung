// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "AbstractImporter.h"
#include <QFile>
#include <QTextStream>

using namespace std;

class MasserFileImporter : public AbstractImporter
{
	Q_OBJECT

	const static char* species[];

private:
	QString parseSpecies(QString *buffer);
	int parseDiameter(QString* buffer);
	int parseHeight(string* buffer);

public:
	MasserFileImporter();
	~MasserFileImporter();

	void open(const char* filename);
};

