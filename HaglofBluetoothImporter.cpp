#include "HaglofBluetoothImporter.h"

#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <iostream>




HaglofBluetoothImporter::HaglofBluetoothImporter() : QObject()
{
	this->bt_port = new QSerialPort(this);
	connect(this->bt_port, &QSerialPort::readyRead, this, &HaglofBluetoothImporter::read);
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
	QString nmea = "";
	qint64 line_length = -1;

	QStringList nmea_fields;
	float d;

	QByteArray data = this->bt_port->readAll();
	this->parseHaglofNMEA(&data);

	return;
}

void HaglofBluetoothImporter::parseHaglofNMEA(QByteArray* data)
{
	QList<QByteArray> nmea_fields;
	float value = 0;

	if (data->left(5).compare("$PHGF") == 0)
	{
		nmea_fields = data->split(',');
		switch (nmea_fields[1].at(0))
		{
		case 'D':
			// parse diameter
			value = nmea_fields[3].toInt() / 10;
			emit diameter(floor(value));

			break;

		case 'L':
			// parse length
			break;

		default:
			// kann eventuell weggelassen werden
			break;
		}
	}

	return;
}
