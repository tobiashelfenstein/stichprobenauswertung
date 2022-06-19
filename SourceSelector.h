// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <QtWidgets/QDialog>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QListView>
#include <QtWidgets/QFileSystemModel>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFileIconProvider>
#include <QtGui/QIcon>
#include <QtCore/QSize>
#include <QFileInfo>
#include <QString>


class SourceSelector : public QDialog
{
	Q_OBJECT

public:
	SourceSelector();
	~SourceSelector();

	void setupUi();

	void getDeviceIndex();
	QString getFilePath();

	QComboBox* measuring_cbx;
	QComboBox* species_cbx;

public slots:


private:
	QFileSystemModel* model;
	QListView* file_lvw;
};

