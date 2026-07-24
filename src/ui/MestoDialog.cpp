#include "ui/MestoDialog.h"
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QTextEdit>
#include <QVBoxLayout>


// ============================================================================
// Конструктор для добавления нового места
// ============================================================================

MestoDialog::MestoDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Добавить машиноместо");
    setMinimumWidth(750);
    setupUi();
    fillFromMesto(Mesto(-1));
}

// ============================================================================
// Конструктор для редактирования существующего места
// ============================================================================

MestoDialog::MestoDialog(const Mesto &m, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Редактировать машиноместо");
    setMinimumWidth(750);
    setupUi();
    fillFromMesto(m);
}

// ============================================================================
// Построение UI — два столбца
// ============================================================================

void MestoDialog::setupUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Область прокрутки на случай маленького экрана
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *scrollWidget = new QWidget();
    QHBoxLayout *columnsLayout = new QHBoxLayout(scrollWidget);

    // ========================================================================
    // Левый столбец
    // ========================================================================
    QVBoxLayout *leftColumn = new QVBoxLayout();

    // --- Основные данные ---
    QGroupBox *groupMain = new QGroupBox("Основные данные");
    QFormLayout *formMain = new QFormLayout(groupMain);

    editPlace = new QLineEdit();
    editPlace->setPlaceholderText("Номер места");
    formMain->addRow("№ места:", editPlace);

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

    // --- Документы ---
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

    // ========================================================================
    // Правый столбец
    // ========================================================================
    QVBoxLayout *rightColumn = new QVBoxLayout();

    // --- Адреса ---
    QGroupBox *groupAddr = new QGroupBox("Адреса");
    QFormLayout *formAddr = new QFormLayout(groupAddr);

    editRegistrationAddress = new QTextEdit();
    editRegistrationAddress->setMaximumHeight(50);
    formAddr->addRow("Прописка:", editRegistrationAddress);

    editActualAddress = new QTextEdit();
    editActualAddress->setMaximumHeight(50);
    formAddr->addRow("Фактический:", editActualAddress);

    rightColumn->addWidget(groupAddr);

    // --- Контакты ---
    QGroupBox *groupContacts = new QGroupBox("Контакты");
    QFormLayout *formContacts = new QFormLayout(groupContacts);

    editPhone1 = new QLineEdit();
    formContacts->addRow("Телефон 1:", editPhone1);

    editPhone2 = new QLineEdit();
    formContacts->addRow("Телефон 2:", editPhone2);

    editPhone3 = new QLineEdit();
    formContacts->addRow("Телефон 3:", editPhone3);

    rightColumn->addWidget(groupContacts);

    // --- Автомобиль ---
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

    // --- Статус ---
    QGroupBox *groupStatus = new QGroupBox("Статус");
    QHBoxLayout *layoutStatus = new QHBoxLayout(groupStatus);

    checkPensioner = new QCheckBox("Пенсионер");
    checkDisabled = new QCheckBox("Инвалид");
    layoutStatus->addWidget(checkPensioner);
    layoutStatus->addWidget(checkDisabled);
    layoutStatus->addStretch();

    rightColumn->addWidget(groupStatus);

    // --- Заметки ---
    QGroupBox *groupNotes = new QGroupBox("Заметки");
    QVBoxLayout *layoutNotes = new QVBoxLayout(groupNotes);

    editNotes = new QTextEdit();
    editNotes->setMaximumHeight(50);
    layoutNotes->addWidget(editNotes);

    rightColumn->addWidget(groupNotes);
    rightColumn->addStretch();

    // Собираем столбцы
    columnsLayout->addLayout(leftColumn);
    columnsLayout->addLayout(rightColumn);

    scrollArea->setWidget(scrollWidget);
    mainLayout->addWidget(scrollArea);

    // --- Кнопки ОК/Отмена ---
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
}

// ============================================================================
// Заполнение полей из объекта Mesto
// ============================================================================

void MestoDialog::fillFromMesto(const Mesto &m)
{
    editPlace->setText(m.getPlace() > 0 ? QString::number(m.getPlace()) : "");
    editLastName->setText(QString::fromStdString(m.getLastName()));
    editFirstName->setText(QString::fromStdString(m.getFirstName()));
    editMiddleName->setText(QString::fromStdString(m.getMiddleName()));
    editBirthDate->setText(QString::fromStdString(m.getBirthDate()));
    editRegistrationAddress->setPlainText(QString::fromStdString(m.getRegistrationAddress()));
    editActualAddress->setPlainText(QString::fromStdString(m.getActualAddress()));
    editPhone1->setText(QString::fromStdString(m.getPhone1()));
    editPhone2->setText(QString::fromStdString(m.getPhone2()));
    editPhone3->setText(QString::fromStdString(m.getPhone3()));
    editMgsaTicketNumber->setText(QString::fromStdString(m.getMgsaTicketNumber()));
    editMgsaTicketIssueDate->setText(QString::fromStdString(m.getMgsaTicketIssueDate()));
    editPassportSeries->setText(QString::fromStdString(m.getPassportSeries()));
    editPassportNumber->setText(QString::fromStdString(m.getPassportNumber()));
    editPassportIssuedBy->setText(QString::fromStdString(m.getPassportIssuedBy()));
    editPassportIssueDate->setText(QString::fromStdString(m.getPassportIssueDate()));
    editVehicleBrand->setText(QString::fromStdString(m.getVehicleBrand()));
    editVehiclePlate->setText(QString::fromStdString(m.getVehiclePlate()));
    editVehicleYear->setText(m.getVehicleYear() != 0 ? QString::number(m.getVehicleYear()) : "");
    checkPensioner->setChecked(m.isPensioner());
    checkDisabled->setChecked(m.isDisabled());
    editNotes->setPlainText(QString::fromStdString(m.getNotes()));
}

// ============================================================================
// Получение объекта Mesto из полей диалога
// ============================================================================

Mesto MestoDialog::getMesto() const
{
    return Mesto(editPlace->text().toInt(), editLastName->text().toStdString(), editFirstName->text().toStdString(),
                 editMiddleName->text().toStdString(), editBirthDate->text().toStdString(),
                 editRegistrationAddress->toPlainText().toStdString(), editActualAddress->toPlainText().toStdString(),
                 editPhone1->text().toStdString(), editPhone2->text().toStdString(), editPhone3->text().toStdString(),
                 editMgsaTicketNumber->text().toStdString(), editMgsaTicketIssueDate->text().toStdString(),
                 editPassportSeries->text().toStdString(), editPassportNumber->text().toStdString(),
                 editPassportIssuedBy->text().toStdString(), editPassportIssueDate->text().toStdString(),
                 editVehicleBrand->text().toStdString(), editVehiclePlate->text().toStdString(),
                 editVehicleYear->text().toInt(), checkPensioner->isChecked(), checkDisabled->isChecked(),
                 editNotes->toPlainText().toStdString());
}

// ============================================================================
// Режим "только чтение"
// ============================================================================

void MestoDialog::setReadOnly(bool readOnly)
{
    editPlace->setReadOnly(readOnly);
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