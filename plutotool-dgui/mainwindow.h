#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();

    void on_actionAddTransaction_triggered();

    void updateTables (void);
    void updateSearchFields (void);

    void handleTransactionSearchButton();

private:
    void updatePayeesTable (void);
    void updateAccountsTable (void);

    void fillCategories (void);
    void fillAccounts (void);
    void fillWorkOrders (void);
    void fillPayees (void);
    void fillTypes (void);

    Ui::MainWindow *ui;

    Database mDatabase;
    QString mDatabaseFileName;
    bool mIsDatabaseOpen;
};
#endif // MAINWINDOW_H
