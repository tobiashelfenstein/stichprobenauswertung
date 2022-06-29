// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "MainWindow.h"
#include "BluetoothProgressDialog.h"
#include "HaglofBluetoothImporter.h"
#include "FileImportDialog.h"
#include "SourceSelector.h"

#include <iostream>
#include <QMessagebox>
#include <QtWidgets/QDialog>


MainWindow::MainWindow() : QMainWindow()
{
	// create model
	// alternativ create the model in main function
	this->model = new SampleModel();

	// create main widget with buttons and set as central widget
	this->setupUi();
}

MainWindow::~MainWindow()
{
	// nothing to do
}

void MainWindow::setupUi()
{
	this->setWindowTitle("Stichprobenauswertung");

	QWidget *central_widget = new QWidget();

	QVBoxLayout *layout = new QVBoxLayout(central_widget);

	// file import button
	QPushButton *btn_file_import = new QPushButton("Stichprobe einlesen");
	btn_file_import->setMinimumHeight(60);

	connect(btn_file_import, &QPushButton::clicked, this, &MainWindow::fileImportAction);

	layout->addWidget(btn_file_import);

	// bluetooth import button
	QPushButton *btn_bluetooth_import = new QPushButton("Bluetooth übertragen");
	btn_bluetooth_import->setMinimumHeight(60);
	layout->addWidget(btn_bluetooth_import);

	connect(btn_bluetooth_import, &QPushButton::clicked, this, &MainWindow::blueImportAction);

	layout->addSpacing(30);

	// quit button
	QPushButton *btn_quit = new QPushButton("Beenden");
	btn_quit->setMinimumHeight(60);
	layout->addWidget(btn_quit);

	connect(btn_quit, &QPushButton::clicked, this, &MainWindow::close);

	this->setCentralWidget(central_widget);

	return;
}

void MainWindow::blueImportAction()
{
	// TODO
	// settings dialog
	// port selecion; baud selection
	// lenth and diameter selection

	// ask for length and diameter measuring
	qint64 msg_ret = 0;
	QMessageBox msg_box;
	msg_box.setWindowTitle("Stichprobenauswertung");
	msg_box.setIcon(QMessageBox::Question);
	msg_box.setText("Nur Durchmesser übertragen?");
	msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msg_box.setDefaultButton(QMessageBox::Yes);

	bool with_length_and_diameter = false;
	if (msg_box.exec() == QMessageBox::No)
	{
		with_length_and_diameter = true;
	}

	this->model->initializeImporter(HAGLOF, "\\\\.\\COM8", 9600, with_length_and_diameter);

	BluetoothProgressDialog dlg_progress;
	connect(this->model, &SampleModel::hasSuccessfulSendToHep, &dlg_progress, &BluetoothProgressDialog::successfulSendToHep);

	dlg_progress.exec();

	

	return;
}

void MainWindow::fileImportAction()
{
	//this->model->initializeImporter(HAGLOF);
	//this->model->initializeImporter(MASSER);
	//this->model->getMeasuring();

	FileImportDialog dlg_file_import; // TODO besser zeiger oder direkte Instanz
	if (dlg_file_import.exec() == QDialog::Accepted)
	{
		this->model->initializeImporter(dlg_file_import.getDeviceIndex(), dlg_file_import.getFilePath().toLatin1().constData());
		//this->model->getMeasuring();
	}

	SourceSelector dlg_source_selector;
	if (dlg_source_selector.exec() == QDialog::Accepted)
	{
		this->model->readFromDatabase(dlg_source_selector.getMeasuring(), dlg_source_selector.getSpecies());
	}

	return;
}
