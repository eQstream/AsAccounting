#pragma once
#include <QMainWindow>

class QTabWidget;

/// @brief Главное окно приложения с вкладками "Учёт" и "Бухгалтерия".
///
/// Содержит QTabWidget с двумя разделами.
/// В будущем разграничение прав доступа (админы — полный доступ,
/// пользователи — только просмотр) будет настраиваться через методы
/// этого класса.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Создаёт главное окно с заголовком "Гаражный учёт" и вкладками.
    /// @param parent Родительский виджет (по умолчанию nullptr)
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /// @brief Инициализирует интерфейс: создаёт QTabWidget и добавляет вкладки.
    void setupUi();

    QTabWidget *tabWidget; ///< Виджет вкладок

    /// @brief Создаёт содержимое вкладки "Учёт".
    /// @return Виджет с интерфейсом учёта машиномест
    QWidget *createAccountingTab();

    /// @brief Создаёт содержимое вкладки "Бухгалтерия".
    /// @return Виджет с интерфейсом бухгалтерского учёта
    QWidget *createBookkeepingTab();
};