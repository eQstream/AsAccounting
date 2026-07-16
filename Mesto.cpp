// Mesto.cpp
#include "Mesto.h"

// Конструктор, соответствующий .h
Mesto::Mesto(int place_id, std::string first, std::string middle, std::string last, std::string phone, std::string addr, std::string pass, std::string model, std::string avto_num, bool isRetired, bool isDiscount)
    : id(place_id),
      first_name(first),
      middle_name(middle),
      last_name(last),
      phone_number(phone),
      address(addr),
      passport(pass),
      avto_model(model),
      avto_number(avto_num),
      retired(isRetired),
      discount(isDiscount)
{
}

Mesto::~Mesto() {}

// Геттер просто возвращает значение
int Mesto::getId() const
{
    return id; // Просто возвращаем поле
}

int Mesto::getBaseMonthlyPayment() const
{
    return (id <= 150) ? 1300 : 2000;
}

int Mesto::getFinalPayment() const
{
    return discount ? getBaseMonthlyPayment() * 0.8 : getBaseMonthlyPayment();
}

// Сеттеры
void Mesto::setFirstName(const std::string &first)
{
    first_name = first;
}

void Mesto::setMiddleName(const std::string &middle)
{
    middle_name = middle;
}

void Mesto::setLastName(const std::string &last)
{
    last_name = last;
}

void Mesto::setPhone(const std::string &phone)
{
    phone_number = phone;
}

void Mesto::setAddress(const std::string &addr)
{
    address = addr;
}

void Mesto::setDiscount(bool isDiscount)
{
    discount = isDiscount;
}