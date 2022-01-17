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
		connect(this->importer, &AbstractImporter::hasMeasured, this, &SampleModel::sendToHEP);

		break;

	default:
		break;
	}
}

void SampleModel::sendToHEP(MeasuredData data)
{
	// for testing only
	// better function needed
	if (!this->automator->connectToHEP()) {
		std::cout << "Fehler: HEP wurde nicht geöffnet!" << std::endl;
	}

	QString send_string = this->prepareSendString(data);
	if (this->automator->sendMeasuredValues(send_string.toStdString()))
	{
		emit hasSuccessfulSendToHep(data);
	}

	return;
}

QString SampleModel::prepareSendString(MeasuredData data)
{
	QString send_string = "";

	if (this->with_length_and_diameter)
	{
		// format 18.026; length and diameter
		send_string = QString("%1%2").arg(data.length, 0, 'f', 1).arg(data.diameter);
	}

	else
	{
		//format 26; diameter only
		send_string = QString("%1").arg(data.diameter);
	}

	return send_string;
}