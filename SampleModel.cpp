// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SampleModel.h"
#include "HaglofFileImporter.h"
#include "HaglofBluetoothImporter.h"
#include "MasserFileImporter.h"


SampleModel::SampleModel() : QObject()
{
	this->automator = new HEPAutomator();
}

SampleModel::~SampleModel()
{
	// nothing to do
}

void SampleModel::initializeImporter(MANUFACTURERS m)
{
	this->manufacturer = m;

	this->initializeDatabase();

	switch (this->manufacturer)
	{
	case MASSER:
		// manufacture is masser
		this->importer = new MasserFileImporter();
		break;

	case HAGLOF:
		// manufacturer is haglöf
		this->importer = new HaglofFileImporter();
		break;
	}

	connect(this->importer, &AbstractImporter::changeMeasuring, this, &SampleModel::setMeasuring);
	connect(this->importer, &AbstractImporter::hasMeasured, this, &SampleModel::saveToDatabase);

	this->importer->open("Z:\\source\\repos\\Stichprobenauswertung_Qt\\Stichprobenauswertung\\examples\\kluppfall.txt");

	return;
}

bool SampleModel::initializeDatabase()
{
	this->sample_db = new SampleDatabase();

	return true;
}

void SampleModel::initializeImporter(MANUFACTURERS m, QString port, qint64 rate, bool with_length_and_diameter)
{
	this->manufacturer = m;
	this->with_length_and_diameter = with_length_and_diameter;

	switch (this->manufacturer)
	{
	case MASSER:
		// manufacture is masser

		break;

	case HAGLOF:
		// manufacturer is haglöf
		// open connection to serial port
		this->importer = new HaglofBluetoothImporter();
		this->importer->setLengthMeasurement(this->with_length_and_diameter);
		this->importer->open(port, rate);

		// connect to importer events
		connect(this->importer, &AbstractImporter::hasMeasured, this, &SampleModel::sendToHEP);

		break;
	}
}

void SampleModel::sendToHEP(MeasuredData data)
{
	// for testing only
	// better function needed
	if (!this->automator->connectToHEP()) {
		std::cout << "Fehler: HEP wurde nicht geöffnet!" << std::endl;
	}

	QString send_string = this->prepareSendString(data);
	if (this->automator->sendMeasuredValues(send_string.toStdString()))
	{
		emit hasSuccessfulSendToHep(data);
	}

	return;
}

QString SampleModel::prepareSendString(MeasuredData data)
{
	QString send_string = "";

	if (this->with_length_and_diameter)
	{
		// format 18.026; length and diameter
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
	this->measuring_id = this->sample_db->setMeasuringProcess(measuring);

	return;
}

QStringList SampleModel::getMeasuring()
{
	QStringList test = this->sample_db->getSpeciesByName();
	for (int i = 0; i < test.size(); i++)
		std::cout << test.at(i).toLocal8Bit().constData() << std::endl;

	return QStringList();
}

void SampleModel::saveToDatabase(MeasuredData data)
{
	this->sample_db->setMeasuredData(this->measuring_id, data);

	return;
}

