// Database.cpp
#include "Database.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>


Database::Database(const QString &path) : db_path(path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

Database::~Database()
{
    close();
}

bool Database::open()
{
    if (!db.open())
    {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    execute("PRAGMA journal_mode=WAL");
    execute("PRAGMA foreign_keys=ON");

    qDebug() << "Database opened successfully!";
    return true;
}

void Database::close()
{
    if (db.isOpen())
    {
        db.close();
        qDebug() << "Database closed.";
    }
}

bool Database::execute(const QString &sql)
{
    QSqlQuery query(db);
    if (!query.exec(sql))
    {
        qWarning() << "SQL error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Database::createTables()
{
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS mesto (
            id INTEGER PRIMARY KEY,
            first_name TEXT NOT NULL,
            middle_name TEXT DEFAULT '',
            last_name TEXT NOT NULL,
            phone_number TEXT DEFAULT '',
            address TEXT DEFAULT '',
            passport TEXT DEFAULT '',
            avto_model TEXT DEFAULT '',
            avto_number TEXT DEFAULT '',
            spot_balance INTEGER DEFAULT 0,
            retired INTEGER DEFAULT 0,
            discount INTEGER DEFAULT 0
        )
    )";

    return execute(sql);
}

QSqlDatabase &Database::getHandle()
{
    return db;
}