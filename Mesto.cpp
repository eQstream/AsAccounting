#include "Mesto.h"

// ============================================================================
// Конструктор / Деструктор
// ============================================================================

Mesto::Mesto(int place_id, std::string first, std::string middle, std::string last, std::string phone, std::string addr,
             std::string pass, std::string model, std::string avto_num, int balance, bool isRetired, bool isDiscount)
    // Основные данные
    : place(place_id), last_name(last), first_name(first), middle_name(middle)
      // Документы
      ,
      birth_date(""), passport_series(pass), passport_number(""), passport_issued_by(""), passport_issue_date("")
      // Адреса
      ,
      registration_address(addr), actual_address("")
      // Телефоны
      ,
      phone1(phone), phone2(""), phone3("")
      // МГСА
      ,
      mgsa_ticket_number(""), mgsa_ticket_issue_date("")
      // Автомобиль
      ,
      vehicle_brand(model), vehicle_plate(avto_num), vehicle_year(0)
      // Статус
      ,
      pensioner(isRetired), disabled(isDiscount)
      // Баланс
      ,
      spot_balance(balance)
      // Прочее
      ,
      notes("")
{
}

Mesto::~Mesto() = default;

// ============================================================================
// Основные геттеры
// ============================================================================

int Mesto::getPlace() const
{
    return place;
}
const std::string &Mesto::getLastName() const
{
    return last_name;
}
const std::string &Mesto::getFirstName() const
{
    return first_name;
}
const std::string &Mesto::getMiddleName() const
{
    return middle_name;
}

// ============================================================================
// Документы
// ============================================================================

const std::string &Mesto::getBirthDate() const
{
    return birth_date;
}
const std::string &Mesto::getPassport() const
{
    return passport_series;
}
const std::string &Mesto::getPassportSeries() const
{
    return passport_series;
}
const std::string &Mesto::getPassportNumber() const
{
    return passport_number;
}
const std::string &Mesto::getPassportIssuedBy() const
{
    return passport_issued_by;
}
const std::string &Mesto::getPassportIssueDate() const
{
    return passport_issue_date;
}

// ============================================================================
// Адреса
// ============================================================================

const std::string &Mesto::getAddress() const
{
    return registration_address;
}
const std::string &Mesto::getRegistrationAddress() const
{
    return registration_address;
}
const std::string &Mesto::getActualAddress() const
{
    return actual_address;
}

// ============================================================================
// Телефоны
// ============================================================================

const std::string &Mesto::getPhoneNumber() const
{
    return phone1;
}
const std::string &Mesto::getPhone1() const
{
    return phone1;
}
const std::string &Mesto::getPhone2() const
{
    return phone2;
}
const std::string &Mesto::getPhone3() const
{
    return phone3;
}

// ============================================================================
// МГСА
// ============================================================================

const std::string &Mesto::getMgsaTicketNumber() const
{
    return mgsa_ticket_number;
}
const std::string &Mesto::getMgsaTicketIssueDate() const
{
    return mgsa_ticket_issue_date;
}

// ============================================================================
// Автомобиль
// ============================================================================

const std::string &Mesto::getAvtoModel() const
{
    return vehicle_brand;
}
const std::string &Mesto::getAvtoNumber() const
{
    return vehicle_plate;
}
const std::string &Mesto::getVehicleBrand() const
{
    return vehicle_brand;
}
const std::string &Mesto::getVehiclePlate() const
{
    return vehicle_plate;
}
int Mesto::getVehicleYear() const
{
    return vehicle_year;
}

// ============================================================================
// Статус
// ============================================================================

bool Mesto::getRetired() const
{
    return pensioner;
}
bool Mesto::getDiscount() const
{
    return disabled;
}
bool Mesto::isPensioner() const
{
    return pensioner;
}
bool Mesto::isDisabled() const
{
    return disabled;
}

// ============================================================================
// Баланс
// ============================================================================

