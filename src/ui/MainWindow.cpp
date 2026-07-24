#include "ui/MainWindow.h"
#include "Mesto.h"
#include "database/Database.h"
#include "ui/MestoDialog.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QStringConverter>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextStream>
#include <QVBoxLayout>


// ============================================================================
// Конструктор / Деструктор
// ============================================================================

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), tabWidget(nullptr), mestoTable(nullptr), searchEdit(nullptr), btnAdd(nullptr),
      btnEdit(nullptr), btnDelete(nullptr), btnImportCsv(nullptr), contextMenu(nullptr), db(nullptr)
{
    setWindowTitle("Гаражный учёт");
    resize(1000, 650);

    // Инициализация БД
    db = new Database("asaccounting.db");
    db->open();
    db->createTables();

    setupUi();
    refreshTable();
}

MainWindow::~MainWindow()
{
    db->close();
    delete db;
}

// ============================================================================
// Построение интерфейса
// ============================================================================

void MainWindow::setupUi()
{
    tabWidget = new QTabWidget(this);
    setCentralWidget(tabWidget);

    tabWidget->addTab(createAccountingTab(), "Учёт");
    tabWidget->addTab(createBookkeepingTab(), "Бухгалтерия");
}

// ============================================================================
// Вкладка "Учёт"
// ============================================================================

QWidget *MainWindow::createAccountingTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(tab);

    // Верхняя панель: поиск + кнопки
    QHBoxLayout *topPanel = new QHBoxLayout();

    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Поиск по фамилии, имени или номеру места...");
    searchEdit->setClearButtonEnabled(true);
    topPanel->addWidget(searchEdit, 1);

    btnAdd = new QPushButton("Добавить");
    btnEdit = new QPushButton("Редактировать");
    btnDelete = new QPushButton("Удалить");
    btnImportCsv = new QPushButton("Импорт CSV");

    topPanel->addWidget(btnAdd);
    topPanel->addWidget(btnEdit);
    topPanel->addWidget(btnDelete);
    topPanel->addWidget(btnImportCsv);

    mainLayout->addLayout(topPanel);

    // Таблица машиномест
    mestoTable = new QTableWidget(0, 8);
    mestoTable->setHorizontalHeaderLabels(
        {"№", "Фамилия", "Имя", "Отчество", "Телефон", "Автомобиль", "Госномер", "Льготы"});
    mestoTable->horizontalHeader()->setStretchLastSection(true);
    mestoTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    mestoTable->setSelectionMode(QAbstractItemView::SingleSelection);
    mestoTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mestoTable->setAlternatingRowColors(true);
    mestoTable->verticalHeader()->setVisible(false);
    mestoTable->setContextMenuPolicy(Qt::CustomContextMenu);

    mainLayout->addWidget(mestoTable);

    // Контекстное меню
    contextMenu = new QMenu(this);
    contextMenu->addAction("Редактировать", this, &MainWindow::onEditMesto);
    contextMenu->addAction("Удалить", this, &MainWindow::onDeleteMesto);

    // Сигналы
    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddMesto);
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::onEditMesto);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteMesto);
    connect(btnImportCsv, &QPushButton::clicked, this, &MainWindow::onImportCsv);
    connect(mestoTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTableDoubleClicked);
    connect(mestoTable, &QTableWidget::customContextMenuRequested, this, &MainWindow::onTableContextMenu);

    return tab;
}

// ============================================================================
// Вкладка "Бухгалтерия" (заглушка)
// ============================================================================

QWidget *MainWindow::createBookkeepingTab()
{
    QWidget *tab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(tab);
    QLabel *label = new QLabel("Здесь будет бухгалтерия");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    return tab;
}

// ============================================================================
// Заполнение таблицы из БД
// ============================================================================

void MainWindow::refreshTable()
{
    auto all = db->getAllMesto();
    mestoTable->setRowCount(static_cast<int>(all.size()));

    for (int row = 0; row < static_cast<int>(all.size()); ++row)
    {
        const Mesto &m = all[row];

        mestoTable->setItem(row, 0, new QTableWidgetItem(QString::number(m.getPlace())));
        mestoTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(m.getLastName())));
        mestoTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(m.getFirstName())));
        mestoTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(m.getMiddleName())));
        mestoTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(m.getPhone1())));
        mestoTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(m.getVehicleBrand())));
        mestoTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(m.getVehiclePlate())));

        QString benefits;
        if (m.isPensioner())
            benefits += "П";
        if (m.isDisabled())
            benefits += (benefits.isEmpty() ? "И" : ",И");
        mestoTable->setItem(row, 7, new QTableWidgetItem(benefits));
    }

    mestoTable->resizeColumnsToContents();
    applyFilter();
}

// ============================================================================
// Фильтрация по поиску
// ============================================================================

