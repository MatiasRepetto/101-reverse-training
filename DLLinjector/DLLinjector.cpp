#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

DWORD GetProcId(LPCSTR procName){
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE){
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))//iterador de los procesos {
            do{
                if (!_stricmp((char*)procEntry.szExeFile, procName)){
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry)); // avanza iterador
        }
    }
    CloseHandle(hSnap);
    return procId;
}

int main(LPCSTR pNameargv, LPCSTR dllPathargv){
    
    int timer = 0;
    LPCSTR dllPath = dllPathargv;
    LPCSTR procName = pNameargv;
    DWORD procId = 0;

    if(!procName){
        char* auxProcName;
        std::cout << "Insert process name: " << std::endl;
        std::cin >> auxProcName;
        pNameargv = (LPCSTR)auxProcName;
    }

    if(!dllPath){
        char* auxDllPath;
        std::cout << "Insert DLL Path: " << std::endl;
        std::cin >> auxDllPath;
        dllPath = (LPCSTR)auxDllPath;
    } 

    while (!procId && timer < 30)
    {
        procId = GetProcId(procName);
        timer++;
        Sleep(30);
    }
    if(procId){
        HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

        if (hProc && hProc != INVALID_HANDLE_VALUE){
            void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
            WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
            HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);
            if(hThread){
                CloseHandle(hThread);
            }
        }
        if (hProc){
            CloseHandle(hProc);
        }
    }else{
        std::cout << "Error process not found" << std::endl;
    }
    return 0;
}
