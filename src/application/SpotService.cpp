// src/application/SpotService.cpp
#include "application/SpotService.h"
#include "domain/Owner.h"
#include "domain/SpotRepository.h"
#include <QFile>
#include <QString>
#include <QStringConverter>
#include <QTextStream>


// Forward declaration
static QStringList parseCsvLine(const QString &line);

SpotService::SpotService(SpotRepository &repo) : repo(repo)
{
}

std::optional<Spot> SpotService::getSpot(int id)
{
    return repo.findById(id);
}

std::vector<Spot> SpotService::getAllSpots()
{
    return repo.findAll();
}

void SpotService::addOrUpdateSpot(const Spot &spot)
{
    repo.save(spot);
}

void SpotService::removeSpot(int id)
{
    repo.remove(id);
}

SpotService::ImportResult SpotService::importFromCsv(const std::string &filePath)
{
    ImportResult result = {0, 0, 0};

    QFile file(QString::fromStdString(filePath));
    if (!file.open(QIODevice::ReadOnly))
        return result;

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList fields = parseCsvLine(line);

        while (fields.size() < 22)
            fields.append("");

        int id = fields[0].toInt();
        if (id <= 0)
        {
            ++result.skipped;
            continue;
        }

        if (fields[1].isEmpty() && fields[2].isEmpty())
        {
            ++result.skipped;
            continue;
        }

        Owner owner(fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString(), fields[4].toStdString(),
                    fields[5].toStdString(), fields[6].toStdString(), fields[7].toStdString(), fields[8].toStdString(),
                    fields[9].toStdString(), fields[10].toStdString(), fields[11].toStdString(),
                    fields[12].toStdString(), fields[13].toStdString(), fields[14].toStdString(),
                    fields[15].toStdString(), fields[16].toStdString(), fields[17].toStdString(),
                    fields[18].isEmpty() ? 0 : fields[18].toInt(), fields[19] == "true", fields[20] == "true");

        Spot spot(id, std::move(owner), fields[21].toStdString());

        auto existing = repo.findById(id);
        if (existing.has_value())
        {
            repo.save(spot);
            ++result.updated;
        }
        else
        {
            repo.save(spot);
            ++result.imported;
        }
    }

    file.close();
    return result;
}

static QStringList parseCsvLine(const QString &line)
{
    QStringList fields;
    QString field;
    bool inQuotes = false;

    for (int i = 0; i < line.size(); ++i)
    {
        QChar c = line[i];

        if (inQuotes)
        {
            if (c == '"')
            {
                if (i + 1 < line.size() && line[i + 1] == '"')
                {
                    field += '"';
                    ++i;
                }
                else
                {
                    inQuotes = false;
                }
            }
            else
            {
                field += c;
            }
        }
        else
        {
            if (c == '"')
            {
                inQuotes = true;
            }
            else if (c == ';')
            {
                fields.append(field.trimmed());
                field.clear();
            }
            else
            {
                field += c;
            }
        }
    }

    fields.append(field.trimmed());
    return fields;
}