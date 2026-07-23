#pragma once
#include <string>

/// @brief Модель данных одного машиноместа в гаражном кооперативе.
///
/// Содержит полную информацию о владельце: ФИО, паспортные данные,
/// контактную информацию, данные автомобиля, членство в МГСА,
/// статус льготника и баланс места.
/// Соответствует одной строке CSV-импорта и таблице `mesto` в БД.
class Mesto
{
private:
    // ========================================================================
    // Основные данные
    // ========================================================================

    int place;               ///< Номер машиноместа (первичный ключ, совпадает с id в БД)
    std::string last_name;   ///< Фамилия владельца
    std::string first_name;  ///< Имя владельца
    std::string middle_name; ///< Отчество владельца

    // ========================================================================
    // Документы
    // ========================================================================

    std::string birth_date;             ///< Дата рождения (строка, формат ДД.ММ.ГГГГ)
    std::string passport_series;        ///< Серия паспорта
    std::string passport_number;        ///< Номер паспорта
    std::string passport_issued_by;     ///< Кем выдан паспорт
    std::string passport_issue_date;    ///< Дата выдачи паспорта
    std::string mgsa_ticket_number;     ///< Номер членского билета МГСА
    std::string mgsa_ticket_issue_date; ///< Дата выдачи членского билета

    // ========================================================================
    // Адреса
    // ========================================================================

    std::string registration_address; ///< Адрес регистрации (прописка)
    std::string actual_address;       ///< Адрес фактического проживания

    // ========================================================================
    // Контакты
    // ========================================================================

    std::string phone1; ///< Основной телефон
    std::string phone2; ///< Дополнительный телефон 1
    std::string phone3; ///< Дополнительный телефон 2

    // ========================================================================
    // Автомобиль
    // ========================================================================

    std::string vehicle_brand; ///< Марка и модель автомобиля
    std::string vehicle_plate; ///< Государственный номер
    int vehicle_year;          ///< Год выпуска

    // ========================================================================
    // Статус
    // ========================================================================

    bool pensioner; ///< Является пенсионером (льгота)
    bool disabled;  ///< Является инвалидом (льгота 20% на оплату)

    // ========================================================================
    // Баланс и заметки
    // ========================================================================

    int spot_balance;  ///< Текущий баланс места (может быть отрицательным)
    std::string notes; ///< Произвольные заметки

public:
    // ========================================================================
    // Конструкторы
    // ========================================================================

    /// @brief Полный конструктор — все поля, порядок соответствует CSV/БД.
    /// @param place Номер машиноместа
    /// @param last_name Фамилия
    /// @param first_name Имя
    /// @param middle_name Отчество
    /// @param birth_date Дата рождения
    /// @param registration_address Адрес регистрации
    /// @param actual_address Фактический адрес
    /// @param phone1 Основной телефон
    /// @param phone2 Доп. телефон 1
    /// @param phone3 Доп. телефон 2
    /// @param mgsa_ticket_number Номер билета МГСА
    /// @param mgsa_ticket_issue_date Дата выдачи билета
    /// @param passport_series Серия паспорта
    /// @param passport_number Номер паспорта
    /// @param passport_issued_by Кем выдан
    /// @param passport_issue_date Дата выдачи
    /// @param vehicle_brand Марка и модель авто
    /// @param vehicle_plate Госномер
    /// @param vehicle_year Год выпуска
    /// @param pensioner Пенсионер
    /// @param disabled Инвалид
    /// @param notes Заметки
    /// @param spot_balance Баланс (по умолчанию 0)
    Mesto(int place, std::string last_name, std::string first_name, std::string middle_name, std::string birth_date,
          std::string registration_address, std::string actual_address, std::string phone1, std::string phone2,
          std::string phone3, std::string mgsa_ticket_number, std::string mgsa_ticket_issue_date,
          std::string passport_series, std::string passport_number, std::string passport_issued_by,
          std::string passport_issue_date, std::string vehicle_brand, std::string vehicle_plate, int vehicle_year,
          bool pensioner, bool disabled, std::string notes, int spot_balance = 0);

