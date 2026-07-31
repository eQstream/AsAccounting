// src/domain/AuthService.h
#pragma once
#include "domain/User.h"
#include <optional>
#include <string>


class UserRepository;

/// @brief Доменный сервис аутентификации.
///
/// Отвечает за проверку пароля, смену пароля и хеширование.
class AuthService
{
public:
    explicit AuthService(UserRepository &userRepo);

    std::optional<Role> authenticate(const std::string &login, const std::string &password);
    bool mustChangePassword(const std::string &login);
    bool changePassword(const std::string &login, const std::string &oldPassword, const std::string &newPassword);

private:
    static std::string hashPassword(const std::string &password);
    static constexpr const char *SALT = "MGSASalt2024";

    UserRepository &userRepo;
};