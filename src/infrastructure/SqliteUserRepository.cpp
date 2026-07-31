// src/infrastructure/SqliteUserRepository.cpp
#include "infrastructure/SqliteUserRepository.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>


SqliteUserRepository::SqliteUserRepository(QSqlDatabase &db) : db(db)
{
    initialize();
}

void SqliteUserRepository::initialize()
{
    QSqlQuery query(db);
    query.exec(R"(
        CREATE TABLE IF NOT EXISTS users (
            login           TEXT PRIMARY KEY,
            password_hash   TEXT NOT NULL,
            role            TEXT NOT NULL,
            change_password INTEGER NOT NULL DEFAULT 0
        )
    )");

    // Создаём пользователей по умолчанию, если таблица пуста
    query.exec("SELECT COUNT(*) FROM users");
    if (query.next() && query.value(0).toInt() == 0)
    {
        // Пароль 1234 с солью
        QSqlQuery insert(db);
        insert.prepare("INSERT INTO users (login, password_hash, role, change_password) "
                       "VALUES (:login, :hash, :role, :change)");

        auto addUser = [&](const QString &login, const QString &hash, const QString &role, int change)
        {
            insert.bindValue(":login", login);
            insert.bindValue(":hash", hash);
            insert.bindValue(":role", role);
            insert.bindValue(":change", change);
            insert.exec();
        };

        // SHA256("1234" + "MGSASalt2024")
        // TODO: вычислить реальный хеш, пока заглушка
        QString defaultHash = "PLACEHOLDER_SHA256_HASH";

        addUser("Мурашов", defaultHash, "Admin", 1);
        addUser("Амелина", defaultHash, "Admin", 1);
        addUser("Белов", defaultHash, "Observer", 1);
        addUser("Белова", defaultHash, "Observer", 1);
        addUser("Нефёдов", defaultHash, "Observer", 1);

        qDebug() << "Default users created.";
    }
}

std::optional<User> SqliteUserRepository::findByLogin(const std::string &login)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE login = :login");
    query.bindValue(":login", QString::fromStdString(login));

    if (!query.exec() || !query.next())
        return std::nullopt;

    Role role = (query.value("role").toString() == "Admin") ? Role::Admin : Role::Observer;

    return User(query.value("login").toString().toStdString(), query.value("password_hash").toString().toStdString(),
                role, query.value("change_password").toBool());
}

void SqliteUserRepository::save(const User &user)
{
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO users (login, password_hash, role, change_password)
        VALUES (:login, :hash, :role, :change)
        ON CONFLICT(login) DO UPDATE SET
            password_hash = excluded.password_hash,
            role = excluded.role,
            change_password = excluded.change_password
    )");

    query.bindValue(":login", QString::fromStdString(user.getLogin()));
    query.bindValue(":hash", QString::fromStdString(user.getPasswordHash()));
    query.bindValue(":role", (user.getRole() == Role::Admin) ? "Admin" : "Observer");
    query.bindValue(":change", user.mustChangePassword() ? 1 : 0);

    if (!query.exec())
        qWarning() << "User save error:" << query.lastError().text();
}