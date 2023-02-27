#include <Windows.h>


LRESULT __stdcall KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
bool isCapsLock();
bool isShift();