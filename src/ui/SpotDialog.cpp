// src/ui/SpotDialog.cpp
#include "ui/SpotDialog.h"
#include "domain/Owner.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>


// ============================================================================
// Конструкторы
// ============================================================================

SpotDialog::SpotDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Добавить машиноместо");
    setMinimumWidth(750);
    setupUi();
    fillFromSpot(Spot(-1));
}

SpotDialog::SpotDialog(const Spot &spot, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Редактировать машиноместо");
    setMinimumWidth(750);
    setupUi();
    fillFromSpot(spot);
}

// ============================================================================
// Построение UI — два столбца
// ============================================================================

void SpotDialog::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget();
    QHBoxLayout *columnsLayout = new QHBoxLayout(scrollWidget);

    // Левый столбец
    QVBoxLayout *leftColumn = new QVBoxLayout();

    QGroupBox *groupMain = new QGroupBox("Основные данные");
    QFormLayout *formMain = new QFormLayout(groupMain);

    editId = new QLineEdit();
    editId->setPlaceholderText("Номер места");
    formMain->addRow("№ места:", editId);

    editLastName = new QLineEdit();
    formMain->addRow("Фамилия:", editLastName);

    editFirstName = new QLineEdit();
    formMain->addRow("Имя:", editFirstName);

    editMiddleName = new QLineEdit();
    formMain->addRow("Отчество:", editMiddleName);

    editBirthDate = new QLineEdit();
    editBirthDate->setPlaceholderText("ДД.ММ.ГГГГ");
    formMain->addRow("Дата рождения:", editBirthDate);

    leftColumn->addWidget(groupMain);

    QGroupBox *groupDocs = new QGroupBox("Документы");
    QFormLayout *formDocs = new QFormLayout(groupDocs);

    editPassportSeries = new QLineEdit();
    formDocs->addRow("Серия паспорта:", editPassportSeries);

    editPassportNumber = new QLineEdit();
    formDocs->addRow("Номер паспорта:", editPassportNumber);

    editPassportIssuedBy = new QLineEdit();
    formDocs->addRow("Кем выдан:", editPassportIssuedBy);

    editPassportIssueDate = new QLineEdit();
    editPassportIssueDate->setPlaceholderText("ДД.ММ.ГГГГ");
    formDocs->addRow("Дата выдачи:", editPassportIssueDate);

    editMgsaTicketNumber = new QLineEdit();
    formDocs->addRow("Билет МГСА №:", editMgsaTicketNumber);

    editMgsaTicketIssueDate = new QLineEdit();
    editMgsaTicketIssueDate->setPlaceholderText("ДД.ММ.ГГГГ");
    formDocs->addRow("Дата выдачи билета:", editMgsaTicketIssueDate);

    leftColumn->addWidget(groupDocs);
    leftColumn->addStretch();

    // Правый столбец
    QVBoxLayout *rightColumn = new QVBoxLayout();

    QGroupBox *groupAddr = new QGroupBox("Адреса");
    QFormLayout *formAddr = new QFormLayout(groupAddr);

    editRegistrationAddress = new QTextEdit();
    editRegistrationAddress->setMaximumHeight(50);
    formAddr->addRow("Прописка:", editRegistrationAddress);

    editActualAddress = new QTextEdit();
    editActualAddress->setMaximumHeight(50);
    formAddr->addRow("Фактический:", editActualAddress);

    rightColumn->addWidget(groupAddr);

    QGroupBox *groupContacts = new QGroupBox("Контакты");
    QFormLayout *formContacts = new QFormLayout(groupContacts);

    editPhone1 = new QLineEdit();
    formContacts->addRow("Телефон 1:", editPhone1);

    editPhone2 = new QLineEdit();
    formContacts->addRow("Телефон 2:", editPhone2);

    editPhone3 = new QLineEdit();
    formContacts->addRow("Телефон 3:", editPhone3);

    rightColumn->addWidget(groupContacts);

    QGroupBox *groupAuto = new QGroupBox("Автомобиль");
    QFormLayout *formAuto = new QFormLayout(groupAuto);

    editVehicleBrand = new QLineEdit();
    formAuto->addRow("Марка/модель:", editVehicleBrand);

    editVehiclePlate = new QLineEdit();
    formAuto->addRow("Госномер:", editVehiclePlate);

    editVehicleYear = new QLineEdit();
    editVehicleYear->setPlaceholderText("Год выпуска");
    formAuto->addRow("Год:", editVehicleYear);

    rightColumn->addWidget(groupAuto);

    QGroupBox *groupStatus = new QGroupBox("Статус");
    QHBoxLayout *layoutStatus = new QHBoxLayout(groupStatus);

    checkPensioner = new QCheckBox("Пенсионер");
    checkDisabled = new QCheckBox("Инвалид");
    layoutStatus->addWidget(checkPensioner);
    layoutStatus->addWidget(checkDisabled);
    layoutStatus->addStretch();

    rightColumn->addWidget(groupStatus);

    QGroupBox *groupNotes = new QGroupBox("Заметки");
    QVBoxLayout *layoutNotes = new QVBoxLayout(groupNotes);

    editNotes = new QTextEdit();
    editNotes->setMaximumHeight(50);
    layoutNotes->addWidget(editNotes);

    rightColumn->addWidget(groupNotes);
    rightColumn->addStretch();

    columnsLayout->addLayout(leftColumn);
    columnsLayout->addLayout(rightColumn);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
}

