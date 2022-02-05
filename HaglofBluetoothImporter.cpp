// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "AbstractImporter.h"
#include "HaglofBluetoothImporter.h"

#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <iostream>




HaglofBluetoothImporter::HaglofBluetoothImporter() : AbstractImporter()
{
	this->bt_port = new QSerialPort(this);
	connect(this->bt_port, &QSerialPort::readyRead, this, &HaglofBluetoothImporter::read);
	connect(this, &HaglofBluetoothImporter::measured, this, &HaglofBluetoothImporter::pushMeasuredData);
}

HaglofBluetoothImporter::~HaglofBluetoothImporter()
{
	// nothing to do
}

void HaglofBluetoothImporter::open(QString com_port, qint64 baud_rate)
{
	// set up bluetooth serial port
	this->bt_port->setPortName(com_port);
	this->bt_port->setBaudRate(baud_rate);

	// open connection
	this->bt_port->open(QIODevice::ReadOnly);

	return;
}

void HaglofBluetoothImporter::close()
{

}

void HaglofBluetoothImporter::read()
{
	QByteArray data = this->bt_port->readAll();
	//QByteArray data = this->bt_port->readLine();
	this->parseHaglofNMEA(&data);

	return;
}

void HaglofBluetoothImporter::parseHaglofNMEA(QByteArray* data)
{
	QList<QByteArray> phgf_split;
	QList<QByteArray> nmea_fields;

	if (data->left(5).compare("$PHGF") == 0) // data from HAGLÖF; at least one entry
	{
		phgf_split = data->split('\r\n');

		for (int i = 0; i < phgf_split.size() - 1; i++) // last line is always empty because of splitting
		{
			nmea_fields = phgf_split[i].trimmed().split(',');
			switch (nmea_fields[1].at(0))
			{
			case 'D':
				// parse diameter
				if (this->diameter_measured)
				{
					std::cout << "Fehler: Länge wurde erwartet!" << std::endl;
					break;
				}

				this->diameter = floor(nmea_fields[3].toInt() / 10);
				this->diameter_measured = true;

				emit measured();

				break;

			case 'L':
				// parse length
				if (!this->with_length_and_diameter || this->length_measured)
				{
					std::cout << "Fehler: Durchmesser wurde erwartet!" << std::endl;
					break;
				}

				this->length = nmea_fields[3].toFloat() / 10;
				this->length_measured = true;

				emit measured();

				break;
			}
		}
		
	}

	return;
}

void HaglofBluetoothImporter::pushMeasuredData()
{
	if (!this->diameter_measured || this->length_measured != this->with_length_and_diameter)
	{
		std::cout << "Kein Wert zu senden" << std::endl;
		return;
	}

	MeasuredData data = { "", this->diameter, this->length };
	emit hasMeasured(data);

	this->resetMeasuredData();

	return;
}

void HaglofBluetoothImporter::resetMeasuredData()
{
	// reset measured diameter
	this->diameter = 0;
	this->diameter_measured = false;

	// reset measured length
	this->length = 0;
	this->length_measured = 0.0;

	return;
}
