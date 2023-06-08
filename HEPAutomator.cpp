// Copyright (C) 2022 Tobias Helfenstein <tobias@die-softwarezimmerei.de>.
// Licensed under the GPLv3 License. See LICENSE file in the project root for license information.

#include "HEPAutomator.h"
#include <stdexcept>
#include <QDebug>

HEPAutomator::HEPAutomator()
{
	// find visible window of HEP and get the window handle
	EnumWindows(findHEPVisibleWindow, (LPARAM)&m_hWndHandle);

	// throw exception, if HEP is not open
	if (m_hWndHandle == NULL || !IsWindow(m_hWndHandle))
	{
		throw std::runtime_error("HEPAutomator() hep is not open");
	}
}

void HEPAutomator::connectToHEP()
{
	// check if hep was closed an throw an exception
	if (m_hWndHandle == NULL || !IsWindow(m_hWndHandle))
	{
		throw std::runtime_error("hep was closed");
	}

	ShowWindow(m_hWndHandle, SW_RESTORE); // neeed, if window is minimized
	BringWindowToTop(m_hWndHandle);
	SetForegroundWindow(m_hWndHandle);
}

BOOL CALLBACK HEPAutomator::findHEPVisibleWindow(HWND handle, LPARAM lparam)
{
	HWND& hWndHandle = *(HWND*)lparam;

	const int length = 31; // Holzaufnahme LF Rheinland-Pfalz
	wchar_t* buffer = new wchar_t[length + 1];

	GetWindowText(handle, buffer, length + 1);
	std::wstring caption(buffer);
	delete[] buffer;

	if (caption.compare(L"Holzaufnahme LF Rheinland-Pfalz") == 0)
	{
		if (IsWindowVisible(handle))
		{
			hWndHandle = handle;
		}
	}

	return true;
}

bool HEPAutomator::sendMeasuredValues(std::string send_string)
{
	// keyboard inputs
	std::vector<INPUT> inputs;

	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;

	for (int i = 0; i < send_string.length(); i++)
	{
		// key down event for data
		ip.ki.dwFlags = 0;
		ip.ki.wVk = (send_string.at(i) == '.') ? VK_OEM_PERIOD : '0' + send_string.at(i);
		inputs.push_back(ip);

		// key up event for data
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		inputs.push_back(ip);
	}

	// key down event for return
	ip.ki.dwFlags = 0;
	ip.ki.wVk = VK_RETURN;
	inputs.push_back(ip);

	// key up event for return
	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	inputs.push_back(ip);

	SendInput(inputs.size(), inputs.data(), sizeof(INPUT));

	return true;
}

void HEPAutomator::clearInputField(int bsCount)
{
	// keyboard inputs
	std::vector<INPUT> backspaces;
	INPUT bs = { 0 };
	bs.type = INPUT_KEYBOARD;

	// for loop is necessary to copmplety reset the input field
	for (int i = 0; i < bsCount; i++)
	{
		// key down event for backspace
		bs.ki.dwFlags = 0;
		bs.ki.wVk = VK_BACK;
		backspaces.push_back(bs);

		// key up event for backspace
		bs.ki.dwFlags = KEYEVENTF_KEYUP;
		backspaces.push_back(bs);
	}

	// send backspcaes to HEP
	SendInput(backspaces.size(), backspaces.data(), sizeof(INPUT));
}