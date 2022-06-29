// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SourceSelector.h"

#include <iostream>
#include <QMessagebox>
#include <QtWidgets/QComboBox>
#include <QMessagebox>

#include <QSqlQueryModel>
#include <QSqlDatabase>


SourceSelector::SourceSelector() : QDialog()
{
	this->setupUi();

	this->initializeFields();
}

SourceSelector::~SourceSelector()
{
	// nothing to do
}

void SourceSelector::setupUi()
{
	this->setWindowTitle("Datenquelle auswählen");

	QVBoxLayout* layout = new QVBoxLayout();
	this->setLayout(layout);

	// measuring process selection
	QLabel* measuring_lbl = new QLabel("Kluppfall:");
	this->measuring_cbx = new QComboBox();
	this->measuring_cbx->setMinimumHeight(60);
	this->measuring_cbx->setMinimumWidth(200);
	// add items from database

	connect(this->measuring_cbx, &QComboBox::currentTextChanged, this, &SourceSelector::measuringUpdated);

	layout->addWidget(measuring_lbl);
	layout->addWidget(this->measuring_cbx);
	layout->addSpacing(20);

	// species selection
	QLabel* species_lbl = new QLabel("Baumart:");
	this->species_cbx = new QComboBox();
	this->species_cbx->setMinimumHeight(60);
	this->species_cbx->setMinimumWidth(200);
	//this->file_lvw->setModel(this->model);

	layout->addWidget(species_lbl);
	layout->addWidget(this->species_cbx);
	layout->addSpacing(20);

	// buttons
	QHBoxLayout* layout_buttons = new QHBoxLayout();
	layout->addLayout(layout_buttons);

	// abort import button
	QIcon icn_abort(":/icons/application-back.svg");
	QPushButton* btn_abort_import = new QPushButton(icn_abort, "");
	btn_abort_import->setMinimumHeight(60);
	btn_abort_import->setIconSize(QSize(40, 40));

	connect(btn_abort_import, &QPushButton::clicked, this, &QDialog::reject);

	layout_buttons->addWidget(btn_abort_import);

	// start import button
	QIcon icn_start(":/icons/application-next.svg");
	QPushButton* btn_start_import = new QPushButton(icn_start, "");
	btn_start_import->setMinimumHeight(60);
	btn_start_import->setIconSize(QSize(40, 40));
	btn_start_import->setDefault(true);

	connect(btn_start_import, &QPushButton::clicked, this, &QDialog::accept);

	layout_buttons->addWidget(btn_start_import);

	return;
}

void SourceSelector::initializeFields()
{
	this->updateMeasuringComboBox();
	this->updateSpeciesComboBox();
	
	return;
}

void SourceSelector::updateMeasuringComboBox()
{
	// measuring process combobox
	QSqlQueryModel* m_measuring = new QSqlQueryModel();
	m_measuring->setQuery("SELECT measuring FROM t_measuring", QSqlDatabase::database("stichprobenauswertung"));
	this->measuring_cbx->setModel(m_measuring);

	return;
}

void SourceSelector::updateSpeciesComboBox()
{
	QString str_measuring = this->measuring_cbx->currentText();
	QSqlQueryModel m_measuring;

	m_measuring.setQuery("SELECT rowid FROM t_measuring WHERE measuring = '" + str_measuring + "'", QSqlDatabase::database("stichprobenauswertung"));
	qint64 int_measuring = m_measuring.data(m_measuring.index(0, 0)).toInt();

	QSqlQueryModel* m_species = new QSqlQueryModel();
	m_species->setQuery("SELECT species FROM t_species WHERE measuring = '" + QString::number(int_measuring) + "'", QSqlDatabase::database("stichprobenauswertung"));
	this->species_cbx->setModel(m_species);

	return;
}

void SourceSelector::measuringUpdated(const QString& text)
{
	this->updateSpeciesComboBox();

	return;
}

QString SourceSelector::getSpecies()
{
	return this->species_cbx->currentText();
}

QString SourceSelector::getMeasuring()
{
	return this->measuring_cbx->currentText();
}
