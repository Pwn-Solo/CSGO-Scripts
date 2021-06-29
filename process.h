#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <tchar.h>

using namespace std;

class process {
public:
	DWORD pid;
	HANDLE procHandle;
	LPSTR windName;

	process(LPSTR wName) {
		this->windName = wName;
		HWND h = FindWindowA(NULL, this->windName);
		GetWindowThreadProcessId(h, &this->pid);
		this->procHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, this->pid);
	}

	DWORD RProcMem(DWORD addr) {
		DWORD buffer;
		ReadProcessMemory(this->procHandle,(LPVOID) addr, &buffer, sizeof(LPVOID), NULL);
		return buffer;
	}

	void WProcMem(DWORD addr, bool value){
		WriteProcessMemory(this->procHandle,(LPVOID) addr, &value, sizeof(value), NULL);
	}

	uintptr_t GetModuleBaseAddr(const wchar_t* ModuleName) {
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, this->pid);
		uintptr_t ModuleBase = 0;


		if (hSnapshot == INVALID_HANDLE_VALUE) {
			cout << "GetModule Failed" << endl;
			CloseHandle(hSnapshot);
			return 0;
		}
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hSnapshot, &modEntry)) {

			cout << "Error Module32First" << endl;
			CloseHandle(hSnapshot);
		}
		do
		{
			//_tprintf(TEXT("\n\n     MODULE NAME:     %s"), modEntry.szModule);
			if (!_wcsicmp(modEntry.szModule, ModuleName)) {
				
				cout << "Module Found" << endl;
				break;
			}
		} while (Module32Next(hSnapshot, &modEntry));
		return (uintptr_t)modEntry.modBaseAddr;

	}

};
