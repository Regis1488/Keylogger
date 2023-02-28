/*
                            Bypass.h

                            This Section is about bypassing AVs
                            learn more about :  anti dynamic analysis & sandboxes

*/
#include <Windows.h>

bool HWIDCheck();
DWORD GetParentPID(DWORD pid);
BOOL CALLBACK EnumWindowsProc(HWND hWindow, LPARAM parameter);
bool CALLBACK MonitorDector(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lpRect, LPARAM data);