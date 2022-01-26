#include "BluetoothDevice.h"

#include <iostream>

#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>

#include <QList>

BluetoothDevice::BluetoothDevice()
{
	// nothing to do
	QBluetoothDeviceDiscoveryAgent* agent = new QBluetoothDeviceDiscoveryAgent(this);
	agent->setLowEnergyDiscoveryTimeout(5000);

	connect(agent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered, this, &BluetoothDevice::addDevice);

	std::cout << "Starte Suche..." << std::endl;
	agent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

BluetoothDevice::~BluetoothDevice()
{
	// nothing to do
}

void BluetoothDevice::addDevice(const QBluetoothDeviceInfo& device)
{

	this->control = QLowEnergyController::createCentral(device, this);
	connect(this->control, &QLowEnergyController::serviceDiscovered, this, &BluetoothDevice::serviceDiscovered);
	connect(this->control, &QLowEnergyController::connected, this, [this]() {std::cout << "discouver" << std::endl;  this->control->discoverServices(); });

	std::cout << "Verbinden ..." << std::endl;
	this->control->connectToDevice();

	////service = control->createServiceObject()
	//QList<QBluetoothUuid> test = control->services();
	//for (int i = 0; i < test.count(); i++)
	//{
	//	std::cout << QString(test[i].toUInt32()).toStdString() << std::endl;
	//}
}

void BluetoothDevice::serviceDiscovered(const QBluetoothUuid& gatt)
{
	std::cout << gatt.toString().toStdString() << std::endl;
}