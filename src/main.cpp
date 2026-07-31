// src/main.cpp
#include "application/SpotService.h"
#include "domain/Spot.h"
#include "infrastructure/SqliteSpotRepository.h"
#include "infrastructure/SqliteUserRepository.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <windows.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SetConsoleOutputCP(65001);

    SqliteSpotRepository spotRepo("asaccounting.db");
    SpotService spotService(spotRepo);

    MainWindow window(spotService);
    window.show();

    return app.exec();
}