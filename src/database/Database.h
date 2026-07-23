#pragma once
#include <QSqlDatabase>
#include <QString>
#include <optional>
#include <vector>


class Mesto;

/// @brief Слой работы с базой данных SQLite через Qt6 QSqlDatabase.
///
/// Обеспечивает подключение к БД, создание таблиц и CRUD-операции
/// над машиноместами. Использует драйвер QSQLITE.
/// Все SQL-запросы параметризованы для защиты от инъекций.
class Database
{
private:
    QSqlDatabase db; ///< Подключение к БД
    QString db_path; ///< Путь к файлу БД

public:
    /// @brief Создаёт объект БД и настраивает подключение QSQLITE.
    /// @param path Путь к файлу базы данных
    explicit Database(const QString &path);
    ~Database();

    /// @brief Открывает соединение, включает WAL-режим и внешние ключи.
    /// @return true при успешном открытии
    bool open();

    /// @brief Закрывает соединение с БД.
    void close();

    /// @brief Выполняет произвольный SQL-запрос (INSERT/UPDATE/DELETE/DDL).
    /// @param sql SQL-строка
    /// @return true при успешном выполнении
    bool execute(const QString &sql);

    /// @brief Создаёт таблицу `mesto`, если она не существует.
    ///
    /// Схема включает все поля из CSV-импорта плюс баланс места.
    /// @return true при успешном создании
    bool createTables();

    // ========================================================================
    // CRUD для машиномест
    // ========================================================================

    /// @brief Добавляет новое машиноместо в БД.
    /// @param m Объект Mesto со всеми заполненными полями
    /// @return true при успешной вставке
    bool addMesto(const Mesto &m);

    /// @brief Обновляет все поля существующего машиноместа по его id.
    /// @param m Объект Mesto с обновлёнными данными (id должен совпадать)
    /// @return true при успешном обновлении
    bool updateMesto(const Mesto &m);

    /// @brief Удаляет машиноместо по id.
    /// @param id Номер места для удаления
    /// @return true при успешном удалении
    bool deleteMesto(int id);

    /// @brief Получает одно машиноместо по id.
    /// @param id Номер места
    /// @return Mesto если найдено, иначе std::nullopt
    std::optional<Mesto> getMestoById(int id);

    /// @brief Получает все машиноместа, отсортированные по id.
    /// @return Вектор объектов Mesto (может быть пустым)
    std::vector<Mesto> getAllMesto();

    /// @brief Возвращает ссылку на QSqlDatabase для прямых запросов.
    /// @return Ссылка на объект подключения
    QSqlDatabase &getHandle();
};