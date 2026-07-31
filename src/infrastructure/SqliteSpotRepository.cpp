// src/infrastructure/SqliteSpotRepository.cpp
#include "infrastructure/SqliteSpotRepository.h"
#include "domain/Owner.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

// ============================================================================
// Конструктор / Деструктор
// ============================================================================

SqliteSpotRepository::SqliteSpotRepository(const QString &dbPath)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    initialize();
}

SqliteSpotRepository::~SqliteSpotRepository()
{
    if (db.isOpen())
        db.close();
}

// ============================================================================
// Инициализация БД
// ============================================================================

void SqliteSpotRepository::initialize()
{
    if (!db.open())
    {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    query.exec("PRAGMA journal_mode=WAL");
    query.exec("PRAGMA foreign_keys=ON");

    query.exec(R"(
        CREATE TABLE IF NOT EXISTS spots (
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
            notes                   TEXT DEFAULT ''
        )
    )");

    qDebug() << "Database initialized.";
}

// ============================================================================
// CRUD
// ============================================================================

std::optional<Spot> SqliteSpotRepository::findById(int id)
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM spots WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next())
        return std::nullopt;

    return spotFromQuery(query);
}

std::vector<Spot> SqliteSpotRepository::findAll()
{
    std::vector<Spot> result;
    QSqlQuery query(db);

    if (!query.exec("SELECT * FROM spots ORDER BY id"))
    {
        qWarning() << "findAll error:" << query.lastError().text();
        return result;
    }

    while (query.next())
        result.push_back(spotFromQuery(query));

    return result;
}

void SqliteSpotRepository::save(const Spot &spot)
{
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO spots (
            id, last_name, first_name, middle_name, birth_date,
            registration_address, actual_address, phone1, phone2, phone3,
            mgsa_ticket_number, mgsa_ticket_issue_date,
            passport_series, passport_number, passport_issued_by, passport_issue_date,
            vehicle_brand, vehicle_plate, vehicle_year,
            pensioner, disabled, notes
        ) VALUES (
            :id, :last_name, :first_name, :middle_name, :birth_date,
            :registration_address, :actual_address, :phone1, :phone2, :phone3,
            :mgsa_ticket_number, :mgsa_ticket_issue_date,
            :passport_series, :passport_number, :passport_issued_by, :passport_issue_date,
            :vehicle_brand, :vehicle_plate, :vehicle_year,
            :pensioner, :disabled, :notes
        )
        ON CONFLICT(id) DO UPDATE SET
            last_name = excluded.last_name,
            first_name = excluded.first_name,
            middle_name = excluded.middle_name,
            birth_date = excluded.birth_date,
            registration_address = excluded.registration_address,
            actual_address = excluded.actual_address,
            phone1 = excluded.phone1,
            phone2 = excluded.phone2,
            phone3 = excluded.phone3,
            mgsa_ticket_number = excluded.mgsa_ticket_number,
            mgsa_ticket_issue_date = excluded.mgsa_ticket_issue_date,
            passport_series = excluded.passport_series,
            passport_number = excluded.passport_number,
            passport_issued_by = excluded.passport_issued_by,
            passport_issue_date = excluded.passport_issue_date,
            vehicle_brand = excluded.vehicle_brand,
            vehicle_plate = excluded.vehicle_plate,
            vehicle_year = excluded.vehicle_year,
            pensioner = excluded.pensioner,
            disabled = excluded.disabled,
            notes = excluded.notes
    )");

    bindSpotParams(query, spot);

    if (!query.exec())
        qWarning() << "save error:" << query.lastError().text();
}

void SqliteSpotRepository::remove(int id)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM spots WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec())
        qWarning() << "remove error:" << query.lastError().text();
}

// ============================================================================
// Приватные методы
// ============================================================================

Spot SqliteSpotRepository::spotFromQuery(QSqlQuery &query)
{
    int id = query.value("id").toInt();

    Owner owner(query.value("last_name").toString().toStdString(), query.value("first_name").toString().toStdString(),
                query.value("middle_name").toString().toStdString(), query.value("birth_date").toString().toStdString(),
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
                query.value("pensioner").toBool(), query.value("disabled").toBool());

    return Spot(id, std::move(owner), query.value("notes").toString().toStdString());
}

void SqliteSpotRepository::bindSpotParams(QSqlQuery &query, const Spot &spot)
{
    const Owner &o = spot.getOwner();

    query.bindValue(":id", spot.getId());
    query.bindValue(":last_name", QString::fromStdString(o.getLastName()));
    query.bindValue(":first_name", QString::fromStdString(o.getFirstName()));
    query.bindValue(":middle_name", QString::fromStdString(o.getMiddleName()));
    query.bindValue(":birth_date", QString::fromStdString(o.getBirthDate()));
    query.bindValue(":registration_address", QString::fromStdString(o.getRegistrationAddress()));
    query.bindValue(":actual_address", QString::fromStdString(o.getActualAddress()));
    query.bindValue(":phone1", QString::fromStdString(o.getPhone1()));
    query.bindValue(":phone2", QString::fromStdString(o.getPhone2()));
    query.bindValue(":phone3", QString::fromStdString(o.getPhone3()));
    query.bindValue(":mgsa_ticket_number", QString::fromStdString(o.getMgsaTicketNumber()));
    query.bindValue(":mgsa_ticket_issue_date", QString::fromStdString(o.getMgsaTicketIssueDate()));
    query.bindValue(":passport_series", QString::fromStdString(o.getPassportSeries()));
    query.bindValue(":passport_number", QString::fromStdString(o.getPassportNumber()));
    query.bindValue(":passport_issued_by", QString::fromStdString(o.getPassportIssuedBy()));
    query.bindValue(":passport_issue_date", QString::fromStdString(o.getPassportIssueDate()));
    query.bindValue(":vehicle_brand", QString::fromStdString(o.getVehicleBrand()));
    query.bindValue(":vehicle_plate", QString::fromStdString(o.getVehiclePlate()));
    query.bindValue(":vehicle_year", o.getVehicleYear());
    query.bindValue(":pensioner", o.isPensioner() ? 1 : 0);
    query.bindValue(":disabled", o.isDisabled() ? 1 : 0);
    query.bindValue(":notes", QString::fromStdString(spot.getNotes()));
}