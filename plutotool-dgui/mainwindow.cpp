#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addtransaction.h"

#include "movement.h"
#include "counts.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mDatabaseFileName("")
    , mIsDatabaseOpen(false)
{
    ui->setupUi(this);

    // Transaction tab
    ui->searchTransactionPushButton->setEnabled(false);
    ui->endDateEdit->setDate(QDate::currentDate());
    ui->movementsTableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
    // Chose file...
//    mDatabaseFileName = QFileDialog::getOpenFileName(this,
//        tr("Open Database"), "/home", tr("Database Files (*.json)"));
    mDatabaseFileName = "/Users/warcomeb/Projects/WARCOMEB/home-balance/GIAMMATEAM_BCK.json";

    if (mDatabaseFileName.isEmpty()) return;

    Config c = {
        .database = mDatabaseFileName,
        .replace = false
    };
    if (mDatabase.load(c))
    {
        mIsDatabaseOpen = true;
        ui->statusbar->showMessage("Database correctly opened!",2000);
        // FIXME: update all tables...
        updateTables();
        updateSearchFields();
    }
    else
    {
        mIsDatabaseOpen = false;
        ui->statusbar->showMessage("Fail open database.",2000);
    }
}


void MainWindow::on_actionSave_triggered()
{
    qDebug() << "MainWindow::on_actionSave_triggered()";
    if (mIsDatabaseOpen == true)
    {
        Config c = {
            .database = "/Users/warcomeb/Projects/WARCOMEB/home-balance/GIAMMATEAM_BCK.json",
    //        .database = fileName,
            .replace = false
        };
        if (mDatabase.store(c))
        {
            ui->statusbar->showMessage("Database correctly saved!",2000);
        }
        else
        {
            ui->statusbar->showMessage("Fail save database.",2000);
        }
    }
    else
    {
        ui->statusbar->showMessage("No opened database to save.",2000);
    }

}

void MainWindow::updateTables (void)
{
    updatePayeesTable();
    updateAccountsTable();
}

void MainWindow::updateSearchFields (void)
{
    fillCategories();
    fillPayees();
    fillWorkOrders();
    fillAccounts();
    fillTypes();

    ui->searchTransactionPushButton->setEnabled(true);
    // Connect button signal to appropriate slot
    connect(ui->searchTransactionPushButton, &QPushButton::released,
            this,&MainWindow::handleTransactionSearchButton);
}

void MainWindow::handleTransactionSearchButton (void)
{
    qDebug() << "MainWindow::handleTransactionSearchButton()";
    Config c;

    c.amountMin = (float)ui->amountMinSpinBox->value();
    c.amountMin = (float)ui->amountMaxSpinBox->value();

    c.dateStart = QDate::fromString(ui->startDateEdit->text(),"dd.MM.yyyy").toString("yyyy-MM-dd");
    c.dateEnd   = QDate::fromString(ui->endDateEdit->text(),"dd.MM.yyyy").toString("yyyy-MM-dd");

    c.account   = (quint32)ui->accountComboBox->currentData().toInt();
    c.payee     = (quint32)ui->payeeComboBox->currentData().toInt();
    c.workorder = (quint32)ui->workorderComboBox->currentData().toInt();
    c.category  = (quint32)ui->categoryComboBox->currentData().toInt();

    QList<Movement> mov = Counts::getMovements(mDatabase,
                                               QDate::fromString(c.dateStart,"yyyy-MM-dd"),
                                               QDate::fromString(c.dateEnd,"yyyy-MM-dd"),
                                               c.account,
                                               c.workorder,
                                               c.category,
                                               c.payee);
    qDebug() << "MainWindow::handleTransactionSearchButton() - Found: " << mov.size();

    // Clear rows and total!
    ui->movementsTableWidget->setRowCount(0);
    ui->totalTextEdit->setPlainText(tr("€ %1").arg(0.0f,0,'f',2));

    if (mov.size() == 0)
    {
        ui->statusbar->showMessage("No transactions founds",2000);
        return;
    }
    ui->statusbar->showMessage("Found " + QString::number(mov.size()) + " transactions.",2000);

    int row = 0;
    float total = 0.0f;
    foreach(Movement m, mov)
    {
        ui->movementsTableWidget->insertRow(row);
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(m.date().toString("dd.MM.yyyy")));
            ui->movementsTableWidget->setItem(row, 0, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(m.amount(),0,'f',2));
            ui->movementsTableWidget->setItem(row, 1, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(m.account().name()));
            ui->movementsTableWidget->setItem(row, 2, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(m.payee().name()));
            ui->movementsTableWidget->setItem(row, 3, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(m.category().completeName()));
            ui->movementsTableWidget->setItem(row, 4, newItem);

        newItem = new QTableWidgetItem(tr("%1").arg(m.workorder().name()));
            ui->movementsTableWidget->setItem(row, 5, newItem);

        row++;

        total += (float)m.amount();
    }
    ui->movementsTableWidget->resizeColumnsToContents();

    ui->totalTextEdit->setPlainText(tr("€ %1").arg(total,0,'f',2));
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

void MainWindow::fillCategories (void)
{
    QMap<quint32,Category> c = mDatabase.categories();
    QList<Category> lc = Category::map2list(c);

    ui->categoryComboBox->clear();
    ui->categoryComboBox->addItem("",0);
    for (int i = 0; i < lc.size(); i++)
    {
        ui->categoryComboBox->addItem(lc.at(i).completeName(),lc.at(i).id());
    }
}

void MainWindow::fillAccounts (void)
{
    QMap<quint32,Account> a = mDatabase.accounts();
    QList<Account> la = Account::map2list(a);

    ui->accountComboBox->clear();
    ui->accountComboBox->addItem("",0);
    for (int i = 0; i < la.size(); i++)
    {
        ui->accountComboBox->addItem(la.at(i).name(),la.at(i).id());
    }
}

void MainWindow::fillWorkOrders (void)
{
    QMap<quint32,WorkOrder> w = mDatabase.workorders();
    QList<WorkOrder> lw = WorkOrder::map2list(w);

    ui->workorderComboBox->clear();
    ui->workorderComboBox->addItem("",0);
    for (int i = 0; i < lw.size(); i++)
    {
        ui->workorderComboBox->addItem(lw.at(i).name(),lw.at(i).id());
    }
}

void MainWindow::fillPayees (void)
{
    QMap<quint32,Payee> p = mDatabase.payees();
    QList<Payee> lp = Payee::map2list(p);

    ui->payeeComboBox->clear();
    ui->payeeComboBox->addItem("",0);
    for (int i = 0; i < lp.size(); i++)
    {
        ui->payeeComboBox->addItem(lp.at(i).name(),lp.at(i).id());
    }
}

void MainWindow::fillTypes (void)
{
    ui->typeComboBox->clear();
    ui->typeComboBox->addItem("",'-');
    ui->typeComboBox->addItem("Neutral",'n');
    ui->typeComboBox->addItem("Input",'i');
    ui->typeComboBox->addItem("Output",'o');
}

void MainWindow::on_actionAddTransaction_triggered()
{
    if (mDatabase.isValid())
    {
        AddTransaction *addTransaction = new AddTransaction(AddTransaction::OpenMode::ADD,&mDatabase,ui); //use a pointer and then create the object and allocate memory with new
        addTransaction->show();
    }
    else
    {
        ui->statusbar->showMessage("No database opened!",2000);
    }
}
