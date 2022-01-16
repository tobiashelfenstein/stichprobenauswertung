#pragma once

#include "HEPAutomator.h"
#include "AbstractImporter.h"
#include <QObject>

//struct MeasuredData
//{
//	std::wstring species;
//	long diameter;
//	long height1;
//};

enum MANUFACTURERS
{
	MASSER,
	HAGLOF
};


class SampleModel : public QObject
{
	Q_OBJECT

public:
	SampleModel();
	~SampleModel();

	void initializeImporter(MANUFACTURERS m); // for files
	void initializeImporter(MANUFACTURERS m, QString port, qint64 rate); // for bluetooth

private:
	HEPAutomator* automator;
	MANUFACTURERS manufacturer;
	AbstractImporter* importer = nullptr;

public slots:
	void sendToHEP(MeasuredData data);
};

