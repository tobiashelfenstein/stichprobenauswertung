// Copyright (C) 2023 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SampleModel.h"
#include "HaglofFileImporter.h"
#include "HaglofBluetoothImporter.h"
#include "MasserFileImporter.h"

#include <QApplication>
#include <QSettings>
#include <stdexcept>


SampleModel::SampleModel() : QObject()
{
	// read application settings
	m_settingsFile = QApplication::applicationDirPath() + "/" + "settings.ini";
	loadSettings();

	// class settings
	m_automator = new HEPAutomator();
}

void SampleModel::loadSettings()
{
	QSettings settings(m_settingsFile, QSettings::IniFormat);
	m_port_name = settings.value("Bluetooth/ComPort", "").toString();
	m_baud_rate = settings.value("Bluetooth/BaudRate", "").toInt();

	m_max_diameter = settings.value("Automator/MaxDiameter", "").toInt();
}

void SampleModel::initializeImporter(qint64 manufacturer, const char* filename)
{
	// reset clear field indicator
	m_repeat = true;

	// initialize sqlite3 database in memory
	initializeDatabase();

	switch (manufacturer)
	{
	case MASSER:
		// manufacture is masser
		importer = new MasserFileImporter();
		break;

	case HAGLOF:
		// manufacturer is haglöf
		importer = new HaglofFileImporter();
		break;
	}

	connect(importer, &AbstractImporter::changeMeasuring, this, &SampleModel::setMeasuring);
	connect(importer, &AbstractImporter::hasMeasured, this, &SampleModel::saveToDatabase);

	importer->open(filename);
}

void SampleModel::initializeDatabase()
{
	sample_db = new SampleDatabase();
}

void SampleModel::initializeImporter(qint64 manufacturer, bool with_length_and_diameter)
{
	// reset clear field indicator
	m_repeat = true;

	this->with_length_and_diameter = with_length_and_diameter;

	switch (manufacturer)
	{
	case MASSER:
		// manufacture is masser

		break;

	case HAGLOF:
		// manufacturer is haglöf
		// open connection to serial port
		importer = new HaglofBluetoothImporter();
		importer->setLengthMeasurement(this->with_length_and_diameter);
		importer->open("\\\\.\\" + m_port_name, m_baud_rate);

		// connect to importer events
		connect(importer, &AbstractImporter::hasMeasured, this, &SampleModel::sendToHEP);

		break;
	}
}

void SampleModel::sendToHEP(MeasuredData data)
{
	// connect to HEP
	m_automator->connectToHEP();

	// do things the first time and repeat them
	if (m_repeat)
	{
		// clear input field
		m_automator->clearInputField(3);
		m_repeat = importer->getLiveState();
	}

	if (data.diameter >= m_max_diameter)
	{
		QString send_string = prepareSendString(data);
		if (m_automator->sendMeasuredValues(send_string.toStdString())) // TODO is if necessary?
		{
			emit hasSuccessfulSendToHep(data);
		}
	}

	return;
}

QString SampleModel::prepareSendString(MeasuredData data)
{
	QString send_string = "";

	if (this->with_length_and_diameter)
	{
		// format 18.026; length and diameter
		// führende 'Null' ist nicht notwendig; #4
		send_string = QString("%1%2").arg(data.length, 0, 'f', 1).arg(data.diameter);
	}

	else
	{
		//format 26; diameter only
		send_string = QString("%1").arg(data.diameter);
	}

	return send_string;
}

void SampleModel::setMeasuring(QString measuring)
{
	measuring_id = sample_db->setMeasuringProcess(measuring);
}

void SampleModel::saveToDatabase(MeasuredData data)
{
	sample_db->setMeasuredData(this->measuring_id, data);
}

void SampleModel::readFromDatabase(QString measuring, QString species)
{
	connect(sample_db, &SampleDatabase::hasReadFromDatabase, this, &SampleModel::sendToHEP);

	sample_db->getMeasuredData(measuring, species);
}

void SampleModel::closeImporter()
{
	importer->close();
	
	delete importer;
	importer = nullptr;

	// what is with the database?!
}
