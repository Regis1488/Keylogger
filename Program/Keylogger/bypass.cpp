#include "bypass.h"
#include <Windows.h>
#include <setupapi.h>
#include <winternl.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <TlHelp32.h>

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

    if(systeminfo.dwNumberOfProcessors < 2)
        exit(0);
    
    MEMORYSTATUSEX memorystatus;
    memorystatus.dwLength = sizeof(memorystatus);
    GlobalMemoryStatusEx(&memorystatus);
    DWORD RAM = memorystatus.ullTotalPhys / 1024 / 1024;
    if(RAM < 1024)
        exit(0);
    
    HANDLE hDevice = CreateFileW(L"\\\\.\\PhysicalDrive0", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    DISK_GEOMETRY pdisk;
    DWORD junk = 0;
    DeviceIoControl(hDevice, IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, &pdisk, sizeof(pdisk), &junk, (LPOVERLAPPED) NULL);
    DWORD diskSize = pdisk.Cylinders.QuadPart * (ULONG)pdisk.TracksPerCylinder * (ULONG)pdisk.SectorsPerTrack * (ULONG)pdisk.BytesPerSector / 1024 / 1024 / 1024;
    if(diskSize < 100)
        exit(0);

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
    if(wcsstr(HDDName,L"VBOX")) exit(0);

    OBJECT_ATTRIBUTES objectAttributes;
    UNICODE_STRING uDeviceName;
    RtlSecureZeroMemory(&objectAttributes, sizeof(objectAttributes));
    RtlInitUnicodeString(&uDeviceName, L"\\Device\\Harddisk0\\Partition0");

    InitializeObjectAttributes(&objectAttributes, &uDeviceName, OBJ_CASE_INSENSITIVE, NULL, NULL);
    HANDLE hDevice = NULL;

    IO_STATUS_BLOCK iosStatusBlock;
    NTSTATUS status = NtCreateFile(&hDevice, FILE_READ_ATTRIBUTES, &objectAttributes, &iosStatusBlock, NULL, FILE_ATTRIBUTE_NORMAL, FILE_SHARE_READ | FILE_SHARE_WRITE, FILE_OPEN, FILE_SYNCHRONOUS_IO_NONALERT, NULL, 0);
    if(NT_SUCCESS(status)) exit(0);

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
                if(!memcmp(mac, "\x00\x00\x27", 3)) exit(0);
            }
            pAdaptatersAdresses = pAdaptatersAdresses->Next;
        }
    }

    WIN32_FIND_DATAW findFileData;

    if(FindFirstFileW(L"C:\\Windows\\System32\\Vbox*.dll", &findFileData) != INVALID_HANDLE_VALUE) exit(0);

    HKEY hkResult;
    if(RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Services\\VBOXSF", 0, KEY_READ, &hkResult) == ERROR_SUCCESS) exit(0);

    DWORD parentID = GetParentPID(GetCurrentProcessId());
    WCHAR parentName[MAX_PATH+1];
    DWORD dwParentName = MAX_PATH;

    HANDLE hParent = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, parentID);
    QueryFullProcessImageNameW(hParent,0,parentName,&dwParentName);
    CharUpperW(parentName);
    if(wcsstr(parentName,L"WINDBG")) exit(0);

    bool debugged = false;
    EnumWindows(EnumWindowsProc, (LPARAM)&debugged);
    if(debugged) exit(0);

    
    
}