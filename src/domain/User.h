// src/domain/User.h
#pragma once
#include <string>

/// @brief Роль пользователя в системе доступа.
enum class Role
{
    Admin,   ///< Полный доступ — просмотр и изменение
    Observer ///< Только просмотр
};

/// @brief Агрегат — пользователь системы доступа.
///
/// Содержит логин, хеш пароля, роль и флаг смены пароля.
class User
{
public:
    /// @brief Создаёт пользователя.
    /// @param login Логин
    /// @param passwordHash SHA256(пароль + соль)
    /// @param role Роль
    /// @param mustChangePassword Требуется ли смена пароля при первом входе
    User(std::string login, std::string passwordHash, Role role, bool mustChangePassword = false);

    const std::string &getLogin() const;
    const std::string &getPasswordHash() const;
    Role getRole() const;
    bool mustChangePassword() const;

    /// @brief Установить новый хеш пароля.
    void setPasswordHash(const std::string &hash);

    /// @brief Сбросить флаг смены пароля.
    void passwordChanged();

private:
    std::string login;
    std::string passwordHash;
    Role role;
    bool changePassword;
};