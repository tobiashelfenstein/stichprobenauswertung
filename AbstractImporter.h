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
	virtual ~AbstractImporter() {}
	virtual void open(const char* filename) {};
	virtual void open(QString port, qint64 rate) {};
	void setLengthMeasurement(bool with_length_and_diameter);

protected:
	bool with_length_and_diameter = false;

signals:
	void changeMeasuring(QString measuring);
	void hasMeasured(MeasuredData data);

};

