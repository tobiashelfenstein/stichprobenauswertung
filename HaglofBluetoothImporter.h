// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

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
	~HaglofBluetoothImporter() {};

	void open(QString port, qint64 rate);
	void close();

private:
	QSerialPort* m_pBT_port;

	qint64 m_diameter = 0;
	float m_length = 0.0;

	bool m_diameter_measured = false;
	bool m_length_measured = false;

	void parseHaglofNMEA(QByteArray* data);
	void resetMeasuredData();

signals:
	void measured();
};

