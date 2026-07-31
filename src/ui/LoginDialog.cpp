// src/ui/LoginDialog.cpp
#include "ui/LoginDialog.h"
#include "domain/AuthService.h"
#include "domain/User.h"
#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedLayout>
#include <QVBoxLayout>


LoginDialog::LoginDialog(AuthService &authService, QWidget *parent)
    : QDialog(parent), authService(authService), loginForm(nullptr), changePasswordForm(nullptr)
{
    setWindowTitle("Вход в систему");
    setMinimumWidth(350);
    setMaximumHeight(400);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QStackedLayout *stack = new QStackedLayout();
    mainLayout->addLayout(stack);

    // Форма входа
    loginForm = new QWidget();
    QVBoxLayout *loginLayout = new QVBoxLayout(loginForm);

    QFormLayout *form = new QFormLayout();
    editLogin = new QLineEdit();
    editLogin->setPlaceholderText("Логин");
    editLogin->setVisible(false);
    comboLogin = new QComboBox();
    comboLogin->addItems({"Мурашов", "Амелина", "Белов", "Белова", "Нефёдов"});
    editPassword = new QLineEdit();
    editPassword->setPlaceholderText("Пароль");
    editPassword->setEchoMode(QLineEdit::Password);
    form->addRow("Пользователь:", comboLogin);
    form->addRow("Пароль:", editPassword);
    loginLayout->addLayout(form);

    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color: red;");
    errorLabel->setVisible(false);
    loginLayout->addWidget(errorLabel);

    QPushButton *btnLogin = new QPushButton("Войти");
    connect(btnLogin, &QPushButton::clicked, this,
            [this]()
            {
                editLogin->setText(comboLogin->currentText());
                onLogin();
            });
    connect(editPassword, &QLineEdit::returnPressed, this,
            [this]()
            {
                editLogin->setText(comboLogin->currentText());
                onLogin();
            });
    loginLayout->addWidget(btnLogin);

    stack->addWidget(loginForm);
    stack->setCurrentWidget(loginForm);
}

bool LoginDialog::changePasswordForUser(const QString &login)
{
    currentLogin = login;
    editLogin->setText(login);

    setupChangePasswordForm(login);

    auto *stack = qobject_cast<QStackedLayout *>(layout()->itemAt(0)->layout());
    if (stack)
    {
        if (stack->count() > 1)
            delete stack->widget(1);
        stack->addWidget(changePasswordForm);
        stack->setCurrentWidget(changePasswordForm);
    }

    editOldPassword->setText("");
    editOldPassword->setReadOnly(false);
    editOldPassword->setFocus();

    return (exec() == QDialog::Accepted);
}

std::optional<Role> LoginDialog::loggedInRole() const
{
    return role;
}

void LoginDialog::onLogin()
{
    QString login = editLogin->text();
    QString password = editPassword->text();

    if (login.isEmpty() || password.isEmpty())
    {
        errorLabel->setText("Выберите пользователя и введите пароль");
        errorLabel->setVisible(true);
        return;
    }

    auto result = authService.authenticate(login.toStdString(), password.toStdString());
    if (!result.has_value())
    {
        errorLabel->setText("Неверный пароль");
        errorLabel->setVisible(true);
        return;
    }

    currentLogin = login;
    role = result;

    if (authService.mustChangePassword(login.toStdString()))
    {
        setupChangePasswordForm(login);

        auto *stack = qobject_cast<QStackedLayout *>(layout()->itemAt(0)->layout());
        if (stack)
        {
            stack->addWidget(changePasswordForm);
            stack->setCurrentWidget(changePasswordForm);
        }
        editOldPassword->setText(password);
        editOldPassword->setReadOnly(true);
        editNewPassword->setFocus();
    }
    else
    {
        accept();
    }
}

void LoginDialog::setupChangePasswordForm(const QString &login)
{
    changePasswordForm = new QWidget();
    QVBoxLayout *changeLayout = new QVBoxLayout(changePasswordForm);

    QLabel *changeTitle = new QLabel("Смена пароля для " + login);
    changeTitle->setStyleSheet("font-weight: bold;");
    changeLayout->addWidget(changeTitle);

    QFormLayout *changeForm = new QFormLayout();
    editOldPassword = new QLineEdit();
    editOldPassword->setPlaceholderText("Старый пароль");
    editOldPassword->setEchoMode(QLineEdit::Password);
    editNewPassword = new QLineEdit();
    editNewPassword->setPlaceholderText("Новый пароль");
    editNewPassword->setEchoMode(QLineEdit::Password);
    editConfirmPassword = new QLineEdit();
    editConfirmPassword->setPlaceholderText("Подтверждение");
    editConfirmPassword->setEchoMode(QLineEdit::Password);
    changeForm->addRow("Старый:", editOldPassword);
    changeForm->addRow("Новый:", editNewPassword);
    changeForm->addRow("Ещё раз:", editConfirmPassword);
    changeLayout->addLayout(changeForm);

    changeErrorLabel = new QLabel();
    changeErrorLabel->setStyleSheet("color: red;");
    changeErrorLabel->setVisible(false);
    changeLayout->addWidget(changeErrorLabel);

    QPushButton *btnChange = new QPushButton("Сменить пароль");
    connect(btnChange, &QPushButton::clicked, this,
            [this]()
            {
                QString oldPwd = editOldPassword->text();
                QString newPwd = editNewPassword->text();
                QString confirmPwd = editConfirmPassword->text();

                if (newPwd != confirmPwd)
                {
                    changeErrorLabel->setText("Пароли не совпадают");
                    changeErrorLabel->setVisible(true);
                    return;
                }

                if (newPwd.isEmpty())
                {
                    changeErrorLabel->setText("Новый пароль не может быть пустым");
                    changeErrorLabel->setVisible(true);
                    return;
                }

                if (authService.changePassword(currentLogin.toStdString(), oldPwd.toStdString(), newPwd.toStdString()))
                {
                    QMessageBox::information(this, "Успех", "Пароль изменён.");
                    accept();
                }
                else
                {
                    changeErrorLabel->setText("Неверный старый пароль");
                    changeErrorLabel->setVisible(true);
                }
            });
    changeLayout->addWidget(btnChange);
}