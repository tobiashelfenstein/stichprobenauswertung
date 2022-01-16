#include "SampleModel.h"
#include "HaglofBluetoothImporter.h"

SampleModel::SampleModel() : QObject()
{
	this->automator = new HEPAutomator();
}

SampleModel::~SampleModel()
{
	// nothing to do
}

void SampleModel::initializeImporter(MANUFACTURERS m, QString port, qint64 rate)
{
	this->manufacturer = m;

	switch (this->manufacturer)
	{
	case MASSER:
		// manufacture is masser

		break;

	case HAGLOF:
		// manufacturer is haglöf
		// open connection to serial port
		this->importer = new HaglofBluetoothImporter();
		this->importer->open(port, rate);

		// connect to importer events
		connect(this->importer, &AbstractImporter::diameter, this, &SampleModel::sendToHEP);

		break;

	default:
		break;
	}
}

void SampleModel::sendToHEP(int diameter)
{
	// for testing only
	// better function needed
	if (!this->automator->connectToHEP()) {
		std::cout << "Fehler: HEP wurde nicht geöffnet!" << std::endl;
	}

	this->automator->sendMeasuredValues(diameter);

	return;
}