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
	~BluetoothProgressDialog();

	void setupUi();

public slots:
	void successfulSendToHep(MeasuredData data);
};

