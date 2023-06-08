// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "BluetoothProgressDialog.h"

#include <iostream>
#include <Windows.h>


BluetoothProgressDialog::BluetoothProgressDialog() : QDialog()
{
	// create main widget with buttons and labels
	this->setupUi();
}

void BluetoothProgressDialog::setupUi()
{
	this->setWindowTitle("Datenübertragung");

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	this->setLayout(main_layout);

	// status label
	QLabel* lbl_status = new QLabel("Kluppdaten: übertragen ...");
	main_layout->addWidget(lbl_status);

	main_layout->addSpacing(10);

	// display last measured length
	QLabel* lblLength = new QLabel("Länge: #NV");
	lblLength->setContentsMargins(20, 0, 0, 0); // default is 0, so we need no copy of margins
	main_layout->addWidget(lblLength);

	connect(this, &BluetoothProgressDialog::measuredLength, lblLength, &QLabel::setText);

	// display last measured diameter
	QLabel* lblDiameter = new QLabel("Durchmesser: #NV");
	lblDiameter->setContentsMargins(20, 0, 0, 0); // default is 0, so we need no copy of margins
	main_layout->addWidget(lblDiameter);

	connect(this, &BluetoothProgressDialog::measuredDiameter, lblDiameter, &QLabel::setText);

	main_layout->addSpacing(40);

	// buttons
	QHBoxLayout* button_layout = new QHBoxLayout();
	main_layout->addLayout(button_layout);

	QIcon icn_finish(":/icons/application-next.svg");
	QPushButton* btn_import_finish = new QPushButton(icn_finish, "");
	btn_import_finish->setMinimumHeight(60);
	btn_import_finish->setIconSize(QSize(40, 40));
	btn_import_finish->setDefault(true);
	button_layout->addWidget(btn_import_finish);

	connect(btn_import_finish, &QPushButton::clicked, this, &BluetoothProgressDialog::accept);
}

void BluetoothProgressDialog::successfulSendToHep(MeasuredData data)
{
	// create acoustic beep signal 
	Beep(2200, 500);

	//emit measuredLength(QString("Länge: %1").arg(data.length));
	emit measuredDiameter(QString("Durchmesser: %1").arg(data.diameter));
}
