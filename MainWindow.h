// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QString>

#include "HaglofBluetoothImporter.h"
#include "SampleModel.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	~MainWindow() {};

	void setModel(SampleModel *model);

public slots:
	void blueImportAction();
	void fileImportAction();

private:
	void setupUi();

	QString m_settingsFile = "";
	QString m_serialPort = "";
	SampleModel* model = nullptr;
};

