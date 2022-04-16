#include <windows.h>
#include "../include/rwMemory.h"

float readPointerData(LPVOID BaseAddr, int Offs, LPCWSTR baseWnd){
	float val ;
    int Buffer;
 
	// Process Handle
	HWND hwnd = FindWindow(NULL, baseWnd);
    HANDLE phandle;
    DWORD pid;
	
	GetWindowThreadProcessId(hwnd, &pid);
    phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); // Gain full Access on the process.
													   // Note: Needs full administrative rights
													   //       on both the injector and target .exe
                                                       // Abriendo un handle cada que se llama a la funcion, esto no es lo mas optimo
 
	// Reading Basepointer
	ReadProcessMemory(phandle, BaseAddr, &Buffer, 4, NULL); // Store the Basepointer into Buffer
	Buffer += Offs; // Add Offset // hay mas de un offset operar con un vector DWORD
 
    ReadProcessMemory(phandle, LPVOID(Buffer), &val, 4, NULL); // Read back the pointer and store into val
 
	return val;
    CloseHandle(phandle);
}

void writePointerData(LPVOID BaseAddr, int Offs, BYTE data[], LPCWSTR baseWnd){
    int Buffer;
	HWND hwnd = FindWindow(NULL, baseWnd);
    HANDLE phandle;
    DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
    phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); // Abriendo un handle cada que se llama a la funcion, esto no es lo mas optimo
	ReadProcessMemory(phandle, BaseAddr, &Buffer, 4, NULL);
	Buffer += Offs; // hay mas de un offset operar con un vector DWORD
	DWORD dataSize = sizeof(data); 
	BYTE datas[sizeof(data)];
	memcpy(datas, data, sizeof(data));
    WriteProcessMemory(phandle, (LPVOID)Buffer,  &datas, 4, NULL);
    CloseHandle(phandle);
}