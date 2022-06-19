// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "FileImportDialog.h"

#include <iostream>
#include <QMessagebox>
#include <QtWidgets/QComboBox>
#include <QMessagebox>


FileImportDialog::FileImportDialog() : QDialog()
{
	// create model
	// TODO wird das modell nicht später erst gebraucht?!
	this->model = new QFileSystemModel();
	this->model->setNameFilterDisables(false);

	// create main widget with buttons and set as central widget
	this->setupUi();
	this->updateFileList();
}

FileImportDialog::~FileImportDialog()
{
	// nothing to do
}

void FileImportDialog::setupUi()
{
	this->setWindowTitle("Stichprobe öffnen");

	QVBoxLayout* layout = new QVBoxLayout();
	this->setLayout(layout);

	// device selection
	QLabel* device_lbl = new QLabel("Kluppentyp:");
	this->device_cbx = new QComboBox();
	this->device_cbx->setMinimumHeight(60);
	this->device_cbx->addItem("Masser");
	this->device_cbx->addItem("Haglöf");

	connect(this->device_cbx, QOverload<int>::of(&QComboBox::currentIndexChanged), this, QOverload<int>::of(&FileImportDialog::updateFileList));

	layout->addWidget(device_lbl);
	layout->addWidget(this->device_cbx);
	layout->addSpacing(20);

	// file list
	QLabel* file_lbl = new QLabel("Stichprobe:");
	this->file_lvw = new QListView();
	this->file_lvw->setMinimumHeight(300);
	this->file_lvw->setMinimumWidth(500);
	this->file_lvw->setModel(this->model);

	layout->addWidget(file_lbl);
	layout->addWidget(this->file_lvw);
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

void FileImportDialog::updateFileList(int index)
{
	QStringList general = {"*.txt", "*.xml"};
	QStringList filters;
	filters << general.at(index).toLocal8Bit().constData();

	this->model->setNameFilters(filters);
	this->file_lvw->setRootIndex(this->model->setRootPath("examples"));

	return;
}

void FileImportDialog::done(int r)
{
	// see https://www.qtcentre.org/threads/8048-Validate-Data-in-QDialog

	if (QDialog::Accepted == r)
	{
		// ok was pressed
		// check for selected file
		if (!this->file_lvw->selectionModel()->hasSelection())
		{
			QMessageBox msg_box;
			msg_box.setWindowTitle("Stichprobenauswertung");
			msg_box.setIcon(QMessageBox::Warning);
			msg_box.setText("Bitte Datei auswählen!");
			msg_box.setStandardButtons(QMessageBox::Ok);
			msg_box.setDefaultButton(QMessageBox::Ok);
			msg_box.exec();

			return;
		}
	}

	QDialog::done(r);

	return;
}

qint64 FileImportDialog::getDeviceIndex()
{
	return this->device_cbx->currentIndex();
}

QString FileImportDialog::getFilePath()
{
	return this->model->filePath(this->file_lvw->currentIndex());
}
