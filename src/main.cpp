// @file main.cpp
/// @brief Точка входа в приложение "Гаражный учёт" (AsAccounting).

#include "ui/MainWindow.h"
#include <QApplication>

#ifdef _WIN32
#include <windows.h>
#endif

/// @brief Инициализирует Qt-приложение, настраивает кодировку консоли
///        и запускает главное окно.
/// @param argc Количество аргументов командной строки
/// @param argv Массив аргументов командной строки
/// @return Код завершения приложения
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

#ifdef _WIN32
    // Установка UTF-8 для вывода в консоль Windows
    SetConsoleOutputCP(65001);
#endif

    MainWindow window;
    window.show();

    return app.exec();
}