#include "addtransaction.h"
#include "ui_addtransaction.h"

AddTransaction::AddTransaction(AddTransaction::OpenMode mode, Database *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransaction),
    mDatabase(db)
{
    ui->setupUi(this);



    if (mode == AddTransaction::OpenMode::ADD)
    {
        setAddView();
    }
}

AddTransaction::~AddTransaction()
{
    delete ui;
}

void AddTransaction::setAddView (void)
{
//        ui->setWindowTitle("Add new transaction");

    ui->idLineEdit->setReadOnly(true);
    ui->idLineEdit->setText("0");

    ui->dateEdit->setDate(QDate::currentDate());

    fillTypes();
    fillCategories();
    fillAccounts();
    fillWorkOrders();
    fillPayees();
}

void AddTransaction::fillTypes (void)
{
    ui->typeComboBox->clear();
    ui->typeComboBox->addItem("Neutral",'n');
    ui->typeComboBox->addItem("Input",'i');
    ui->typeComboBox->addItem("Output",'o');
}

void AddTransaction::fillCategories (void)
{
    QMap<quint32,Category> c = mDatabase->categories();
    QList<Category> lc = Category::map2list(c);

    ui->categoryComboBox->clear();
    for (int i = 0; i < lc.size(); i++)
    {
        ui->categoryComboBox->addItem(lc.at(i).completeName(),lc.at(i).id());
    }
}

void AddTransaction::fillAccounts (void)
{
    QMap<quint32,Account> a = mDatabase->accounts();
    QList<Account> la = Account::map2list(a);

    ui->accountToComboBox->clear();
    ui->accountFromComboBox->clear();
    for (int i = 0; i < la.size(); i++)
    {
        ui->accountToComboBox->addItem(la.at(i).name(),la.at(i).id());
        ui->accountFromComboBox->addItem(la.at(i).name(),la.at(i).id());
    }
}

void AddTransaction::fillWorkOrders (void)
{
    QMap<quint32,WorkOrder> w = mDatabase->workorders();
    QList<WorkOrder> lw = WorkOrder::map2list(w);

    ui->workorderComboBox->clear();
    for (int i = 0; i < lw.size(); i++)
    {
        ui->workorderComboBox->addItem(lw.at(i).name(),lw.at(i).id());
    }
}

void AddTransaction::fillPayees (void)
{
    QMap<quint32,Payee> p = mDatabase->payees();
    QList<Payee> lp = Payee::map2list(p);

    ui->payeeComboBox->clear();
    for (int i = 0; i < lp.size(); i++)
    {
        ui->payeeComboBox->addItem(lp.at(i).name(),lp.at(i).id());
    }
}

void AddTransaction::on_typeComboBox_currentIndexChanged (const QString &arg1)
{
    if (arg1 == "Neutral")
    {
        ui->accountToComboBox->setEnabled(true);
        ui->accountFromComboBox->setEnabled(true);
    }
    else if (arg1 == "Input")
    {
        ui->accountToComboBox->setEnabled(true);
        ui->accountFromComboBox->setEnabled(false);
    }
    else // Output
    {
        ui->accountToComboBox->setEnabled(false);
        ui->accountFromComboBox->setEnabled(true);
    }
}

void AddTransaction::on_buttonBox_accepted()
{
    qDebug() << "AddTransaction::on_buttonBox_accepted()";
    Config c;

    if (ui->amountEdit->value() > 0)
    {
        // FIX DATE Conversion!!!
        c.tDate = QDate::fromString(ui->dateEdit->text(),"dd.MM.yyyy").toString("yyyy-MM-dd");
        c.tAmount = (float)ui->amountEdit->value();
        c.tType = (quint32)ui->typeComboBox->currentData().toInt();

        c.tCategory = (quint32)ui->categoryComboBox->currentData().toInt();

        c.tAccountTo = (quint32)ui->accountToComboBox->currentData().toInt();
        c.tAccountFrom = (quint32)ui->accountFromComboBox->currentData().toInt();

        c.tPayee = (quint32)ui->payeeComboBox->currentData().toInt();

        c.tWorkorder = (quint32)ui->workorderComboBox->currentData().toInt();

        c.tNote = ui->noteTextEdit->toPlainText();

        if (mDatabase->addTransaction(c) == true)
        {
            qDebug() << "AddTransaction::on_buttonBox_accepted() - Added";
        }
        else
        {
            qDebug() << "AddTransaction::on_buttonBox_accepted() - Fail";
        }
    }
    else
    {

    }
}
