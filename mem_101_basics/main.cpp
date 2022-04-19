#include "./include/rwMemory.h"

using namespace std;

int main(){
    std::vector<DWORD> listOffs;
    string exeNameS;
    string memAddrS;
    DWORD offst;
    BYTE data[4];
    int cantoffs;
    cout << "ingresa el nombre del ejecutable: " << endl;
    cin >> exeNameS;
    cout << "ingresa la direccion base de memoria: " << endl;
    cin >> memAddrS;
    cout << "ingrese la cantidad de offsets de la direccion: " << endl;
    cin >> cantoffs;
    for(int i=0; i <= cantoffs; i++){
        cout << "ingrese offset de la direccion: " << endl;
        cin >> offst;
        listOffs[i] = offst;
    }
    LPCWSTR exeName = (LPCWSTR)exeNameS.c_str();
    LPVOID memAddr = (LPVOID)memAddrS.c_str();
    readPointerData(memAddr, listOffs, exeName);
    writePointerData(memAddr, listOffs, data, exeName);
    return 0;
}