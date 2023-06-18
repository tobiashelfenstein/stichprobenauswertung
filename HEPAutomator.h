// Copyright (C) 2023 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include <QObject>

class HEPAutomator
{
private:
	static BOOL CALLBACK findHEPVisibleWindow(HWND handle, LPARAM lparam);

public:
	HEPAutomator() {};
	~HEPAutomator() {};

	void connectToHEP();

	bool sendMeasuredValues(std::string send_string);
	void clearInputField(int bsCount);
};

