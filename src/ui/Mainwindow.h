// src/ui/MainWindow.h
#pragma once
#include <QMainWindow>
#include <QStringList>

class QTabWidget;
class QTableWidget;
class QPushButton;
class QLineEdit;
class QMenu;
class SpotService;

/// @brief Главное окно приложения с вкладками "Учёт" и "Бухгалтерия".
///
/// Вкладка "Учёт" содержит таблицу машиномест, кнопки управления,
/// поиск по таблице и контекстное меню.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @param spotService Сервис для работы с местами
    /// @param parent Родительский виджет
    explicit MainWindow(SpotService &spotService, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddSpot();
    void onEditSpot();
    void onDeleteSpot();
    void onImportCsv();
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

    QTabWidget *tabWidget;
    QTableWidget *spotTable;
    QLineEdit *searchEdit;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnImportCsv;
    QMenu *contextMenu;
};