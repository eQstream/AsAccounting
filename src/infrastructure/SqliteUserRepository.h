// src/infrastructure/SqliteUserRepository.h
#pragma once
#include "domain/UserRepository.h"
#include <QSqlDatabase>
#include <QString>

/// @brief Реализация UserRepository на SQLite через Qt6.
class SqliteUserRepository : public UserRepository
{
public:
    /// @brief Создаёт репозиторий. БД должна быть уже открыта.
    /// @param db Существующее подключение к БД
    explicit SqliteUserRepository(QSqlDatabase &db);
    ~SqliteUserRepository() override = default;

    std::optional<User> findByLogin(const std::string &login) override;
    void save(const User &user) override;

private:
    /// @brief Создаёт таблицу users, если её нет.
    void initialize();

    QSqlDatabase &db;
};