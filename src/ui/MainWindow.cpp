// src/ui/MainWindow.cpp
#include "ui/MainWindow.h"
#include "application/SpotService.h"
#include "domain/Owner.h"
#include "domain/Spot.h"
#include "ui/SpotDialog.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>


// ============================================================================
// Конструктор / Деструктор
// ============================================================================

MainWindow::MainWindow(SpotService &spotService, QWidget *parent)
    : QMainWindow(parent), spotService(spotService), tabWidget(nullptr), spotTable(nullptr), searchEdit(nullptr),
      btnAdd(nullptr), btnEdit(nullptr), btnDelete(nullptr), btnImportCsv(nullptr), contextMenu(nullptr)
{
    setWindowTitle("Гаражный учёт");
    resize(1000, 650);
    setupUi();
    refreshTable();
}

MainWindow::~MainWindow() = default;

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

    spotTable = new QTableWidget(0, 8);
    spotTable->setHorizontalHeaderLabels(
        {"№", "Фамилия", "Имя", "Отчество", "Телефон", "Автомобиль", "Госномер", "Льготы"});
    spotTable->horizontalHeader()->setStretchLastSection(true);
    spotTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    spotTable->setSelectionMode(QAbstractItemView::SingleSelection);
    spotTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    spotTable->setAlternatingRowColors(true);
    spotTable->verticalHeader()->setVisible(false);
    spotTable->setContextMenuPolicy(Qt::CustomContextMenu);

    mainLayout->addWidget(spotTable);

    contextMenu = new QMenu(this);
    contextMenu->addAction("Редактировать", this, &MainWindow::onEditSpot);
    contextMenu->addAction("Удалить", this, &MainWindow::onDeleteSpot);

    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::onAddSpot);
    connect(btnEdit, &QPushButton::clicked, this, &MainWindow::onEditSpot);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onDeleteSpot);
    connect(btnImportCsv, &QPushButton::clicked, this, &MainWindow::onImportCsv);
    connect(spotTable, &QTableWidget::cellDoubleClicked, this, &MainWindow::onTableDoubleClicked);
    connect(spotTable, &QTableWidget::customContextMenuRequested, this, &MainWindow::onTableContextMenu);

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
// Заполнение таблицы
// ============================================================================

void MainWindow::refreshTable()
{
    auto all = spotService.getAllSpots();
    spotTable->setRowCount(static_cast<int>(all.size()));

    for (int row = 0; row < static_cast<int>(all.size()); ++row)
    {
        const Spot &spot = all[row];
        const Owner &o = spot.getOwner();

        spotTable->setItem(row, 0, new QTableWidgetItem(QString::number(spot.getId())));
        spotTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(o.getLastName())));
        spotTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(o.getFirstName())));
        spotTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(o.getMiddleName())));
        spotTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(o.getPhone1())));
        spotTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(o.getVehicleBrand())));
        spotTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(o.getVehiclePlate())));

        QString benefits;
        if (o.isPensioner())
            benefits += "П";
        if (o.isDisabled())
            benefits += (benefits.isEmpty() ? "И" : ",И");
        spotTable->setItem(row, 7, new QTableWidgetItem(benefits));
    }

    spotTable->resizeColumnsToContents();
    applyFilter();
}

// ============================================================================
// Фильтрация
// ============================================================================

void MainWindow::onSearchTextChanged(const QString &text)
{
    Q_UNUSED(text);
    applyFilter();
}

void MainWindow::applyFilter()
{
    QString filter = searchEdit->text().trimmed();
    for (int row = 0; row < spotTable->rowCount(); ++row)
    {
        bool match = filter.isEmpty();
        if (!match)
        {
            for (int col = 0; col < spotTable->columnCount(); ++col)
            {
                QTableWidgetItem *item = spotTable->item(row, col);
                if (item && item->text().contains(filter, Qt::CaseInsensitive))
                {
                    match = true;
                    break;
                }
            }
        }
        spotTable->setRowHidden(row, !match);
    }
}

// ============================================================================
// Контекстное меню
// ============================================================================

void MainWindow::onTableContextMenu(const QPoint &pos)
{
    QTableWidgetItem *item = spotTable->itemAt(pos);
    if (!item)
        return;

    spotTable->selectRow(item->row());
    contextMenu->popup(spotTable->viewport()->mapToGlobal(pos));
}

// ============================================================================
// Слоты
// ============================================================================

void MainWindow::onAddSpot()
{
    SpotDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted)
    {
        spotService.addOrUpdateSpot(dialog.getSpot());
        refreshTable();
    }
}

void MainWindow::onEditSpot()
{
    int row = spotTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Редактирование", "Выберите место для редактирования.");
        return;
    }

    int id = spotTable->item(row, 0)->text().toInt();
    auto opt = spotService.getSpot(id);
    if (!opt.has_value())
    {
        QMessageBox::warning(this, "Ошибка", "Запись не найдена.");
        return;
    }

    SpotDialog dialog(opt.value(), this);
    if (dialog.exec() == QDialog::Accepted)
    {
        spotService.addOrUpdateSpot(dialog.getSpot());
        refreshTable();
    }
}

void MainWindow::onDeleteSpot()
{
    int row = spotTable->currentRow();
    if (row < 0)
    {
        QMessageBox::information(this, "Удаление", "Выберите место для удаления.");
        return;
    }

    int id = spotTable->item(row, 0)->text().toInt();
    QString name = spotTable->item(row, 1)->text() + " " + spotTable->item(row, 2)->text();

    auto answer = QMessageBox::question(this, "Подтверждение", QString("Удалить место №%1 (%2)?").arg(id).arg(name),
                                        QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        spotService.removeSpot(id);
        refreshTable();
    }
}

void MainWindow::onImportCsv()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Выберите CSV-файл", "data", "CSV files (*.csv);;All files (*.*)");
    if (fileName.isEmpty())
        return;

    auto result = spotService.importFromCsv(fileName.toStdString());
    refreshTable();

    QMessageBox::information(this, "Импорт завершён",
                             QString("Добавлено: %1\nОбновлено: %2\nПропущено: %3")
                                 .arg(result.imported)
                                 .arg(result.updated)
                                 .arg(result.skipped));
}

void MainWindow::onTableDoubleClicked(int row, int /*column*/)
{
    int id = spotTable->item(row, 0)->text().toInt();
    auto opt = spotService.getSpot(id);
    if (!opt.has_value())
        return;

    SpotDialog dialog(opt.value(), this);
    dialog.setReadOnly(true);
    dialog.exec();
}

// ============================================================================
// Вспомогательный метод
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