// ============================================================================
// Заполнение полей
// ============================================================================

void SpotDialog::fillFromSpot(const Spot &spot)
{
    const Owner &o = spot.getOwner();

    editId->setText(spot.getId() > 0 ? QString::number(spot.getId()) : "");
    editLastName->setText(QString::fromStdString(o.getLastName()));
    editFirstName->setText(QString::fromStdString(o.getFirstName()));
    editMiddleName->setText(QString::fromStdString(o.getMiddleName()));
    editBirthDate->setText(QString::fromStdString(o.getBirthDate()));
    editRegistrationAddress->setPlainText(QString::fromStdString(o.getRegistrationAddress()));
    editActualAddress->setPlainText(QString::fromStdString(o.getActualAddress()));
    editPhone1->setText(QString::fromStdString(o.getPhone1()));
    editPhone2->setText(QString::fromStdString(o.getPhone2()));
    editPhone3->setText(QString::fromStdString(o.getPhone3()));
    editMgsaTicketNumber->setText(QString::fromStdString(o.getMgsaTicketNumber()));
    editMgsaTicketIssueDate->setText(QString::fromStdString(o.getMgsaTicketIssueDate()));
    editPassportSeries->setText(QString::fromStdString(o.getPassportSeries()));
    editPassportNumber->setText(QString::fromStdString(o.getPassportNumber()));
    editPassportIssuedBy->setText(QString::fromStdString(o.getPassportIssuedBy()));
    editPassportIssueDate->setText(QString::fromStdString(o.getPassportIssueDate()));
    editVehicleBrand->setText(QString::fromStdString(o.getVehicleBrand()));
    editVehiclePlate->setText(QString::fromStdString(o.getVehiclePlate()));
    editVehicleYear->setText(o.getVehicleYear() != 0 ? QString::number(o.getVehicleYear()) : "");
    checkPensioner->setChecked(o.isPensioner());
    checkDisabled->setChecked(o.isDisabled());
    editNotes->setPlainText(QString::fromStdString(spot.getNotes()));
}

// ============================================================================
// Получение Spot из полей
// ============================================================================

Spot SpotDialog::getSpot() const
{
    Owner owner(editLastName->text().toStdString(), editFirstName->text().toStdString(),
                editMiddleName->text().toStdString(), editBirthDate->text().toStdString(),
                editRegistrationAddress->toPlainText().toStdString(), editActualAddress->toPlainText().toStdString(),
                editPhone1->text().toStdString(), editPhone2->text().toStdString(), editPhone3->text().toStdString(),
                editMgsaTicketNumber->text().toStdString(), editMgsaTicketIssueDate->text().toStdString(),
                editPassportSeries->text().toStdString(), editPassportNumber->text().toStdString(),
                editPassportIssuedBy->text().toStdString(), editPassportIssueDate->text().toStdString(),
                editVehicleBrand->text().toStdString(), editVehiclePlate->text().toStdString(),
                editVehicleYear->text().toInt(), checkPensioner->isChecked(), checkDisabled->isChecked());

    return Spot(editId->text().toInt(), std::move(owner), editNotes->toPlainText().toStdString());
}

// ============================================================================
// Режим "только чтение"
// ============================================================================

void SpotDialog::setReadOnly(bool readOnly)
{
    editId->setReadOnly(readOnly);
    editLastName->setReadOnly(readOnly);
    editFirstName->setReadOnly(readOnly);
    editMiddleName->setReadOnly(readOnly);
    editBirthDate->setReadOnly(readOnly);
    editRegistrationAddress->setReadOnly(readOnly);
    editActualAddress->setReadOnly(readOnly);
    editPhone1->setReadOnly(readOnly);
    editPhone2->setReadOnly(readOnly);
    editPhone3->setReadOnly(readOnly);
    editMgsaTicketNumber->setReadOnly(readOnly);
    editMgsaTicketIssueDate->setReadOnly(readOnly);
    editPassportSeries->setReadOnly(readOnly);
    editPassportNumber->setReadOnly(readOnly);
    editPassportIssuedBy->setReadOnly(readOnly);
    editPassportIssueDate->setReadOnly(readOnly);
    editVehicleBrand->setReadOnly(readOnly);
    editVehiclePlate->setReadOnly(readOnly);
    editVehicleYear->setReadOnly(readOnly);
    checkPensioner->setEnabled(!readOnly);
    checkDisabled->setEnabled(!readOnly);
    editNotes->setReadOnly(readOnly);

    buttonBox->setVisible(!readOnly);
}