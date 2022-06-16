// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include "AbstractImporter.h"
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVariant>


class SampleDatabase : public QObject
{
	Q_OBJECT

public:
	SampleDatabase();
	~SampleDatabase();

	qint64 setMeasuringProcess(QString measuring);
	void setMeasuredData(qint64 measuring_id, MeasuredData data);

	QStringList getMeasuringByName();
	QStringList getSpeciesByName();

	


private:
	qint64 getExistingEntryById(QString table, QString column, QString value);
	QStringList getExistingEntries(QString table, QString column);

};

