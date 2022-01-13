#pragma once

#include <QObject>
#include <QtSerialPort/QSerialPort>

struct HaglofData
{
	std::wstring species;
	long diameter;
	long height1;
};


class HaglofBluetoothImporter : public QObject
{
	Q_OBJECT

public slots:
	void printDiameter(int d);
	void read();

public:
	HaglofBluetoothImporter();
	~HaglofBluetoothImporter();

	void open(QString port, qint64 rate);

private:
	std::vector<HaglofData> measuredData;
	QSerialPort* bt_port;

	QStringList parseHaglofNMEA(QString nmea);

signals:
	void finished(bool f);
	void diameter(int d);
};

