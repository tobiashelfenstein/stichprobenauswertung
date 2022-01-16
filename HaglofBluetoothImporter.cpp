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

void HaglofBluetoothImporter::read()
{
	QByteArray data = this->bt_port->readAll();
	this->parseHaglofNMEA(&data);

	return;
}

void HaglofBluetoothImporter::parseHaglofNMEA(QByteArray* data)
{
	QList<QByteArray> nmea_fields;

	if (data->left(5).compare("$PHGF") == 0)
	{
		nmea_fields = data->split(',');
		switch (nmea_fields[1].at(0))
		{
		case 'D':
			// parse diameter
			
			// first check, if length is needed instead of diameter
			if (this->waitForLength)
			{
				std::cout << "Fehler: Länge wurde erwartet!" << std::endl;
				break;
			}

			this->diameter = floor(nmea_fields[3].toInt() / 10);

			// set waitForLength to true, if length is needed in next step
			this->waitForLength = this->with_length_and_diameter;

			emit measured;

			break;

		case 'L':
			// parse length

			// first check, if length is needed instead of diameter
			if (!this->with_length_and_diameter && this->waitForDiameter)
			{
				std::cout << "Fehler: Durchmesser wurde erwartet!" << std::endl;
				break;
			}

			this->length = nmea_fields[3].toFloat() / 10;

			// set waitForLength to true, if length is needed in next step
			this->waitForDiameter = this->with_length_and_diameter;

			emit measured;

			break;

		default:
			// kann eventuell weggelassen werden
			break;
		}
	}

	return;
}

void HaglofBluetoothImporter::pushMeasuredData()
{
	if (!this->waitForLength)
	{
		// durchmesser senden
	}
}
