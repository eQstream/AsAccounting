#include "domain/Owner.h"
#include <utility>

Owner::Owner(std::string last_name, std::string first_name, std::string middle_name, std::string birth_date,
             std::string registration_address, std::string actual_address, std::string phone1, std::string phone2,
             std::string phone3, std::string mgsa_ticket_number, std::string mgsa_ticket_issue_date,
             std::string passport_series, std::string passport_number, std::string passport_issued_by,
             std::string passport_issue_date, std::string vehicle_brand, std::string vehicle_plate, int vehicle_year,
             bool pensioner, bool disabled)
    : last_name(std::move(last_name)), first_name(std::move(first_name)), middle_name(std::move(middle_name)),
      birth_date(std::move(birth_date)), registration_address(std::move(registration_address)),
      actual_address(std::move(actual_address)), phone1(std::move(phone1)), phone2(std::move(phone2)),
      phone3(std::move(phone3)), mgsa_ticket_number(std::move(mgsa_ticket_number)),
      mgsa_ticket_issue_date(std::move(mgsa_ticket_issue_date)), passport_series(std::move(passport_series)),
      passport_number(std::move(passport_number)), passport_issued_by(std::move(passport_issued_by)),
      passport_issue_date(std::move(passport_issue_date)), vehicle_brand(std::move(vehicle_brand)),
      vehicle_plate(std::move(vehicle_plate)), vehicle_year(vehicle_year), pensioner(pensioner), disabled(disabled)
{
}

Owner::Owner(std::string last_name, std::string first_name, std::string middle_name)
    : last_name(std::move(last_name)), first_name(std::move(first_name)), middle_name(std::move(middle_name)),
      birth_date(""), registration_address(""), actual_address(""), phone1(""), phone2(""), phone3(""),
      mgsa_ticket_number(""), mgsa_ticket_issue_date(""), passport_series(""), passport_number(""),
      passport_issued_by(""), passport_issue_date(""), vehicle_brand(""), vehicle_plate(""), vehicle_year(0),
      pensioner(false), disabled(false)
{
}

const std::string &Owner::getLastName() const
{
    return last_name;
}
const std::string &Owner::getFirstName() const
{
    return first_name;
}
const std::string &Owner::getMiddleName() const
{
    return middle_name;
}
const std::string &Owner::getBirthDate() const
{
    return birth_date;
}
const std::string &Owner::getRegistrationAddress() const
{
    return registration_address;
}
const std::string &Owner::getActualAddress() const
{
    return actual_address;
}
const std::string &Owner::getPhone1() const
{
    return phone1;
}
const std::string &Owner::getPhone2() const
{
    return phone2;
}
const std::string &Owner::getPhone3() const
{
    return phone3;
}
const std::string &Owner::getMgsaTicketNumber() const
{
    return mgsa_ticket_number;
}
const std::string &Owner::getMgsaTicketIssueDate() const
{
    return mgsa_ticket_issue_date;
}
const std::string &Owner::getPassportSeries() const
{
    return passport_series;
}
const std::string &Owner::getPassportNumber() const
{
    return passport_number;
}
const std::string &Owner::getPassportIssuedBy() const
{
    return passport_issued_by;
}
const std::string &Owner::getPassportIssueDate() const
{
    return passport_issue_date;
}
const std::string &Owner::getVehicleBrand() const
{
    return vehicle_brand;
}
const std::string &Owner::getVehiclePlate() const
{
    return vehicle_plate;
}
int Owner::getVehicleYear() const
{
    return vehicle_year;
}
bool Owner::isPensioner() const
{
    return pensioner;
}
bool Owner::isDisabled() const
{
    return disabled;
}

double Owner::getDiscountMultiplier() const
{
    return disabled ? 0.8 : 1.0;
}