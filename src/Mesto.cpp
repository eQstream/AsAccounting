#include "Mesto.h"

// ============================================================================
// Полный конструктор
// ============================================================================

Mesto::Mesto(int place, std::string last_name, std::string first_name, std::string middle_name, std::string birth_date,
             std::string registration_address, std::string actual_address, std::string phone1, std::string phone2,
             std::string phone3, std::string mgsa_ticket_number, std::string mgsa_ticket_issue_date,
             std::string passport_series, std::string passport_number, std::string passport_issued_by,
             std::string passport_issue_date, std::string vehicle_brand, std::string vehicle_plate, int vehicle_year,
             bool pensioner, bool disabled, std::string notes, int spot_balance)
    : place(place), last_name(std::move(last_name)), first_name(std::move(first_name)),
      middle_name(std::move(middle_name)), birth_date(std::move(birth_date)),
      registration_address(std::move(registration_address)), actual_address(std::move(actual_address)),
      phone1(std::move(phone1)), phone2(std::move(phone2)), phone3(std::move(phone3)),
      mgsa_ticket_number(std::move(mgsa_ticket_number)), mgsa_ticket_issue_date(std::move(mgsa_ticket_issue_date)),
      passport_series(std::move(passport_series)), passport_number(std::move(passport_number)),
      passport_issued_by(std::move(passport_issued_by)), passport_issue_date(std::move(passport_issue_date)),
      vehicle_brand(std::move(vehicle_brand)), vehicle_plate(std::move(vehicle_plate)), vehicle_year(vehicle_year),
      pensioner(pensioner), disabled(disabled), notes(std::move(notes)), spot_balance(spot_balance)
{
}

// ============================================================================
// Краткий конструктор — все поля по умолчанию, кроме места и ФИО
// ============================================================================

Mesto::Mesto(int place, std::string last_name, std::string first_name, std::string middle_name)
    : place(place), last_name(std::move(last_name)), first_name(std::move(first_name)),
      middle_name(std::move(middle_name)), birth_date(""), registration_address(""), actual_address(""), phone1(""),
      phone2(""), phone3(""), mgsa_ticket_number(""), mgsa_ticket_issue_date(""), passport_series(""),
      passport_number(""), passport_issued_by(""), passport_issue_date(""), vehicle_brand(""), vehicle_plate(""),
      vehicle_year(0), pensioner(false), disabled(false), notes(""), spot_balance(0)
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
const std::string &Mesto::getMgsaTicketNumber() const
{
    return mgsa_ticket_number;
}
const std::string &Mesto::getMgsaTicketIssueDate() const
{
    return mgsa_ticket_issue_date;
}

// ============================================================================
// Адреса
// ============================================================================

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
// Автомобиль
// ============================================================================

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

bool Mesto::isPensioner() const
{
    return pensioner;
}
bool Mesto::isDisabled() const
{
    return disabled;
}

// ============================================================================
// Баланс и заметки
// ============================================================================

int Mesto::getSpotBalance() const
{
    return spot_balance;
}
const std::string &Mesto::getNotes() const
{
    return notes;
}

// ============================================================================
// Бизнес-логика оплаты
// ============================================================================

int Mesto::getBaseMonthlyPayment() const
{
    return 1300; // Фиксированная ставка
}

int Mesto::getFinalPayment() const
{
    int payment = getBaseMonthlyPayment();

    // Скидка 20% для инвалидов
    if (disabled)
    {
        payment = static_cast<int>(payment * 0.8);
    }

    return payment;
}

// ============================================================================
// Сеттеры — ФИО
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
// Сеттеры — Документы
// ============================================================================

void Mesto::setBirthDate(const std::string &value)
{
    birth_date = value;
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
void Mesto::setMgsaTicketNumber(const std::string &value)
{
    mgsa_ticket_number = value;
}
void Mesto::setMgsaTicketIssueDate(const std::string &value)
{
    mgsa_ticket_issue_date = value;
}

// ============================================================================
// Сеттеры — Адреса
// ============================================================================

void Mesto::setRegistrationAddress(const std::string &value)
{
    registration_address = value;
}
void Mesto::setActualAddress(const std::string &value)
{
    actual_address = value;
}

// ============================================================================
// Сеттеры — Телефоны
// ============================================================================

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
// Сеттеры — Автомобиль
// ============================================================================

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
// Сеттеры — Статус
// ============================================================================

void Mesto::setPensioner(bool value)
{
    pensioner = value;
}
void Mesto::setDisabled(bool value)
{
    disabled = value;
}

// ============================================================================
// Сеттеры — Баланс и заметки
// ============================================================================

void Mesto::setSpotBalance(int value)
{
    spot_balance = value;
}
void Mesto::setNotes(const std::string &value)
{
    notes = value;
}