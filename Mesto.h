#pragma once
#include <string>

class Mesto
{
private:
    int place;               // Номер места
    std::string last_name;   // Фамилия
    std::string first_name;  // Имя
    std::string middle_name; // Отчество
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
    std::string notes;
    int spot_balance;

public:
    // Конструктор / Деструктор
    Mesto(int place_id, std::string first = "", std::string middle = "", std::string last = "", std::string phone = "",
          std::string addr = "", std::string pass = "", std::string model = "", std::string avto_num = "",
          int balance = 0, bool isRetired = false, bool isDiscount = false);
    ~Mesto();

    // Основные данные
    int getPlace() const;

    // ФИО
    const std::string &getLastName() const;
    const std::string &getFirstName() const;
    const std::string &getMiddleName() const;

    // Дата рождения
    const std::string &getBirthDate() const;

    // Адреса
    const std::string &getRegistrationAddress() const;
    const std::string &getActualAddress() const;

    // Телефоны
    const std::string &getPhone1() const;
    const std::string &getPhone2() const;
    const std::string &getPhone3() const;

    // МГСА
    const std::string &getMgsaTicketNumber() const;
    const std::string &getMgsaTicketIssueDate() const;

    // Паспорт
    const std::string &getPassportSeries() const;
    const std::string &getPassportNumber() const;
    const std::string &getPassportIssuedBy() const;
    const std::string &getPassportIssueDate() const;

    // Автомобиль
    const std::string &getVehicleBrand() const;
    const std::string &getVehiclePlate() const;
    int getVehicleYear() const;

    // Статус
    bool isPensioner() const;
    bool isDisabled() const;

    // Баланс
    int getSpotBalance() const;

    // Прочее
    const std::string &getNotes() const;

    // Расчёт оплаты
    int getBaseMonthlyPayment() const;
    int getFinalPayment() const;

    // ========================================================================
    // Сеттеры
    // ========================================================================

    // ФИО
    void setLastName(const std::string &value);
    void setFirstName(const std::string &value);
    void setMiddleName(const std::string &value);

    // Дата рождения
    void setBirthDate(const std::string &value);

    // Адреса
    void setRegistrationAddress(const std::string &value);
    void setActualAddress(const std::string &value);

    // Телефоны
    void setPhone1(const std::string &value);
    void setPhone2(const std::string &value);
    void setPhone3(const std::string &value);

    // МГСА
    void setMgsaTicketNumber(const std::string &value);
    void setMgsaTicketIssueDate(const std::string &value);

    // Паспорт
    void setPassportSeries(const std::string &value);
    void setPassportNumber(const std::string &value);
    void setPassportIssuedBy(const std::string &value);
    void setPassportIssueDate(const std::string &value);

    // Автомобиль
    void setVehicleBrand(const std::string &value);
    void setVehiclePlate(const std::string &value);
    void setVehicleYear(int value);

    // Статус
    void setPensioner(bool value);
    void setDisabled(bool value);

    // Баланс
    void setSpotBalance(int value);

    // Прочее
    void setNotes(const std::string &value);
};