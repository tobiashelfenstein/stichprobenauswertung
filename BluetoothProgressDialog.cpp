// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "BluetoothProgressDialog.h"

#include <iostream>
#include <Windows.h>


BluetoothProgressDialog::BluetoothProgressDialog() : QDialog()
{

	this->setupUi();
}

BluetoothProgressDialog::~BluetoothProgressDialog()
{
	// nothing to do
}

void BluetoothProgressDialog::setupUi()
{
	this->setWindowTitle("Datenübertragung");

	QVBoxLayout* main_layout = new QVBoxLayout(this);
	this->setLayout(main_layout);

	// status label
	QLabel* lbl_status = new QLabel("Kluppdaten: übertragen ...");
	main_layout->addWidget(lbl_status);

	// buttons
	QHBoxLayout* button_layout = new QHBoxLayout();
	main_layout->addLayout(button_layout);

	QIcon icn_abort(":/icons/application-back.svg");
	QPushButton* btn_import_abort = new QPushButton(icn_abort, "");
	btn_import_abort->setMinimumHeight(60);
	btn_import_abort->setIconSize(QSize(40, 40));
	button_layout->addWidget(btn_import_abort);

	connect(btn_import_abort, &QPushButton::clicked, this, &BluetoothProgressDialog::reject);

	QIcon icn_finish(":/icons/application-next.svg");
	QPushButton* btn_import_finish = new QPushButton(icn_finish, "");
	btn_import_finish->setMinimumHeight(60);
	btn_import_finish->setIconSize(QSize(40, 40));
	btn_import_finish->setDefault(true);
	button_layout->addWidget(btn_import_finish);

	connect(btn_import_finish, &QPushButton::clicked, this, &BluetoothProgressDialog::accept);

	return;
}

void BluetoothProgressDialog::successfulSendToHep(MeasuredData data)
{
	Beep(2200, 500);

	/*Beep(2000, 500);
	Sleep(10);
	Beep(2000, 3000);*/

	

	return;
}
