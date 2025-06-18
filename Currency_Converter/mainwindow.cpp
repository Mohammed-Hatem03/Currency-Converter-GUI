
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->convertButton->setText("Convert");
    ui->amountInput->setPlaceholderText("Enter amount");
    ui->resultLabel->setText("Result will appear here");
    ui->resultLabel->setAlignment(Qt::AlignCenter);

    QMap<QString, QString> currencyNames = {
        {"EGP", "Egyptian Pound"},
        {"USD", "US Dollar"},
        {"EUR", "Euro"},
        {"GBP", "British Pound"},
        {"JPY", "Japanese Yen"},
        {"INR", "Indian Rupee"}
    };

    QStringList displayList;
    for (const QString &code : currencyNames.keys()) {
        displayList << QString("%1 (%2)").arg(currencyNames.value(code), code);
    }

    ui->fromCurrency->addItems(displayList);
    ui->toCurrency->addItems(displayList);

    connect(ui->convertButton, &QPushButton::clicked, this, &MainWindow::convertCurrency);
    connect(ui->resetButton, &QPushButton::clicked, this, &MainWindow::resetFields);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convertCurrency()
{
    QString fromText = ui->fromCurrency->currentText();
    QString toText = ui->toCurrency->currentText();

    QString from = fromText.section('(', 1, 1).section(')', 0, 0).trimmed();
    QString to = toText.section('(', 1, 1).section(')', 0, 0).trimmed();

    bool ok;
    double amount = ui->amountInput->text().toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid amount greater than 0.");
        ui->resultLabel->setText("Invalid input.");
        return;
    }

    QMap<QString, double> rates = {
        {"USD", 1.0},
        {"EUR", 0.9},
        {"GBP", 0.8},
        {"JPY", 110.0},
        {"INR", 75.0},
        {"EGP", 50.0}
    };

    if (!rates.contains(from) || !rates.contains(to)) {
        QMessageBox::warning(this, "Unsupported Currency", "Selected currencies are not supported.");
        ui->resultLabel->setText("Unsupported currency.");
        return;
    }

    if (from == to) {
        ui->resultLabel->setText(QString("%1 %2").arg(QString::number(amount, 'f', 2), toText.split(" ").first()));
        return;
    }

    double convertedAmount = amount * (rates[to] / rates[from]);
    ui->resultLabel->setText(QString("%1 %2").arg(QString::number(convertedAmount, 'f', 2), toText.split(" ").first()));
}

void MainWindow::resetFields()
{
    ui->amountInput->clear();
    ui->resultLabel->setText("Result will appear here");
    ui->fromCurrency->setCurrentIndex(0);
    ui->toCurrency->setCurrentIndex(0);
}
