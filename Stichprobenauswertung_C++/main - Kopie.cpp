#include "Windows.h"
#include <iostream>
#include <vector>

void SendKey(HWND hWndTargetWindow, BYTE virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}

void sendNumberToHep(int num)
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
	INPUT ip = {0};
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
}

void pressReturn()
{

	//INPUT keyReturn[2] = {};
	//ZeroMemory(keyReturn, sizeof(keyReturn));

	//keyReturn[0].type = INPUT_KEYBOARD;
	//keyReturn[0].ki.dwFlags = 0;
	//keyReturn[0].ki.wVk = VK_RETURN; // VK_RETURN is the code of return key on keyboard

	//keyReturn[1].type = INPUT_KEYBOARD;
	//keyReturn[1].ki.dwFlags = KEYEVENTF_KEYUP;
	//keyReturn[1].ki.wVk = VK_RETURN; // VK_RETURN is the code of return key on keyboard

	//SendInput(1, keyReturn, sizeof(INPUT));

	char test[2];
	test[0] = '4';
	test[1] = '1';

	sendNumberToHep(103);
}

void InputToHEP()
{
	/*INPUT inputs[4] = {};
	ZeroMemory(inputs, sizeof(inputs));

	inputs[0].type = INPUT_KEYBOARD;
	inputs[0].ki.wVk = '8';
	inputs[0].ki.wScan = '8';

	inputs[1].type = INPUT_KEYBOARD;
	inputs[1].ki.wVk = '8';
	inputs[1].ki.wScan = '8';
	inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

	inputs[2].type = INPUT_KEYBOARD;
	inputs[2].ki.wVk = '2';
	inputs[2].ki.wScan = '2';

	inputs[3].type = INPUT_KEYBOARD;
	inputs[3].ki.wVk = '2';
	inputs[3].ki.wScan = '2';
	inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

	UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));*/

	pressReturn();

}

static BOOL CALLBACK FindHEPVisibleWindow(HWND handle, LPARAM lparam)
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

int main(int argc, char* argv[])
{
	HWND hWndHandle = NULL;
	EnumWindows(FindHEPVisibleWindow, (LPARAM)&hWndHandle);

	DWORD currentTID = GetCurrentThreadId();
	DWORD HEPTID = GetWindowThreadProcessId(hWndHandle, LPDWORD(0));

	//AttachThreadInput(dwHEPID, dwMyID, true);
	BringWindowToTop(hWndHandle);
	ShowWindow(hWndHandle, SW_RESTORE);
	BringWindowToTop(hWndHandle);
	SetForegroundWindow(hWndHandle);
	SetFocus(hWndHandle);
	//PostMessage(hWndTarget, WM_SYSCOMMAND, SC_RESTORE, 0);
	//SetFocus(hWndTarget);
	//SetForegroundWindow(hWndTarget);
	//{
	InputToHEP();
	//AttachThreadInput(dwHEPID, dwMyID, false);


	/*HWND hWndTarget = FindWindow(NULL, L"Holzaufnahme LF Rheinland-Pfalz V4.04n");

	DWORD dwProcessID = 0;
	dwProcessID =  GetWindowThreadProcessId(hWndTarget, LPDWORD(0));

	HWND test = hWndTarget;
	HWND HEP = NULL;
	DWORD dwTestID = 0;
	while (test != NULL)
	{
		test = GetWindow(test, GW_HWNDNEXT);
		dwTestID = GetWindowThreadProcessId(test, LPDWORD(0));

		if (dwTestID == dwProcessID)
		{
			if (IsWindowVisible(test))
			{
				HEP = test;
			}
		}
		
	}

	//DWORD dwMyID = GetCurrentThreadId();
	//DWORD dwHEPID = GetWindowThreadProcessId(hWndTarget, LPDWORD(0));

	//AttachThreadInput(dwHEPID, dwMyID, true);
	//BringWindowToTop(hWndTarget);
	ShowWindow(HEP, SW_SHOW);
	BringWindowToTop(HEP);
	SetForegroundWindow(HEP);
	SetFocus(HEP);
	//PostMessage(hWndTarget, WM_SYSCOMMAND, SC_RESTORE, 0);
	//SetFocus(hWndTarget);
	//SetForegroundWindow(hWndTarget);
	//{
	InputToHEP();
	//AttachThreadInput(dwHEPID, dwMyID, false);
	//SendKey(HEP, '10');
	//SendKey(HEP, VK_RETURN);
	//InputToHEP();

	//PostMessage(HEP, WM_KEYDOWN, '9', 0);
	//PostMessage(HEP, WM_KEYUP, '9', 0);
	//}
	
	*/


	return 0;
}