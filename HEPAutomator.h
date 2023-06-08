// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>

#include <QObject>

class HEPAutomator
{
private:
	HWND m_hWndHandle = NULL;

public:
	HEPAutomator();
	~HEPAutomator() {};

	void connectToHEP();
	static BOOL CALLBACK findHEPVisibleWindow(HWND handle, LPARAM lparam);

	bool sendMeasuredValues(std::string send_string);
	void clearInputField(int bsCount);
};

