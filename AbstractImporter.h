// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <QObject>

struct MeasuredData
{
	QString species;
	qint64 diameter;
	float length;
};

class AbstractImporter : public QObject
{
	Q_OBJECT

public:
	AbstractImporter() {}
	~AbstractImporter() {}
	virtual void open(const char* filename) {};
	virtual void open(QString port, qint64 rate) {};
	virtual void close() {};
	void setLengthMeasurement(bool with_length_and_diameter);
	bool getLiveState();

protected:
	bool with_length_and_diameter = false;
	bool m_liveModus = false; // for bluetooth live connection

signals:
	void changeMeasuring(QString measuring);
	void hasMeasured(MeasuredData data);

};

