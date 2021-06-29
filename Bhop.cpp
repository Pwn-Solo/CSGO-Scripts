// Bhop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "process.h"

#define ON_GROUND 257
#define playerbase 0x524A6D4
#define m_fFlags 0x104 

int main()
{
    process csgo((LPSTR)"Counter-Strike: Global Offensive");
    DWORD base = csgo.GetModuleBaseAddr(L"client.dll");
    printf("Base Address = 0x%08X", (DWORD)base);

    DWORD LocalPlayer;
    int Localflags;

    while (true) {
        
        DWORD ptr = csgo.RProcMem(base + playerbase) + m_fFlags;
        DWORD jmp = csgo.RProcMem((DWORD)ptr);

        //cout << jmp << endl;
        if (jmp == ON_GROUND && GetAsyncKeyState(VK_SPACE)) {
            DWORD forcejmp = base + 0x524BF4C;
            //cout << "canjump" << endl;
            csgo.WProcMem(forcejmp, true);
            Sleep(25);
            csgo.WProcMem(forcejmp, false);
            
        } 
    }
}