void MainWindow::onSearchTextChanged(const QString &text)
{
    Q_UNUSED(text);
    applyFilter();
}

void MainWindow::applyFilter()
{
    QString filter = searchEdit->text().trimmed();
    for (int row = 0; row < mestoTable->rowCount(); ++row)
    {
        bool match = filter.isEmpty();
        if (!match)
        {
            for (int col = 0; col < mestoTable->columnCount(); ++col)
            {
                QTableWidgetItem *item = mestoTable->item(row, col);
                if (item && item->text().contains(filter, Qt::CaseInsensitive))
                {
                    match = true;
                    break;
                }
            }
        }
        mestoTable->setRowHidden(row, !match);
    }
}

// ============================================================================
// Контекстное меню
// ============================================================================

void MainWindow::onTableContextMenu(const QPoint &pos)
{
    QTableWidgetItem *item = mestoTable->itemAt(pos);
    if (!item)
        return;

    mestoTable->selectRow(item->row());
    contextMenu->popup(mestoTable->viewport()->mapToGlobal(pos));
}

// ============================================================================
// Слоты кнопок
// ============================================================================

void MainWindow::onAddMesto()
{
    MestoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        db->addMesto(dialog.getMesto());
        refreshTable();
    }
}

void MainWindow::onEditMesto()
{
    int row = mestoTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Редактирование", "Выберите место для редактирования.");
        return;
    }

    int id = mestoTable->item(row, 0)->text().toInt();
    auto opt = db->getMestoById(id);
    if (!opt.has_value())
    {
        QMessageBox::warning(this, "Ошибка", "Запись не найдена в базе данных.");
        return;
    }

    MestoDialog dialog(opt.value(), this);
    if (dialog.exec() == QDialog::Accepted)
    {
        db->updateMesto(dialog.getMesto());
        refreshTable();
    }
}

void MainWindow::onDeleteMesto()
{
    int row = mestoTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Удаление", "Выберите место для удаления.");
        return;
    }

    int id = mestoTable->item(row, 0)->text().toInt();
    QString name = mestoTable->item(row, 1)->text() + " " + mestoTable->item(row, 2)->text();

    auto answer = QMessageBox::question(this, "Подтверждение", QString("Удалить место №%1 (%2)?").arg(id).arg(name),
                                        QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        db->deleteMesto(id);
        refreshTable();
    }
}

void MainWindow::onImportCsv()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Выберите CSV-файл", "data", "CSV files (*.csv);;All files (*.*)");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    int imported = 0;
    int updated = 0;
    int skipped = 0;

    // Пропускаем заголовок
    if (!in.atEnd())
        in.readLine();

    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList fields = MainWindow::parseCsvLine(line);

        // Дополняем поля до 22 пустыми строками
        while (fields.size() < 22)
            fields.append("");

        int place = fields[0].toInt();
        if (place <= 0)
        {
            ++skipped;
            continue;
        }

        // Пропускаем строки где фамилия пустая И имя пустое (Свободно)
        if (fields[1].isEmpty() && fields[2].isEmpty())
        {
            ++skipped;
            continue;
        }

        Mesto m(place, fields[1].toStdString(), fields[2].toStdString(), fields[3].toStdString(),
                fields[4].toStdString(), fields[5].toStdString(), fields[6].toStdString(), fields[7].toStdString(),
                fields[8].toStdString(), fields[9].toStdString(), fields[10].toStdString(), fields[11].toStdString(),
                fields[12].toStdString(), fields[13].toStdString(), fields[14].toStdString(), fields[15].toStdString(),
                fields[16].toStdString(), fields[17].toStdString(), fields[18].isEmpty() ? 0 : fields[18].toInt(),
                fields[19] == "true", fields[20] == "true", fields[21].toStdString());

        // Проверяем, существует ли уже запись с таким id
        auto existing = db->getMestoById(place);
        if (existing.has_value())
        {
            db->updateMesto(m);
            ++updated;
        }
        else
        {
            db->addMesto(m);
            ++imported;
        }
    }

    file.close();
    refreshTable();

    QMessageBox::information(
        this, "Импорт завершён",
        QString("Добавлено: %1\nОбновлено: %2\nПропущено: %3").arg(imported).arg(updated).arg(skipped));
}

void MainWindow::onTableDoubleClicked(int row, int /*column*/)
{
    int id = mestoTable->item(row, 0)->text().toInt();
    auto opt = db->getMestoById(id);
    if (!opt.has_value())
        return;

    MestoDialog dialog(opt.value(), this);
    dialog.setReadOnly(true);
    dialog.exec();
}

// ============================================================================
// Вспомогательный метод: разбор строки CSV с разделителем ';'
// ============================================================================

QStringList MainWindow::parseCsvLine(const QString &line)
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