// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SampleModel.h"
#include "HaglofFileImporter.h"
#include "HaglofBluetoothImporter.h"

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

	switch (this->manufacturer)
	{
	case MASSER:
		// manufacture is masser

		break;

	case HAGLOF:
		// manufacturer is haglöf
		this->initializeDatabase();

		break;
	}

	return;
}

bool SampleModel::initializeDatabase()
{
	//QSqlDatabase sample_db = QSqlDatabase::addDatabase("QSQLITE", "stichprobenauswertung_db");
	//sample_db.setDatabaseName(":memory:");

	QSqlDatabase sample_db = QSqlDatabase::addDatabase("QSQLITE", "stichprobenauswertung_db");
	sample_db.setDatabaseName("sample.db");

	if (!sample_db.open())
	{
		// throw exception
	}

	QSqlQuery sample_query(sample_db);

	// create tables
	// t_measuring for Kluppfall
	if (!sample_query.exec("CREATE TABLE t_measuring (id INTEGER PRIMARY KEY, measuring INTEGER);"))
	{
		// throw exception
	}

	// t_species
	if (!sample_query.exec("CREATE TABLE t_species (id INTEGER PRIMARY KEY, meausring INTEGER, species TEXT);"))
	{
		// throw execption
	}

	// t_trees
	if (!sample_query.exec("CREATE TABLE t_trees (id INTEGER PRIMARY KEY, species INTEGER, length INTEGER, diameter INTEGER)"))
	{
		// throw exception
	}

	
	this->importer = new HaglofFileImporter();
	connect(this->importer, &AbstractImporter::hasMeasured, this, &SampleModel::saveToDatabase);
	this->importer->open("Z:\\source\\repos\\Stichprobenauswertung_Qt\\Stichprobenauswertung\\examples\\kluppfall.xml");

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

void SampleModel::saveToDatabase(MeasuredData data)
{
	QSqlQuery data_query(QSqlDatabase::database("stichprobenauswertung_db"));
	QString query("INSERT INTO t_trees (id, species, length, diameter) VALUES (0, 0 ," + QString::number(data.length) + "," + QString::number(data.diameter) + ")");
	std::cout << query.toStdString() << std::endl;
	//data_query.prepare("INSERT INTO t_trees (id, species, length, diameter) VALUES (0, " + data.species + "," + data.length + "," + data.diameter + ")");
	data_query.prepare(query);
	data_query.exec();

	return;
}