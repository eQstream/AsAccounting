#pragma once
#include <string>

/// @brief Value object — владелец машиноместа.
///
/// Содержит все данные о владельце: ФИО, паспорт, адреса, контакты,
/// автомобиль, членский билет МГСА и статус льгот.
/// Является неотъемлемой частью агрегата Spot.
/// При смене владельца заменяется целиком.
class Owner
{
public:
    Owner(std::string last_name, std::string first_name, std::string middle_name, std::string birth_date,
          std::string registration_address, std::string actual_address, std::string phone1, std::string phone2,
          std::string phone3, std::string mgsa_ticket_number, std::string mgsa_ticket_issue_date,
          std::string passport_series, std::string passport_number, std::string passport_issued_by,
          std::string passport_issue_date, std::string vehicle_brand, std::string vehicle_plate, int vehicle_year,
          bool pensioner, bool disabled);

    Owner(std::string last_name = "", std::string first_name = "", std::string middle_name = "");

    const std::string &getLastName() const;
    const std::string &getFirstName() const;
    const std::string &getMiddleName() const;
    const std::string &getBirthDate() const;
    const std::string &getRegistrationAddress() const;
    const std::string &getActualAddress() const;
    const std::string &getPhone1() const;
    const std::string &getPhone2() const;
    const std::string &getPhone3() const;
    const std::string &getMgsaTicketNumber() const;
    const std::string &getMgsaTicketIssueDate() const;
    const std::string &getPassportSeries() const;
    const std::string &getPassportNumber() const;
    const std::string &getPassportIssuedBy() const;
    const std::string &getPassportIssueDate() const;
    const std::string &getVehicleBrand() const;
    const std::string &getVehiclePlate() const;
    int getVehicleYear() const;
    bool isPensioner() const;
    bool isDisabled() const;

    /// @return Множитель льготы: 0.8 для инвалидов, 1.0 для остальных.
    double getDiscountMultiplier() const;

private:
    std::string last_name;
    std::string first_name;
    std::string middle_name;
    std::string birth_date;
    std::string registration_address;
    std::string actual_address;
    std::string phone1;
    std::string phone2;
    std::string phone3;
    std::string mgsa_ticket_number;
    std::string mgsa_ticket_issue_date;
    std::string passport_series;
    std::string passport_number;
    std::string passport_issued_by;
    std::string passport_issue_date;
    std::string vehicle_brand;
    std::string vehicle_plate;
    int vehicle_year;
    bool pensioner;
    bool disabled;
};