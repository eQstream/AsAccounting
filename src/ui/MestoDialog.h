#pragma once
#include "Mesto.h"
#include <QDialog>


class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;

/// @brief Диалог просмотра и редактирования данных одного машиноместа.
///
/// Используется для добавления нового места, редактирования существующего
/// и просмотра (режим "только чтение").
class MestoDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Конструктор для добавления нового места.
    /// @param parent Родительский виджет
    explicit MestoDialog(QWidget *parent = nullptr);

    /// @brief Конструктор для редактирования существующего места.
    /// @param m Объект Mesto для редактирования
    /// @param parent Родительский виджет
    explicit MestoDialog(const Mesto &m, QWidget *parent = nullptr);

    ~MestoDialog() = default;

    /// @brief Возвращает объект Mesto с введёнными данными.
    /// @return Объект Mesto
    Mesto getMesto() const;

    /// @brief Переключает все поля в режим "только чтение".
    /// @param readOnly true — только просмотр, false — можно редактировать
    void setReadOnly(bool readOnly);

private:
    /// @brief Создаёт и размещает все виджеты диалога.
    void setupUi();

    /// @brief Заполняет поля данными из объекта Mesto.
    /// @param m Объект Mesto
    void fillFromMesto(const Mesto &m);

    // Поля ввода
    QLineEdit *editPlace;
    QLineEdit *editLastName;
    QLineEdit *editFirstName;
    QLineEdit *editMiddleName;
    QLineEdit *editBirthDate;
    QTextEdit *editRegistrationAddress;
    QTextEdit *editActualAddress;
    QLineEdit *editPhone1;
    QLineEdit *editPhone2;
    QLineEdit *editPhone3;
    QLineEdit *editMgsaTicketNumber;
    QLineEdit *editMgsaTicketIssueDate;
    QLineEdit *editPassportSeries;
    QLineEdit *editPassportNumber;
    QLineEdit *editPassportIssuedBy;
    QLineEdit *editPassportIssueDate;
    QLineEdit *editVehicleBrand;
    QLineEdit *editVehiclePlate;
    QLineEdit *editVehicleYear;
    QCheckBox *checkPensioner;
    QCheckBox *checkDisabled;
    QTextEdit *editNotes;

    QDialogButtonBox *buttonBox;
};