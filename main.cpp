#include "Windows.h"

#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QtGui/QFont>

int main(int argc, char* argv[])
{
	//HaglofBluetoothImporter importer;

	//importer.connect("\\\\.\\COM11", 9600);

	//int d = 0;

	//importer.read();

	//cout << "Hello" << endl;
	////HEPAutomator hep = HEPAutomator();
	////hep.connectToHEP();
	////hep.sendMeasuredValues(9);

	//// test
	////char file[] = "examples/kluppfall.txt";
	////MasserFileImporter test = MasserFileImporter();
	////test.importTXTFile(file);
	////test.readAll();

	//HANDLE hCom;

	//hCom = CreateFile(L"\\\\.\\COM11", GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

	////DCB dcb;
	////dcb.DCBlength = sizeof(DCB);

	//char ReadData;
	//char SerialBuffer[64];
	//DWORD NoBytesRead;
	//unsigned char loop = 0;
	//DWORD dwEventMask;

	//SetCommMask(hCom, EV_RXCHAR);
	//WaitCommEvent(hCom, &dwEventMask, NULL);

	//do
	//{
	//	ReadFile(hCom, &ReadData, sizeof(ReadData), &NoBytesRead, NULL);
	//	wcout << ReadData << endl;
	//	SerialBuffer[loop] = ReadData;
	//	++loop;
	//} while (NoBytesRead > 0);

	//CloseHandle(hCom);

	QApplication app(argc, argv);

	// general font settings
	QFont font = app.font();
	font.setPointSize(24);
	app.setFont(font);

	MainWindow stichprobenauswertung;
	stichprobenauswertung.show();

	return app.exec();
}