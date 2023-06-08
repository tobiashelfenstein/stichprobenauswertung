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
	// if hep is not open notify the user
	// TODO better solution e.g. initialize model instead constructor
	SampleModel* mainModel = nullptr;

	try {
		mainModel = new SampleModel();
	}
	catch (const std::runtime_error& e)
	{
		// notify the user
		QMessageBox msg_box;
		msg_box.setWindowTitle("Stichprobenauswertung");
		msg_box.setIcon(QMessageBox::Critical);
		msg_box.setText("HEP wurde nicht gestartet! Bitte starten Sie zuerst HEP.");
		msg_box.setStandardButtons(QMessageBox::Ok);

		msg_box.exec();
		
		return 1;
	}

	MainWindow mainWindow;
	mainWindow.setModel(mainModel);
	mainWindow.show();

	return app.exec();
}