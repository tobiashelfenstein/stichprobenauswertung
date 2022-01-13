#include "MainWindow.h"
#include "BluetoothProgressDialog.h"
#include "HaglofBluetoothImporter.h"

#include <iostream>


MainWindow::MainWindow() : QMainWindow()
{
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
	layout->addWidget(btn_file_import);

	// bluetooth import button
	QPushButton *btn_bluetooth_import = new QPushButton("Bluetooth übertragen");
	btn_bluetooth_import->setMinimumHeight(60);
	layout->addWidget(btn_bluetooth_import);

	connect(btn_bluetooth_import, SIGNAL(clicked()), this, SLOT(blueImportAction()));

	layout->addSpacing(30);

	// quit button
	QPushButton *btn_quit = new QPushButton("Beenden");
	btn_quit->setMinimumHeight(60);
	layout->addWidget(btn_quit);

	this->setCentralWidget(central_widget);

	return;
}

void MainWindow::blueImportAction()
{
	this->importer = new HaglofBluetoothImporter();
	importer->open("\\\\.\\COM11", 9600);

	BluetoothProgressDialog dlg_progress;
	dlg_progress.exec();

	return;
}
