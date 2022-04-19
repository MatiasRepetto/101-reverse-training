#ifndef RW_MEMORY
#define RW_MEMORY
#include <vector>
#include <windows.h>
#include <iostream>
#include <string>

void readPointerData(LPVOID, std::vector<DWORD>, LPCWSTR);
void writePointerData(LPVOID, std::vector<DWORD>, BYTE data[], LPCWSTR);


#endif