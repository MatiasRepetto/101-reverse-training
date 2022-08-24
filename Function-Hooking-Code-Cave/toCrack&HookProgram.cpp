#include <stdio.h>
#include <iostream>

int main(){
    std::string allow = "momo123";
    std::string password;

    std::cout << "Increse su password " << std::endl;
    std::cin >> password;
    if(password == allow){
        std::cout << "Ingresado correctamente" << std::endl;
    }else{
        std::cout << "Error contraseña incorrecta" << std::endl;
    }
}