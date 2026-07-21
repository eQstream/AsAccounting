// Database.h
#pragma once
#include <QSqlDatabase>
#include <QString>

class Database
{
private:
    QSqlDatabase db;
    QString db_path;

public:
    Database(const QString &path);
    ~Database();

    bool open();
    void close();
    bool execute(const QString &sql);
    bool createTables();
    QSqlDatabase &getHandle();
};