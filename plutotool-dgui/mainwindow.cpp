#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtransaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    // FIXME: chose file...
    Config c = {
        .database = "/Users/warcomeb/Projects/WARCOMEB/home-balance/GIAMMATEAM_BCK.json",
        .replace = false
    };
    if (mDatabase.load(c))
    {
        ui->statusbar->showMessage("Database correctly opened!",2000);
        // FIXME: update all tables...
        updateTables();
    }
    else
    {
        ui->statusbar->showMessage("Fail open database.",2000);
    }
}

void MainWindow::updateTables (void)
{
    updatePayeesTable();
    updateAccountsTable();
}

void MainWindow::updatePayeesTable (void)
{
    QMap<quint32,Payee> payees = mDatabase.payees();

    //ui->payeeTableWidget->clear();
    // FIXME: add header!
    int row = 0;
    foreach (Payee p, payees)
    {
        ui->payeeTableWidget->insertRow(row);
        qDebug() << "updatePayeesTable > Print row element no." << row;
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(QString::number(p.id())));
            ui->payeeTableWidget->setItem(row, 0, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(p.name()));
            ui->payeeTableWidget->setItem(row, 1, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(p.type().name()));
            ui->payeeTableWidget->setItem(row, 2, newItem);

        row++;
    }
}

void MainWindow::updateAccountsTable (void)
{
    QMap<quint32,Account> accounts = mDatabase.accounts();

    //ui->accountsTableWidget->clear();
    // FIXME: add header!
    int row = 0;
    foreach (Account a, accounts)
    {
        ui->accountsTableWidget->insertRow(row);
        qDebug() << "updateAccountsTable > Print row element no." << row;
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(QString::number(a.id())));
            ui->accountsTableWidget->setItem(row, 0, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(a.name()));
            ui->accountsTableWidget->setItem(row, 1, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(a.number()));
            ui->accountsTableWidget->setItem(row, 2, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(a.type().name()));
            ui->accountsTableWidget->setItem(row, 3, newItem);

        row++;
    }
}

void MainWindow::on_actionAddTransaction_triggered()
{
    if (mDatabase.isValid())
    {
        AddTransaction *addTransaction = new AddTransaction(AddTransaction::OpenMode::ADD,&mDatabase); //use a pointer and then create the object and allocate memory with new
        addTransaction->show();
    }
    else
    {
        ui->statusbar->showMessage("No database opened!",2000);
    }
}
