// src/ui/SpotDialog.h
#pragma once
#include "domain/Spot.h"
#include <QDialog>


class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;

/// @brief Диалог просмотра и редактирования данных одного машиноместа.
///
/// Используется для добавления нового места, редактирования существующего
/// и просмотра (режим "только чтение").
class SpotDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Конструктор для добавления нового места.
    explicit SpotDialog(QWidget *parent = nullptr);

    /// @brief Конструктор для редактирования существующего места.
    explicit SpotDialog(const Spot &spot, QWidget *parent = nullptr);

    ~SpotDialog() = default;

    /// @brief Возвращает объект Spot с введёнными данными.
    Spot getSpot() const;

    /// @brief Переключает все поля в режим "только чтение".
    void setReadOnly(bool readOnly);

private:
    void setupUi();
    void fillFromSpot(const Spot &spot);

    QLineEdit *editId;
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