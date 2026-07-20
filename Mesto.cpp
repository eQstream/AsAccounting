// Mesto.cpp
#include "Mesto.h"
#include <string>

// Конструктор, соответствующий .h
Mesto::Mesto(int place_id, std::string first, std::string middle,
             std::string last, std::string phone, std::string addr,
             std::string pass, std::string model, std::string avto_num,
             int balance, bool isRetired, bool isDiscount)
    : id(place_id), first_name(first), middle_name(middle), last_name(last),
      phone_number(phone), address(addr), passport(pass), avto_model(model),
      avto_number(avto_num), spot_balance(balance), retired(isRetired),
      discount(isDiscount) {}

Mesto::~Mesto() {}

// Геттер просто возвращает значение
int Mesto::getId() const { return id; }
const std::string &Mesto::getFirstName() const { return first_name; }
const std::string &Mesto::getMiddleName() const { return middle_name; }
const std::string &Mesto::getLastName() const { return last_name; }
const std::string &Mesto::getPhoneNumber() const { return phone_number; }
const std::string &Mesto::getAddress() const { return address; }
const std::string &Mesto::getPassport() const { return passport; }
const std::string &Mesto::getAvtoModel() const { return avto_model; }
const std::string &Mesto::getAvtoNumber() const { return avto_number; }
int Mesto::getBaseMonthlyPayment() const { return (id <= 150) ? 1300 : 2000; }
int Mesto::getFinalPayment() const {
  return discount ? getBaseMonthlyPayment() * 0.8 : getBaseMonthlyPayment();
}
int Mesto::getBalance() const { return spot_balance; }
bool Mesto::getRetired() const { return retired; }
bool Mesto::getDiscount() const { return discount; }

// Сеттеры
void Mesto::setBalance(const int balance) { spot_balance = balance; }

void Mesto::setFirstName(const std::string &first) { first_name = first; }

void Mesto::setMiddleName(const std::string &middle) { middle_name = middle; }

void Mesto::setLastName(const std::string &last) { last_name = last; }

void Mesto::setPhone(const std::string &phone) { phone_number = phone; }

void Mesto::setAddress(const std::string &addr) { address = addr; }

void Mesto::setPassport(const std::string &pass) { passport = pass; }

void Mesto::setAvtoModel(const std::string &model) { avto_model = model; }

void Mesto::setAvtoNumber(const std::string &avto_num) {
  avto_number = avto_num;
}

void Mesto::setRetired(const bool isRetired) { retired = isRetired; }

void Mesto::setDiscount(bool isDiscount) { discount = isDiscount; }