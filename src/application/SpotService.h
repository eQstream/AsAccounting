// src/application/SpotService.h
#pragma once
#include "domain/Spot.h"
#include <optional>
#include <vector>


class SpotRepository;

/// @brief Сервис прикладного уровня для работы с машиноместами.
///
/// Координирует операции между UI и репозиторием.
/// Содержит логику импорта CSV.
class SpotService
{
public:
    explicit SpotService(SpotRepository &repo);

    std::optional<Spot> getSpot(int id);
    std::vector<Spot> getAllSpots();
    void addOrUpdateSpot(const Spot &spot);
    void removeSpot(int id);

    /// @brief Импорт из CSV-файла (UTF-8, разделитель ';').
    /// @param filePath Путь к файлу
    /// @return {imported, updated, skipped}
    struct ImportResult
    {
        int imported;
        int updated;
        int skipped;
    };
    ImportResult importFromCsv(const std::string &filePath);

private:
    SpotRepository &repo;
};