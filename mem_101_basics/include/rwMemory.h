#ifndef RW_MEMORY
#define RW_MEMORY


float readPointerData(LPVOID baseAddr, int offs, LPCWSTR baseWnd);
void writePointerData(LPVOID BaseAddr, int Offs, BYTE data[], LPCWSTR baseWnd);


#endif