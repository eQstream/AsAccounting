// main.cpp
#include "Mesto.h"
#include "database/Database.h"
#include <QApplication>
#include <iostream>
#include <windows.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    Database db("asaccounting.db");
    if (!db.open())
    {
        std::cerr << "Failed to open database!" << std::endl;
        return 1;
    }

    if (!db.createTables())
    {
        std::cerr << "Failed to create tables!" << std::endl;
        return 1;
    }

    std::cout << "База данных готова к работе!" << std::endl;

    int place;
    std::cout << "Введите номер места: " << std::endl;
    std::cin >> place;
    Mesto Spot(place);
    std::cout << "Номер места: " << Spot.getPlace() << std::endl;
    app.quit();
    return 0;
}