// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "SourceSelector.h"

#include <iostream>
#include <QMessagebox>
#include <QtWidgets/QComboBox>
#include <QMessagebox>


SourceSelector::SourceSelector() : QDialog()
{
	this->setupUi();
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

	//connect(this->device_cbx, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&FileImportDialog::updateFileList));

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
