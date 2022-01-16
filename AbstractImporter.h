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
	virtual void open(QString port, qint64 rate) = 0;

protected:
	bool with_length_and_diameter = false;

signals:
	void hasMeasured(MeasuredData data);

};

