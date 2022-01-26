#pragma once

#include <QObject>
#include <QtBluetooth/QBluetoothDeviceInfo>
#include <QtBluetooth/QLowEnergyController>

class BluetoothDevice : public QObject
{

	Q_OBJECT

public:
	BluetoothDevice();
	~BluetoothDevice();

public slots:
	void addDevice(const QBluetoothDeviceInfo&);
	void serviceDiscovered(const QBluetoothUuid&);

private:
	QLowEnergyController* control;

};

