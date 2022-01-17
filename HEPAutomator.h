#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include <QObject>

class HEPAutomator
{
private:

public:
	HEPAutomator();
	~HEPAutomator();

	bool connectToHEP();
	static BOOL CALLBACK findHEPVisibleWindow(HWND handle, LPARAM lparam);

	bool sendMeasuredValues(std::string send_string);
};

