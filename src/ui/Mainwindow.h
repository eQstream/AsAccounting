#pragma once
#include <QMainWindow>
#include <QStringList>

class QTabWidget;
class QTableWidget;
class QPushButton;
class QLineEdit;
class QMenu;
class Database;

/// @brief Главное окно приложения с вкладками "Учёт" и "Бухгалтерия".
///
/// Вкладка "Учёт" содержит таблицу машиномест, кнопки управления,
/// поиск по таблице и контекстное меню.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// @brief Открывает диалог добавления нового машиноместа.
    void onAddMesto();

    /// @brief Открывает диалог редактирования выбранного машиноместа.
    void onEditMesto();

    /// @brief Удаляет выбранное машиноместо после подтверждения.
    void onDeleteMesto();

    /// @brief Открывает диалог импорта данных из CSV-файла.
    void onImportCsv();

    /// @brief Обрабатывает двойной клик по строке таблицы — открывает карточку места.
    void onTableDoubleClicked(int row, int column);

    /// @brief Фильтрует таблицу при изменении текста поиска.
    void onSearchTextChanged(const QString &text);

    /// @brief Показывает контекстное меню по правому клику.
    void onTableContextMenu(const QPoint &pos);

private:
    void setupUi();
    void refreshTable();

    /// @brief Применяет фильтр поиска к видимости строк таблицы.
    void applyFilter();

    QWidget *createAccountingTab();
    QWidget *createBookkeepingTab();

    static QStringList parseCsvLine(const QString &line);

    QTabWidget *tabWidget;
    QTableWidget *mestoTable;
    QLineEdit *searchEdit;
    QPushButton *btnAdd;
    QPushButton *btnEdit;
    QPushButton *btnDelete;
    QPushButton *btnImportCsv;
    QMenu *contextMenu;

    Database *db;
};