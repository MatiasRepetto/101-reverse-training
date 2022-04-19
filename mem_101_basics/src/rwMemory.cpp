#include "../include/rwMemory.h"


void readPointerData(LPVOID BaseAddr, std::vector<DWORD> listOffs, LPCWSTR baseWnd){
    float val;
	int Buffer;
	// Process Handle
	HWND hwnd = FindWindow(NULL, baseWnd);
    HANDLE phandle;
    DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
    phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); // Gain full Access on the process, Note: Needs full administrative rights, on both the injector and target .exe ,Abriendo un handle cada que se llama a la funcion, esto no es lo mas optimo. 
	//Reading Basepointer
	ReadProcessMemory(phandle, BaseAddr, &Buffer, 4, NULL); // Store the Basepointer into Buffer
	for (int i=0; i < listOffs.size()-1; i++){
		ReadProcessMemory(phandle, LPVOID(Buffer + listOffs.at(i)), &val, 4, NULL); // Read back the pointer and store into val
		printf("%f", val);
	}
    CloseHandle(phandle);
}

void writePointerData(LPVOID BaseAddr, std::vector<DWORD> listOffs, BYTE data[], LPCWSTR baseWnd){
    int Buffer;
	HWND hwnd = FindWindow(NULL, baseWnd);
    HANDLE phandle;
    DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
    phandle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid); // Abriendo un handle cada que se llama a la funcion, esto no es lo mas optimo
	ReadProcessMemory(phandle, BaseAddr, &Buffer, 4, NULL);
	DWORD dataSize = sizeof(data); 
	BYTE datas[sizeof(data)];
	memcpy(datas, data, sizeof(data));
	for (int i=0; i < listOffs.size()-1; i++){
		WriteProcessMemory(phandle, LPVOID(Buffer + listOffs.at(i)),  &datas, 4, NULL);
	}
    CloseHandle(phandle);
}