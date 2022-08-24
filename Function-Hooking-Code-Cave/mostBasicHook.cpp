#include <stdio.h>
#include <windows.h>

DWORD patch_cliprgn = 0x004658D8;
DWORD* base_address;
DWORD return_address;

void __declspec(naked) cliprgn_hook(){
    __asm {
        pop return_address
        mov[base_address], esp
        pushad
    }

    if(*(base_address + 0x2) == 820 && *(base_address + 0x4) == 200){
        *(base_address + 0x2) == 600;
        *(base_address + 0x4) == 425;
    }

    __asm{
        popad
        push 0x53328B
        push return_address
        ret
    }
}
