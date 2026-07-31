// src/domain/AuthService.cpp
#include "domain/AuthService.h"
#include "domain/UserRepository.h"
#include <QCryptographicHash>
#include <QString>

AuthService::AuthService(UserRepository &userRepo) : userRepo(userRepo)
{
}

std::optional<Role> AuthService::authenticate(const std::string &login, const std::string &password)
{
    auto user = userRepo.findByLogin(login);
    if (!user.has_value())
        return std::nullopt;

    if (user->getPasswordHash() != hashPassword(password))
        return std::nullopt;

    return user->getRole();
}

bool AuthService::mustChangePassword(const std::string &login)
{
    auto user = userRepo.findByLogin(login);
    if (!user.has_value())
        return false;

    return user->mustChangePassword();
}

bool AuthService::changePassword(const std::string &login, const std::string &oldPassword,
                                 const std::string &newPassword)
{
    auto user = userRepo.findByLogin(login);
    if (!user.has_value())
        return false;

    if (user->getPasswordHash() != hashPassword(oldPassword))
        return false;

    user->setPasswordHash(hashPassword(newPassword));
    user->passwordChanged();
    userRepo.save(*user);

    return true;
}

std::string AuthService::hashPassword(const std::string &password)
{
    QString input = QString::fromStdString(password) + SALT;
    QByteArray hash = QCryptographicHash::hash(input.toUtf8(), QCryptographicHash::Sha256);
    return hash.toHex().toStdString();
}