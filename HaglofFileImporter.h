// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include "AbstractImporter.h"

#include <Windows.h>
#include <iostream>
#include <vector>

#include <QtCore/QXmlStreamReader>
#include <QFile>


class HaglofFileImporter : public AbstractImporter
{
	Q_OBJECT

private:
	QFile* m_xmlfile = nullptr;
	QXmlStreamReader xml;
	std::vector<MeasuredData> measuredData;

	bool readAll();
	void readTree();
	void readHaglofData();
	void readHgData();

public:
	HaglofFileImporter() {};
	~HaglofFileImporter() {};

	void open(const char *filename);
	void close();
};

