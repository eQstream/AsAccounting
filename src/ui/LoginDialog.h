// src/ui/LoginDialog.h
#pragma once
#include "domain/User.h"
#include <QDialog>
#include <optional>

class QLineEdit;
class QLabel;
class QComboBox;
class AuthService;

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(AuthService &authService, QWidget *parent = nullptr);
    std::optional<Role> loggedInRole() const;
    QString getLogin() const
    {
        return currentLogin;
    }

    /// @brief Показать диалог смены пароля для текущего пользователя.
    /// @param login Логин пользователя
    /// @return true если пароль сменён
    bool changePasswordForUser(const QString &login);

private slots:
    void onLogin();

private:
    void setupLoginForm();
    void setupChangePasswordForm(const QString &login);

    AuthService &authService;

    QWidget *loginForm;
    QLineEdit *editLogin;
    QComboBox *comboLogin;
    QLineEdit *editPassword;
    QLabel *errorLabel;

    QWidget *changePasswordForm;
    QLineEdit *editOldPassword;
    QLineEdit *editNewPassword;
    QLineEdit *editConfirmPassword;
    QLabel *changeErrorLabel;

    QString currentLogin;
    std::optional<Role> role;
};