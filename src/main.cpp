// src/main.cpp
#include "application/SpotService.h"
#include "domain/AuthService.h"
#include "domain/Spot.h"
#include "infrastructure/SqliteSpotRepository.h"
#include "infrastructure/SqliteUserRepository.h"
#include "ui/LoginDialog.h"
#include "ui/MainWindow.h"
#include <QApplication>
#include <windows.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SetConsoleOutputCP(65001);

    SqliteSpotRepository spotRepo("asaccounting.db");
    SpotService spotService(spotRepo);

    SqliteUserRepository userRepo(spotRepo.getDatabase());
    AuthService authService(userRepo);

    LoginDialog loginDialog(authService);
    if (loginDialog.exec() != QDialog::Accepted)
        return 0;

    std::optional<Role> role = loginDialog.loggedInRole();

    MainWindow window(spotService, authService, role.value_or(Role::Observer), loginDialog.getLogin());
    window.show();

    return app.exec();
}