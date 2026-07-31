#include "domain/Spot.h"
#include <utility>

// ============================================================================
// Конструкторы
// ============================================================================

Spot::Spot(int id, Owner owner, std::string notes) : id(id), owner(std::move(owner)), notes(std::move(notes))
{
}

Spot::Spot(int id)
    : id(id), owner() // пустой владелец (свободно)
      ,
      notes("")
{
}

// ============================================================================
// Геттеры
// ============================================================================

int Spot::getId() const
{
    return id;
}
const Owner &Spot::getOwner() const
{
    return owner;
}
const std::string &Spot::getNotes() const
{
    return notes;
}

// ============================================================================
// Бизнес-логика
// ============================================================================

int Spot::getBaseMonthlyPayment() const
{
    return (id <= 150) ? 1300 : 2000;
}

int Spot::getFinalPayment() const
{
    return static_cast<int>(getBaseMonthlyPayment() * owner.getDiscountMultiplier());
}

// ============================================================================
// Мутация
// ============================================================================

void Spot::setOwner(Owner newOwner)
{
    owner = std::move(newOwner);
}

void Spot::setNotes(const std::string &newNotes)
{
    notes = newNotes;
}