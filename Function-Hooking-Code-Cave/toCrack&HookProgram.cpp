#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>

int main(){
    std::string allow = std::to_string(rand());
    std::string password;

    std::cout << "Increse su password " << std::endl;
    std::cin >> password;
    if(password == allow){ // no way to hit the pass crack it !
        std::cout << "Ingresado correctamente" << std::endl;
    }else{
        std::cout << "Error contraseña incorrecta" << std::endl;
    }
}