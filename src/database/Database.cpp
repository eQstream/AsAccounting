// Database.cpp
#include "database/Database.h"
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
            id                      INTEGER PRIMARY KEY,
            last_name               TEXT NOT NULL,
            first_name              TEXT NOT NULL,
            middle_name             TEXT DEFAULT '',
            birth_date              TEXT DEFAULT '',
            registration_address    TEXT DEFAULT '',
            actual_address          TEXT DEFAULT '',
            phone1                  TEXT DEFAULT '',
            phone2                  TEXT DEFAULT '',
            phone3                  TEXT DEFAULT '',
            mgsa_ticket_number      TEXT DEFAULT '',
            mgsa_ticket_issue_date  TEXT DEFAULT '',
            passport_series         TEXT DEFAULT '',
            passport_number         TEXT DEFAULT '',
            passport_issued_by      TEXT DEFAULT '',
            passport_issue_date     TEXT DEFAULT '',
            vehicle_brand           TEXT DEFAULT '',
            vehicle_plate           TEXT DEFAULT '',
            vehicle_year            INTEGER DEFAULT 0,
            pensioner               INTEGER DEFAULT 0,
            disabled                INTEGER DEFAULT 0,
            notes                   TEXT DEFAULT '',
            spot_balance            INTEGER DEFAULT 0
        )
    )";

    return execute(sql);
}

QSqlDatabase &Database::getHandle()
{
    return db;
}