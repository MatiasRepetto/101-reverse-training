#include <windows.h>

DWORD* playerBase;
DWORD* gameBase;
DWORD* object;
DWORD*  return_addr = (DWORD*) 0x0CD8240; // Return to exec addr before code caving

__declspec(naked) void codeCave(){ // __declspec(naked) is to avoid adding stack frame 
    __asm{
        pushad // pushes 8 registers into the stack
    }

    playerBase = (DWORD*)0x1562DA4;
    gameBase = (DWORD*)(*playerBase + 0xA90);
    object = (DWORD*)(*gameBase + 0x4);

    __asm{
        popad // retrives the 8 registers to previous state
        mov eax, dword ptr ds:[ecx]
        lea esi, dword ptr ds:[esi]
        jmp return_addr  
    }
}

bool WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved){
    DWORD oldProtect;
    unsigned char* hookLocation = (unsigned char*)0x0CD823A;

    if(dwReason == DLL_PROCESS_ATTACH){
        unsigned char* hookLocation1;
        VirtualProtect((VOID*)hookLocation1, 6, PAGE_EXECUTE_READWRITE, &oldProtect); // changin the permission of the memo location 
                                                                                      // so we can modify and store previous mem protection
        *hookLocation = 0xE9; // JMP instruction with the 0xE9 and then JMP to our code cave
        *(DWORD*)(hookLocation1 + 1) = (DWORD)&codeCave - ((DWORD)hookLocation +5);
        *(hookLocation + 5) = 0x90;
    }
    return true;
}