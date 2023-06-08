// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "AbstractImporter.h"
#include "HaglofBluetoothImporter.h"

#include <QtSerialPort/QSerialPort>
#include <QtCore/QList>
#include <iostream>

#include <qDebug>




HaglofBluetoothImporter::HaglofBluetoothImporter() : AbstractImporter()
{
	// this is a live importer
	m_liveModus = true;

	// create serial port connection for bluetooth
	m_pBT_port = new QSerialPort(this);
	connect(m_pBT_port, &QSerialPort::readyRead, this, &HaglofBluetoothImporter::read);
	connect(this, &HaglofBluetoothImporter::measured, this, &HaglofBluetoothImporter::pushMeasuredData);
}

void HaglofBluetoothImporter::open(QString com_port, qint64 baud_rate)
{
	// set up bluetooth serial port
	m_pBT_port->setPortName(com_port);
	m_pBT_port->setBaudRate(baud_rate);

	// open connection
	m_pBT_port->open(QIODevice::ReadOnly);
}

void HaglofBluetoothImporter::close()
{

}

void HaglofBluetoothImporter::read()
{
	QByteArray data = m_pBT_port->readAll();
	parseHaglofNMEA(&data);
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
				if (this->m_diameter_measured)
				{
					std::cout << "Fehler: Länge wurde erwartet!" << std::endl;
					break;
				}

				m_diameter = floor(nmea_fields[3].toInt() / 10);
				m_diameter_measured = true;

				emit measured();

				break;

			case 'L':
				// parse length
				if (!with_length_and_diameter || m_length_measured)
				{
					std::cout << "Fehler: Durchmesser wurde erwartet!" << std::endl;
					break;
				}

				m_length = nmea_fields[3].toFloat() / 10;
				m_length_measured = true;

				emit measured();

				break;
			}
		}
		
	}
}

void HaglofBluetoothImporter::pushMeasuredData()
{
	if (!m_diameter_measured || m_length_measured != with_length_and_diameter)
	{
		std::cout << "Kein Wert zu senden" << std::endl;
		return;
	}

	MeasuredData data = { "", m_diameter, m_length };
	emit hasMeasured(data);

	resetMeasuredData();
}

void HaglofBluetoothImporter::resetMeasuredData()
{
	// reset measured diameter
	m_diameter = 0;
	m_diameter_measured = false;

	// reset measured length
	m_length = 0;
	m_length_measured = 0.0;
}
