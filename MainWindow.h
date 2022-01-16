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
	~MainWindow();

	void setupUi();

public slots:
	void blueImportAction();

private:
	SampleModel* model;
};

