#include <iostream>
#include <string>
#include <cstdlib>
#include <windows.h>

int main(){
    std::string allow = std::to_string(rand());
    std::string password;

    std::cout << "Increse su password " << std::endl;
    std::cin >> password;
    if(password == allow){ // no way to hit the pass crack it !!
        std::cout << "Ingresado correctamente" << std::endl;
        Sleep(1500);
    }else{
        std::cout << "Error contraseña incorrecta" << std::endl;
        Sleep(1500);
    }
}