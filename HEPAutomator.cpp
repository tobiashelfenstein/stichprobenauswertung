#include "HEPAutomator.h"

HEPAutomator::HEPAutomator()
{
	// nothing to do
}

HEPAutomator::~HEPAutomator()
{
	// nothing to do
}

bool HEPAutomator::connectToHEP()
{
	HWND hWndHandle = NULL;
	EnumWindows(findHEPVisibleWindow, (LPARAM)&hWndHandle);

	if (hWndHandle != NULL && IsWindow(hWndHandle))
	{
		ShowWindow(hWndHandle, SW_RESTORE); // neeed, if window is minimized
		//Sleep(1000);

		BringWindowToTop(hWndHandle);
		SetForegroundWindow(hWndHandle);

		return TRUE;
	}

	return FALSE;
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
			//std::wcout << handle << " " << caption << std::endl;
			hWndHandle = handle;
		}
	}

	return TRUE;
}

bool HEPAutomator::sendMeasuredValues(int num)
{
	// split number into digits
	std::vector<int> digits;
	while (num > 0)
	{
		digits.push_back(num % 10);
		num /= 10;
	}

	// keyboard inputs
	std::vector<INPUT> inputs;
	INPUT ip = { 0 };
	ip.type = INPUT_KEYBOARD;

	for (std::vector<int>::reverse_iterator i = digits.rbegin(); i != digits.rend(); i++)
	{
		// key down event for data
		ip.ki.dwFlags = 0;
		ip.ki.wVk = '0' + *i;
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

	return TRUE;
}