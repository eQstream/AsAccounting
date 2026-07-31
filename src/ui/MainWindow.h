// src/ui/MainWindow.h
#pragma once
#include "domain/User.h"
#include <QMainWindow>
#include <QStringList>


class QTabWidget;
class QTableWidget;
class QPushButton;
class QLineEdit;
class QMenu;
class SpotService;
class AuthService;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SpotService &spotService, AuthService &authService, Role role, const QString &login,
                        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddSpot();
    void onEditSpot();
    void onDeleteSpot();
    void onImportCsv();
    void onChangePassword();
    void onTableDoubleClicked(int row, int column);
    void onSearchTextChanged(const QString &text);
    void onTableContextMenu(const QPoint &pos);

private:
    void setupUi();
    void refreshTable();
    void applyFilter();

    QWidget *createAccountingTab();
    QWidget *createBookkeepingTab();

    static QStringList parseCsvLine(const QString &line);

    SpotService &spotService;
    AuthService &authService;
    Role userRole;
    QString userLogin;

    QTabWidget *tabWidget;
    QTableWidget *spotTable;
    QLineEdit *searchEdit;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnImportCsv;
    QPushButton *btnChangePassword;
    QMenu *contextMenu;
};