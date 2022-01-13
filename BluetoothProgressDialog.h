#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtGui/QIcon>
#include <QtCore/QSize>
#include <QtWidgets/QPushButton>
#include <QString>


class BluetoothProgressDialog : public QDialog
{
	Q_OBJECT

public:
	BluetoothProgressDialog();
	~BluetoothProgressDialog();

	void setupUi();
};

