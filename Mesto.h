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
    int spot_balance;
    bool retired;
    bool discount; // имеет ли право на льготы

public:
    Mesto(int place_id, std::string first = "", std::string middle = "", std::string last = "", std::string phone = "",
          std::string addr = "", std::string pass = "", std::string model = "", std::string avto_num = "",
          int balance = 0, bool isRetired = false, bool isDiscount = false);
    ~Mesto();
    int getId() const;
    const std::string &getFirstName() const;
    const std::string &getMiddleName() const;
    const std::string &getLastName() const;
    const std::string &getPhoneNumber() const;
    const std::string &getAddress() const;
    const std::string &getPassport() const;
    const std::string &getAvtoModel() const;
    const std::string &getAvtoNumber() const;
    int getBaseMonthlyPayment() const;
    int getFinalPayment() const;
    int getBalance() const;
    bool getRetired() const;
    bool getDiscount() const;
    void setFirstName(const std::string &first);
    void setMiddleName(const std::string &middle);
    void setLastName(const std::string &last);
    void setPhone(const std::string &phone);
    void setAddress(const std::string &addr);
    void setPassport(const std::string &pass);
    void setAvtoModel(const std::string &model);
    void setAvtoNumber(const std::string &avto_num);
    void setBalance(const int balance);
    void setRetired(const bool isRetired);
    void setDiscount(const bool discount);
};