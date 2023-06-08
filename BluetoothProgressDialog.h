// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtGui/QIcon>
#include <QtCore/QSize>
#include <QtWidgets/QPushButton>
#include <QString>

#include "AbstractImporter.h"


class BluetoothProgressDialog : public QDialog
{
	Q_OBJECT

public:
	BluetoothProgressDialog();
	~BluetoothProgressDialog() {};

	void setupUi();

public slots:
	void successfulSendToHep(MeasuredData data);

signals:
	void measuredDiameter(const QString& diameter);
	void measuredLength(const QString& length);
};