int Mesto::getBalance() const
{
    return spot_balance;
}
int Mesto::getSpotBalance() const
{
    return spot_balance;
}

// ============================================================================
// Прочее
// ============================================================================

const std::string &Mesto::getNotes() const
{
    return notes;
}

// ============================================================================
// Расчет оплаты
// ============================================================================

int Mesto::getBaseMonthlyPayment() const
{
    return 1500;
}

int Mesto::getFinalPayment() const
{
    int payment = getBaseMonthlyPayment();

    if (pensioner)
    {
        payment = static_cast<int>(payment * 0.7);
    }

    if (disabled)
    {
        payment = static_cast<int>(payment * 0.5);
    }

    return payment;
}

// ============================================================================
// Основные сеттеры
// ============================================================================

void Mesto::setLastName(const std::string &value)
{
    last_name = value;
}
void Mesto::setFirstName(const std::string &value)
{
    first_name = value;
}
void Mesto::setMiddleName(const std::string &value)
{
    middle_name = value;
}

// ============================================================================
// Документы (сеттеры)
// ============================================================================

void Mesto::setBirthDate(const std::string &value)
{
    birth_date = value;
}
void Mesto::setPassport(const std::string &value)
{
    passport_series = value;
}
void Mesto::setPassportSeries(const std::string &value)
{
    passport_series = value;
}
void Mesto::setPassportNumber(const std::string &value)
{
    passport_number = value;
}
void Mesto::setPassportIssuedBy(const std::string &value)
{
    passport_issued_by = value;
}
void Mesto::setPassportIssueDate(const std::string &value)
{
    passport_issue_date = value;
}

// ============================================================================
// Адреса (сеттеры)
// ============================================================================

void Mesto::setAddress(const std::string &value)
{
    registration_address = value;
}
void Mesto::setRegistrationAddress(const std::string &value)
{
    registration_address = value;
}
void Mesto::setActualAddress(const std::string &value)
{
    actual_address = value;
}

// ============================================================================
// Телефоны (сеттеры)
// ============================================================================

void Mesto::setPhone(const std::string &value)
{
    phone1 = value;
}
void Mesto::setPhone1(const std::string &value)
{
    phone1 = value;
}
void Mesto::setPhone2(const std::string &value)
{
    phone2 = value;
}
void Mesto::setPhone3(const std::string &value)
{
    phone3 = value;
}

// ============================================================================
// МГСА (сеттеры)
// ============================================================================

void Mesto::setMgsaTicketNumber(const std::string &value)
{
    mgsa_ticket_number = value;
}
void Mesto::setMgsaTicketIssueDate(const std::string &value)
{
    mgsa_ticket_issue_date = value;
}

// ============================================================================
// Автомобиль (сеттеры)
// ============================================================================

void Mesto::setAvtoModel(const std::string &value)
{
    vehicle_brand = value;
}
void Mesto::setAvtoNumber(const std::string &value)
{
    vehicle_plate = value;
}
void Mesto::setVehicleBrand(const std::string &value)
{
    vehicle_brand = value;
}
void Mesto::setVehiclePlate(const std::string &value)
{
    vehicle_plate = value;
}
void Mesto::setVehicleYear(int value)
{
    vehicle_year = value;
}

// ============================================================================
// Статус (сеттеры)
// ============================================================================

void Mesto::setRetired(bool value)
{
    pensioner = value;
}
void Mesto::setDiscount(bool value)
{
    disabled = value;
}
void Mesto::setPensioner(bool value)
{
    pensioner = value;
}
void Mesto::setDisabled(bool value)
{
    disabled = value;
}

// ============================================================================
// Баланс (сеттеры)
// ============================================================================

void Mesto::setBalance(int value)
{
    spot_balance = value;
}
void Mesto::setSpotBalance(int value)
{
    spot_balance = value;
}

// ============================================================================
// Прочее (сеттеры)
// ============================================================================

void Mesto::setNotes(const std::string &value)
{
    notes = value;
}