    /// @brief Краткий конструктор — только номер места и ФИО.
    ///        Остальные поля инициализируются значениями по умолчанию.
    /// @param place Номер машиноместа
    /// @param last_name Фамилия (по умолчанию "")
    /// @param first_name Имя (по умолчанию "")
    /// @param middle_name Отчество (по умолчанию "")
    Mesto(int place, std::string last_name = "", std::string first_name = "", std::string middle_name = "");

    ~Mesto();

    // ========================================================================
    // Геттеры
    // ========================================================================

    /// @name Основные данные
    /// @{

    /// @return Номер машиноместа
    int getPlace() const;

    /// @return Фамилия
    const std::string &getLastName() const;

    /// @return Имя
    const std::string &getFirstName() const;

    /// @return Отчество
    const std::string &getMiddleName() const;

    /// @}

    /// @name Документы
    /// @{

    const std::string &getBirthDate() const;
    const std::string &getPassportSeries() const;
    const std::string &getPassportNumber() const;
    const std::string &getPassportIssuedBy() const;
    const std::string &getPassportIssueDate() const;
    const std::string &getMgsaTicketNumber() const;
    const std::string &getMgsaTicketIssueDate() const;

    /// @}

    /// @name Адреса
    /// @{

    const std::string &getRegistrationAddress() const;
    const std::string &getActualAddress() const;

    /// @}

    /// @name Телефоны
    /// @{

    const std::string &getPhone1() const;
    const std::string &getPhone2() const;
    const std::string &getPhone3() const;

    /// @}

    /// @name Автомобиль
    /// @{

    const std::string &getVehicleBrand() const;
    const std::string &getVehiclePlate() const;
    int getVehicleYear() const;

    /// @}

    /// @name Статус
    /// @{

    /// @return true если пенсионер
    bool isPensioner() const;

    /// @return true если инвалид
    bool isDisabled() const;

    /// @}

    /// @name Баланс
    /// @{

    /// @return Текущий баланс места
    int getSpotBalance() const;

    /// @}

    /// @return Произвольные заметки
    const std::string &getNotes() const;

    // ========================================================================
    // Бизнес-логика
    // ========================================================================

    /// @brief Базовый ежемесячный платёж без учёта льгот.
    /// @return Сумма в рублях (фиксированная ставка 1300 руб.)
    int getBaseMonthlyPayment() const;

    /// @brief Итоговый платёж с учётом льгот.
    ///
    /// Для инвалидов применяется скидка 20%.
    /// При расчёте нескольких льгот они не суммируются.
    /// @return Сумма к оплате в рублях
    int getFinalPayment() const;

    // ========================================================================
    // Сеттеры
    // ========================================================================

    /// @name ФИО
    /// @{
    void setLastName(const std::string &value);
    void setFirstName(const std::string &value);
    void setMiddleName(const std::string &value);
    /// @}

    /// @name Документы
    /// @{
    void setBirthDate(const std::string &value);
    void setPassportSeries(const std::string &value);
    void setPassportNumber(const std::string &value);
    void setPassportIssuedBy(const std::string &value);
    void setPassportIssueDate(const std::string &value);
    void setMgsaTicketNumber(const std::string &value);
    void setMgsaTicketIssueDate(const std::string &value);
    /// @}

    /// @name Адреса
    /// @{
    void setRegistrationAddress(const std::string &value);
    void setActualAddress(const std::string &value);
    /// @}

    /// @name Телефоны
    /// @{
    void setPhone1(const std::string &value);
    void setPhone2(const std::string &value);
    void setPhone3(const std::string &value);
    /// @}

    /// @name Автомобиль
    /// @{
    void setVehicleBrand(const std::string &value);
    void setVehiclePlate(const std::string &value);
    void setVehicleYear(int value);
    /// @}

    /// @name Статус
    /// @{
    void setPensioner(bool value);
    void setDisabled(bool value);
    /// @}

    /// @name Баланс
    /// @{
    void setSpotBalance(int value);
    /// @}

    void setNotes(const std::string &value);
};