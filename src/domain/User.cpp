// src/domain/User.cpp
#include "domain/User.h"
#include <utility>

User::User(std::string login, std::string passwordHash, Role role, bool mustChangePassword)
    : login(std::move(login)), passwordHash(std::move(passwordHash)), role(role), changePassword(mustChangePassword)
{
}

const std::string &User::getLogin() const
{
    return login;
}
const std::string &User::getPasswordHash() const
{
    return passwordHash;
}
Role User::getRole() const
{
    return role;
}
bool User::mustChangePassword() const
{
    return changePassword;
}

void User::setPasswordHash(const std::string &hash)
{
    passwordHash = hash;
}

void User::passwordChanged()
{
    changePassword = false;
}