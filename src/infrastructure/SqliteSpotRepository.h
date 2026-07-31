// src/infrastructure/SqliteSpotRepository.h
#pragma once
#include "domain/SpotRepository.h"
#include <QSqlDatabase>
#include <QString>

/// @brief Реализация SpotRepository на SQLite через Qt6.
///
/// Инкапсулирует всю работу с БД: подключение, создание таблиц,
/// CRUD-операции над местами.
class SqliteSpotRepository : public SpotRepository
{
public:
    /// @brief Создаёт репозиторий и подключается к БД.
    /// @param dbPath Путь к файлу базы данных
    explicit SqliteSpotRepository(const QString &dbPath);
    ~SqliteSpotRepository() override;

    std::optional<Spot> findById(int id) override;
    std::vector<Spot> findAll() override;
    void save(const Spot &spot) override;
    void remove(int id) override;

private:
    /// @brief Открывает БД и создаёт таблицы, если их нет.
    void initialize();

    /// @brief Преобразует строку результата запроса в Spot.
    Spot spotFromQuery(class QSqlQuery &query);

    /// @brief Привязывает поля Spot к параметрам запроса.
    void bindSpotParams(class QSqlQuery &query, const Spot &spot);

    QSqlDatabase db;
};