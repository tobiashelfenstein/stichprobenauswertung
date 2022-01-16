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