#pragma once
#include <string>

class Mesto
{
private:
    int id; // Нмер места
    std::string first_name;
    std::string middle_name;
    std::string last_name;
    std::string phone_number;
    std::string address;
    std::string passport;
    std::string avto_model;
    std::string avto_number;
    bool retired;
    bool discount; // имеет ли право на льготы

public:
    Mesto(int place_id,
          std::string first = "",
          std::string middle = "",
          std::string last = "",
          std::string phone = "",
          std::string addr = "",
          std::string pass = "",
          std::string model = "",
          std::string avto_num = "",
          bool isRetired = false,
          bool isDiscount = false);
    ~Mesto();
    int getId() const;
    int getBaseMonthlyPayment() const;
    int getFinalPayment() const;
    void setFirstName(const std::string &first);
    void setMiddleName(const std::string &middle);
    void setLastName(const std::string &last);
    void setDiscount(const bool discount);
};