// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "HaglofFileImporter.h"


void HaglofFileImporter::open(const char *filename)
{
	m_xmlfile = new QFile(filename);
	m_xmlfile->open(QFile::ReadOnly);

	this->xml.setDevice(m_xmlfile);
	this->readAll();

	// close the file after reading
	m_xmlfile->close();
}

void HaglofFileImporter::close()
{
	// check if file is open before close it
	if (m_xmlfile->isOpen())
	{
		m_xmlfile->close();
	}
}

bool HaglofFileImporter::readAll()
{
	MeasuredData entry;

	if (this->xml.readNextStartElement())
	{
		if (QString("mdiidata").compare(this->xml.name(), Qt::CaseInsensitive) == 0)
		{
			this->readHaglofData();
		}
		else
		{
			this->xml.raiseError("Keine Kluppendatei von HAGLÖF!");
		}
	}

	return true;
}

void HaglofFileImporter::readHaglofData()
{
	while (this->xml.readNextStartElement())
	{
		if (QString("data").compare(this->xml.name(), Qt::CaseInsensitive) == 0)
		{
			// create current measuring
			// HAGLOF always "0"
			this->changeMeasuring("haglof");

			// now begin reading tree entries
			this->readHgData();
		}
		else
			this->xml.skipCurrentElement();
	}
}

void HaglofFileImporter::readHgData()
{
	while (this->xml.readNextStartElement())
	{
		if (this->xml.name() == QString("Tree"))
			this->readTree();
		else
			this->xml.skipCurrentElement();
	}
}

void HaglofFileImporter::readTree()
{
	QString result;
	MeasuredData entry;

	while (this->xml.readNextStartElement())
	{
		result = "";

		if (this->xml.name() == QString("SpeciesText"))
		{
			result = this->xml.readElementText();
			entry.species = result.trimmed();
		}
		else if (this->xml.name() == QString("Diameter"))
		{
			result = this->xml.readElementText();
			entry.diameter = floor(result.trimmed().toInt()/ 10);
		}
		else if (this->xml.name() == QString("Height1"))
		{
			result = this->xml.readElementText();
			entry.length = result.trimmed().toFloat() / 10;
		}
		else
		{
			this->xml.skipCurrentElement();
		}

	}

	this->hasMeasured(entry);
}
