#include "HaglofBluetoothImporter.h"

#include <QtSerialPort/QSerialPort>
#include <iostream>




void HaglofBluetoothImporter::read()
{
	char nmea[1024];
	qint64 line_length = -1;

	QStringList nmea_fields;
	float d;

	QByteArray data = this->bt_port->readAll();
	std::cout << data.toStdString();
	//while (!this->stop)
	//{
	//	//line_length = this->bt_port.read(nmea, sizeof(nmea));
	//	QByteArray data = this->bt_port.readAll();
	//	std::cout << data.toStdString();
	//	if (line_length != -1)
	//	{
	//		nmea_fields = this->parseHaglofNMEA(nmea);
	//		std::cout << nmea_fields[1].toStdString() << std::endl;
	//		if (nmea_fields[1] == "DIA")
	//		{
	//			d = nmea_fields[3].toInt() / 10;
	//			emit diameter(floor(d));
	//		}
	//	}
	//}

	//emit finished(true);

	return;
}

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

	//while (true)
	//{

	//	if (this->bt_port.waitForReadyRead(1000))
	//	{
	//		QByteArray test = this->bt_port.readAll();
	//		/*while (this->bt_port.waitForReadyRead(10))
	//		{
	//			test += this->bt_port.readAll();
	//		}*/

	//		const QString ausgabe = QString::fromUtf8(test);
	//		std::cout << ausgabe.toStdString() << std::endl;
	//	}
	//	else {
	//		std::cout << "Timeout!" << std::endl;
	//	}
	//}

	return;
}

QStringList HaglofBluetoothImporter::parseHaglofNMEA(QString nmea)
{
	if (nmea.left(5) == "$PHGF")
	{
		return nmea.split(',');
	}
	else
	{
		return QStringList{ "", "", "", "" };
	}
}

void HaglofBluetoothImporter::printDiameter(int d)
{
	std::cout << d << std::endl;

	return;
}
