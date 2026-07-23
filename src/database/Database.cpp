#include "database/Database.h"
#include "Mesto.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <optional>

// ============================================================================
// Конструктор / Деструктор
// ============================================================================

Database::Database(const QString &path) : db_path(path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
}

Database::~Database()
{
    close();
}

// ============================================================================
// Подключение / Отключение
// ============================================================================

bool Database::open()
{
    if (!db.open())
    {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    // WAL-режим — быстрее при конкурентном доступе
    execute("PRAGMA journal_mode=WAL");
    // Внешние ключи — на будущее, когда появятся связанные таблицы
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

// ============================================================================
// Выполнение SQL
// ============================================================================

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

// ============================================================================
// Создание таблиц
// ============================================================================

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

// ============================================================================
// CRUD: Добавление машиноместа
// ============================================================================

bool Database::addMesto(const Mesto &m)
{
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO mesto (
            id, last_name, first_name, middle_name, birth_date,
            registration_address, actual_address, phone1, phone2, phone3,
            mgsa_ticket_number, mgsa_ticket_issue_date,
            passport_series, passport_number, passport_issued_by, passport_issue_date,
            vehicle_brand, vehicle_plate, vehicle_year,
            pensioner, disabled, notes, spot_balance
        ) VALUES (
            :id, :last_name, :first_name, :middle_name, :birth_date,
            :registration_address, :actual_address, :phone1, :phone2, :phone3,
            :mgsa_ticket_number, :mgsa_ticket_issue_date,
            :passport_series, :passport_number, :passport_issued_by, :passport_issue_date,
            :vehicle_brand, :vehicle_plate, :vehicle_year,
            :pensioner, :disabled, :notes, :spot_balance
        )
    )");

    query.bindValue(":id", m.getPlace());
    query.bindValue(":last_name", QString::fromStdString(m.getLastName()));
    query.bindValue(":first_name", QString::fromStdString(m.getFirstName()));
    query.bindValue(":middle_name", QString::fromStdString(m.getMiddleName()));
    query.bindValue(":birth_date", QString::fromStdString(m.getBirthDate()));
    query.bindValue(":registration_address", QString::fromStdString(m.getRegistrationAddress()));
    query.bindValue(":actual_address", QString::fromStdString(m.getActualAddress()));
    query.bindValue(":phone1", QString::fromStdString(m.getPhone1()));
    query.bindValue(":phone2", QString::fromStdString(m.getPhone2()));
    query.bindValue(":phone3", QString::fromStdString(m.getPhone3()));
    query.bindValue(":mgsa_ticket_number", QString::fromStdString(m.getMgsaTicketNumber()));
    query.bindValue(":mgsa_ticket_issue_date", QString::fromStdString(m.getMgsaTicketIssueDate()));
    query.bindValue(":passport_series", QString::fromStdString(m.getPassportSeries()));
    query.bindValue(":passport_number", QString::fromStdString(m.getPassportNumber()));
    query.bindValue(":passport_issued_by", QString::fromStdString(m.getPassportIssuedBy()));
    query.bindValue(":passport_issue_date", QString::fromStdString(m.getPassportIssueDate()));
    query.bindValue(":vehicle_brand", QString::fromStdString(m.getVehicleBrand()));
    query.bindValue(":vehicle_plate", QString::fromStdString(m.getVehiclePlate()));
    query.bindValue(":vehicle_year", m.getVehicleYear());
    query.bindValue(":pensioner", m.isPensioner() ? 1 : 0);
    query.bindValue(":disabled", m.isDisabled() ? 1 : 0);
    query.bindValue(":notes", QString::fromStdString(m.getNotes()));
    query.bindValue(":spot_balance", m.getSpotBalance());

    if (!query.exec())
    {
        qWarning() << "addMesto error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================================
// CRUD: Обновление машиноместа
// ============================================================================

bool Database::updateMesto(const Mesto &m)
{
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE mesto SET
            last_name = :last_name,
            first_name = :first_name,
            middle_name = :middle_name,
            birth_date = :birth_date,
            registration_address = :registration_address,
            actual_address = :actual_address,
            phone1 = :phone1,
            phone2 = :phone2,
            phone3 = :phone3,
            mgsa_ticket_number = :mgsa_ticket_number,
            mgsa_ticket_issue_date = :mgsa_ticket_issue_date,
            passport_series = :passport_series,
            passport_number = :passport_number,
            passport_issued_by = :passport_issued_by,
            passport_issue_date = :passport_issue_date,
            vehicle_brand = :vehicle_brand,
            vehicle_plate = :vehicle_plate,
            vehicle_year = :vehicle_year,
            pensioner = :pensioner,
            disabled = :disabled,
            notes = :notes,
            spot_balance = :spot_balance
        WHERE id = :id
    )");

    query.bindValue(":id", m.getPlace());
    query.bindValue(":last_name", QString::fromStdString(m.getLastName()));
    query.bindValue(":first_name", QString::fromStdString(m.getFirstName()));
    query.bindValue(":middle_name", QString::fromStdString(m.getMiddleName()));
    query.bindValue(":birth_date", QString::fromStdString(m.getBirthDate()));
    query.bindValue(":registration_address", QString::fromStdString(m.getRegistrationAddress()));
    query.bindValue(":actual_address", QString::fromStdString(m.getActualAddress()));
    query.bindValue(":phone1", QString::fromStdString(m.getPhone1()));
    query.bindValue(":phone2", QString::fromStdString(m.getPhone2()));
    query.bindValue(":phone3", QString::fromStdString(m.getPhone3()));
    query.bindValue(":mgsa_ticket_number", QString::fromStdString(m.getMgsaTicketNumber()));
    query.bindValue(":mgsa_ticket_issue_date", QString::fromStdString(m.getMgsaTicketIssueDate()));
    query.bindValue(":passport_series", QString::fromStdString(m.getPassportSeries()));
    query.bindValue(":passport_number", QString::fromStdString(m.getPassportNumber()));
    query.bindValue(":passport_issued_by", QString::fromStdString(m.getPassportIssuedBy()));
    query.bindValue(":passport_issue_date", QString::fromStdString(m.getPassportIssueDate()));
    query.bindValue(":vehicle_brand", QString::fromStdString(m.getVehicleBrand()));
    query.bindValue(":vehicle_plate", QString::fromStdString(m.getVehiclePlate()));
    query.bindValue(":vehicle_year", m.getVehicleYear());
    query.bindValue(":pensioner", m.isPensioner() ? 1 : 0);
    query.bindValue(":disabled", m.isDisabled() ? 1 : 0);
    query.bindValue(":notes", QString::fromStdString(m.getNotes()));
    query.bindValue(":spot_balance", m.getSpotBalance());

    if (!query.exec())
    {
        qWarning() << "updateMesto error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================================
// CRUD: Удаление машиноместа
// ============================================================================

bool Database::deleteMesto(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM mesto WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
    {
        qWarning() << "deleteMesto error:" << query.lastError().text();
        return false;
    }
    return true;
}

// ============================================================================
// CRUD: Получение одного машиноместа по id
// ============================================================================

std::optional<Mesto> Database::getMestoById(int id)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM mesto WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next())
    {
        return std::nullopt; // Запись не найдена
    }

    return Mesto(
        query.value("id").toInt(), query.value("last_name").toString().toStdString(),
        query.value("first_name").toString().toStdString(), query.value("middle_name").toString().toStdString(),
        query.value("birth_date").toString().toStdString(),
        query.value("registration_address").toString().toStdString(),
        query.value("actual_address").toString().toStdString(), query.value("phone1").toString().toStdString(),
        query.value("phone2").toString().toStdString(), query.value("phone3").toString().toStdString(),
        query.value("mgsa_ticket_number").toString().toStdString(),
        query.value("mgsa_ticket_issue_date").toString().toStdString(),
        query.value("passport_series").toString().toStdString(),
        query.value("passport_number").toString().toStdString(),
        query.value("passport_issued_by").toString().toStdString(),
        query.value("passport_issue_date").toString().toStdString(),
        query.value("vehicle_brand").toString().toStdString(), query.value("vehicle_plate").toString().toStdString(),
        query.value("vehicle_year").toInt(), query.value("pensioner").toBool(), query.value("disabled").toBool(),
        query.value("notes").toString().toStdString(), query.value("spot_balance").toInt());
}

// ============================================================================
// CRUD: Получение всех машиномест
// ============================================================================

std::vector<Mesto> Database::getAllMesto()
{
    std::vector<Mesto> result;
    QSqlQuery query(db);

    if (!query.exec("SELECT * FROM mesto ORDER BY id"))
    {
        qWarning() << "getAllMesto error:" << query.lastError().text();
        return result; // Возвращаем пустой вектор при ошибке
    }

    while (query.next())
    {
        result.emplace_back(
            query.value("id").toInt(), query.value("last_name").toString().toStdString(),
            query.value("first_name").toString().toStdString(), query.value("middle_name").toString().toStdString(),
            query.value("birth_date").toString().toStdString(),
            query.value("registration_address").toString().toStdString(),
            query.value("actual_address").toString().toStdString(), query.value("phone1").toString().toStdString(),
            query.value("phone2").toString().toStdString(), query.value("phone3").toString().toStdString(),
            query.value("mgsa_ticket_number").toString().toStdString(),
            query.value("mgsa_ticket_issue_date").toString().toStdString(),
            query.value("passport_series").toString().toStdString(),
            query.value("passport_number").toString().toStdString(),
            query.value("passport_issued_by").toString().toStdString(),
            query.value("passport_issue_date").toString().toStdString(),
            query.value("vehicle_brand").toString().toStdString(),
            query.value("vehicle_plate").toString().toStdString(), query.value("vehicle_year").toInt(),
            query.value("pensioner").toBool(), query.value("disabled").toBool(),
            query.value("notes").toString().toStdString(), query.value("spot_balance").toInt());
    }

    return result;
}

// ============================================================================
// Доступ к сырому подключению (для прямых запросов)
// ============================================================================

QSqlDatabase &Database::getHandle()
{
    return db;
}