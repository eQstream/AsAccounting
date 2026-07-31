// src/domain/SpotRepository.h
#pragma once
#include "domain/Spot.h"
#include <optional>
#include <vector>


/// @brief Интерфейс репозитория машиномест.
///
/// Определяет контракт для доступа к данным агрегата Spot.
/// Реализация находится в infrastructure/SqliteSpotRepository.
class SpotRepository
{
public:
    virtual ~SpotRepository() = default;

    /// @brief Найти место по id.
    /// @param id Номер места
    /// @return Spot если найден, иначе std::nullopt
    virtual std::optional<Spot> findById(int id) = 0;

    /// @brief Получить все места, отсортированные по id.
    /// @return Вектор Spot (может быть пустым)
    virtual std::vector<Spot> findAll() = 0;

    /// @brief Сохранить место (добавить или обновить).
    /// @param spot Объект Spot
    virtual void save(const Spot &spot) = 0;

    /// @brief Удалить место по id.
    /// @param id Номер места
    virtual void remove(int id) = 0;
};