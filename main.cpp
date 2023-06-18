// Copyright (C) 2023 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.


#include "Windows.h"
#include <exception>

#include "MainWindow.h"
#include "SampleModel.h"
#include <QtWidgets/QApplication>
#include <QtGui/QFont>
#include <QMessagebox>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// general font settings
	QFont font = app.font();
	font.setPointSize(24);
	app.setFont(font);

	// create the main window for "stichprobenauswertung"
	// create the model for the main window
	// TODO better solution e.g. initialize model instead constructor
	SampleModel* mainModel = new SampleModel();

	MainWindow mainWindow;
	mainWindow.setModel(mainModel);
	mainWindow.show();

	return app.exec();
}