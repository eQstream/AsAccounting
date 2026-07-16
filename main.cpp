// main.cpp
#include "Mesto.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    int id;
    std::cout << "Введите номер места: " << std::endl;
    std::cin >> id;
    Mesto Spot(id);
    std::cout << "Номер места: " << Spot.getId() << std::endl;
    return 0;
}