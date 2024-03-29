﻿// Copyright (C) 2023 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include "HEPAutomator.h"
#include "AbstractImporter.h"
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QVariant>
#include "SampleDatabase.h"
#include <QStringList>


enum MANUFACTURERS
{
	MASSER,
	HAGLOF
};


class SampleModel : public QObject
{
	Q_OBJECT

signals:
	void hasSuccessfulSendToHep(MeasuredData data);

public:
	SampleModel();
	~SampleModel() {};

	void initializeImporter(qint64 manufacturer, const char* filename); // for files
	void initializeImporter(qint64 manufacturer, bool with_length_and_diameter = false); // for bluetooth
	void readFromDatabase(QString measuring, QString species);

	void closeImporter();

private:
	HEPAutomator* m_automator;
	AbstractImporter* importer = nullptr;
	bool with_length_and_diameter = false;

	qint64 measuring_id = 0; // current measuring id

	SampleDatabase* sample_db = nullptr;

	QString prepareSendString(MeasuredData data);
	void saveToDatabase(MeasuredData data);
	void setMeasuring(QString measuring);
	void initializeDatabase();

	QString m_settingsFile = "";
	QString m_port_name = "";
	qint64 m_baud_rate = 0;
	qint64 m_max_diameter = 0;

	void loadSettings();

	bool m_repeat = true;

public slots:
	void sendToHEP(MeasuredData data);
};

