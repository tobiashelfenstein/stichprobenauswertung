#pragma once

#include "AbstractImporter.h"
#include <QObject>
#include <QtSerialPort/QSerialPort>

class HaglofBluetoothImporter : public AbstractImporter
{
	Q_OBJECT

public slots:
	void read();

public:
	HaglofBluetoothImporter();
	~HaglofBluetoothImporter();

	void open(QString port, qint64 rate);

private:
	QSerialPort* bt_port;

	qint64 diameter = 0;
	float length = 0.0;

	bool waitForDiameter = true;
	bool waitForLength = false;

	void parseHaglofNMEA(QByteArray* data);
	void pushMeasuredData();

signals:
	void measured();
};

