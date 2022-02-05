// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.


#include "Windows.h"

#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtGui/QFont>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// general font settings
	QFont font = app.font();
	font.setPointSize(24);
	app.setFont(font);

	MainWindow stichprobenauswertung;
	stichprobenauswertung.show();

	return app.exec();
}