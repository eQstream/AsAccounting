#include "ui/MainWindow.h"
#include <QLabel>
#include <QTabWidget>
#include <QVBoxLayout>


// ============================================================================
// Конструктор / Деструктор
// ============================================================================

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), tabWidget(nullptr)
{
    setWindowTitle("Гаражный учёт");
    resize(900, 650);
    setupUi();
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
    QVBoxLayout *layout = new QVBoxLayout(tab);
    QLabel *label = new QLabel("Здесь будет учёт машиномест");
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
    return tab;
}

// ============================================================================
// Вкладка "Бухгалтерия"
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