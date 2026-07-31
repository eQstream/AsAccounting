// src/domain/UserRepository.h
#pragma once
#include "domain/User.h"
#include <optional>

/// @brief Интерфейс репозитория пользователей.
class UserRepository
{
public:
    virtual ~UserRepository() = default;

    /// @brief Найти пользователя по логину.
    /// @param login Логин
    /// @return User если найден, иначе std::nullopt
    virtual std::optional<User> findByLogin(const std::string &login) = 0;

    /// @brief Сохранить пользователя (добавить или обновить).
    /// @param user Пользователь
    virtual void save(const User &user) = 0;
};