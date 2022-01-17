#pragma once

#include "AbstractImporter.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>

class HaglofBluetoothImporter : public AbstractImporter
{
	Q_OBJECT

public slots:
	void read();
	void pushMeasuredData();

public:
	HaglofBluetoothImporter();
	~HaglofBluetoothImporter();

	void open(QString port, qint64 rate);

private:
	QSerialPort* bt_port;

	qint64 diameter = 0;
	float length = 0.0;

	bool diameter_measured = false;
	bool length_measured = false;

	void parseHaglofNMEA(QByteArray* data);
	void resetMeasuredData();

signals:
	void measured();
};

