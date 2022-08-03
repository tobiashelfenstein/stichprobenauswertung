// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SampleDatabase.h"
#include <iostream>


SampleDatabase::SampleDatabase() : QObject()
{
	// TODO
	if (QSqlDatabase::database("stichprobenauswertung").isOpen())
	{
		QSqlDatabase::removeDatabase("stichprobenauswertung");
	}
	
	QSqlDatabase sample_db = QSqlDatabase::addDatabase("QSQLITE", "stichprobenauswertung");
	sample_db.setDatabaseName(":memory:");

	//QSqlDatabase sample_db = QSqlDatabase::addDatabase("QSQLITE", "stichprobenauswertung");
	//sample_db.setDatabaseName("sample.db");

	if (!sample_db.open())
	{
		// throw exception
	}


	// create tables
	QSqlQuery sample_query(sample_db);

	// t_measuring for measuring case
	if (!sample_query.exec("CREATE TABLE t_measuring (measuring TEXT);"))
	{
		// throw exception
	}

	// t_species
	if (!sample_query.exec("CREATE TABLE t_species (measuring INTEGER, species TEXT);"))
	{
		// throw execption
	}

	// t_trees
	if (!sample_query.exec("CREATE TABLE t_trees (species INTEGER, length REAL, diameter INTEGER);"))
	{
		// throw exception
	}

	return; // TODO return bei  Konstruktor
}

SampleDatabase::~SampleDatabase()
{
	// nothing to do
}


qint64 SampleDatabase::setMeasuringProcess(QString measuring)
{
	// check, if measuring is in database
	// mid is measuring id
	qint64 measuring_id = this->getExistingEntryById("t_measuring", "measuring", measuring);
	if (measuring_id == 0)
	{
		// create or change current measuring
		// TODO Standarddatenbank und Abstraktion von INSERT
		QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));
		query.prepare("INSERT INTO t_measuring (measuring) VALUES (:measuring)");
		query.bindValue(":measuring", measuring);
		query.exec();

		measuring_id = query.lastInsertId().toInt();
	}

	return measuring_id;
}

void SampleDatabase::setMeasuredData(qint64 measuring_id, MeasuredData data)
{
	QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));

	// check, if species is in database
	// sid is species id
	qint64 species_id = this->getExistingSpeciesEntry(measuring_id, data.species);
	if (species_id == 0)
	{
		// species is not in database
		query.prepare("INSERT INTO t_species (measuring, species) VALUES (:measuring, :species)");
		query.bindValue(":measuring", measuring_id);
		query.bindValue(":species", data.species);
		query.exec();

		species_id = query.lastInsertId().toInt();
	}

	query.prepare("INSERT INTO t_trees (species, length, diameter) VALUES (:species, :length, :diameter)");
	query.bindValue(":species", species_id);
	query.bindValue(":length", QString("%1").arg(data.length, 0, 'f', 1)); // TODO better way to insert float value
	query.bindValue(":diameter", data.diameter);
	query.exec();

	return;
}

void SampleDatabase::getMeasuredData(QString measuring, QString species)
{
	QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));

	// check, if species is in database
	// sid is species id
	qint64 measuring_id = this->getExistingEntryById("t_measuring", "measuring", measuring);
	qint64 species_id = this->getExistingSpeciesEntry(measuring_id, species);
	if (species_id > 0)
	{
		query.exec("SELECT diameter, length FROM t_trees WHERE species = " + QString::number(species_id));
		qint64 fld_diameter = query.record().indexOf("diameter");
		qint64 fld_length = query.record().indexOf("length");

		MeasuredData entry;
		while (query.next())
		{
			entry.species = species;
			entry.diameter = query.value(fld_diameter).toInt();
			entry.length = query.value(fld_length).toInt();

			emit hasReadFromDatabase(entry);
		}
	}

	return;
}

qint64 SampleDatabase::getExistingEntryById(QString table, QString column, QString value)
{
	QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));
	query.exec("SELECT rowid FROM " + table + " WHERE " + column + " = '" + value + "'");

	qint64 id = 0;
	if (query.next())
		id = query.value(0).toInt();

	return id;
}

qint64 SampleDatabase::getExistingSpeciesEntry(qint64 measuring_id, QString species)
{
	QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));
	query.exec("SELECT rowid FROM t_species WHERE measuring = " + QString::number(measuring_id) + " AND species = '" + species + "'");

	qint64 id = 0;
	if (query.next())
		id = query.value(0).toInt();

	return id;
}

QStringList SampleDatabase::getExistingEntries(QString table, QString column)
{
	QSqlQuery query(QSqlDatabase::database("stichprobenauswertung"));
	query.exec("SELECT " + column + " FROM " + table);

	QStringList results = {};
	while (query.next())
		results.append(query.value(0).toString());

	return results;
}

QStringList SampleDatabase::getMeasuringByName()
{
	return this->getExistingEntries("t_measuring", "measuring");
}

QStringList SampleDatabase::getSpeciesByName()
{
	return this->getExistingEntries("t_species", "species");
}