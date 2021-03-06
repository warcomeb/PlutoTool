#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>

#include "database.h"
#include "mainwindow.h"

namespace Ui {
class AddTransaction;
class MainWindow;
}

class AddTransaction : public QDialog
{
    Q_OBJECT

public:

    typedef enum _OperMode
    {
        ADD,
        EDIT,
        VIEW
    } OpenMode;

    explicit AddTransaction(OpenMode mode, Database* db, Ui::MainWindow* main, QWidget *parent = nullptr);
    ~AddTransaction();

private slots:
    void on_typeComboBox_currentIndexChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    void setAddView (void);

    void fillTypes (void);
    void fillCategories (void);
    void fillAccounts (void);
    void fillWorkOrders (void);
    void fillPayees (void);

    Ui::AddTransaction *ui;
    Database* mDatabase;
    Ui::MainWindow* mMain;
};

#endif // ADDTRANSACTION_H
