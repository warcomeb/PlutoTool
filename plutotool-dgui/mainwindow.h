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

    void on_actionAddTransaction_triggered();

private:
    void updateTables (void);
    void updatePayeesTable (void);
    void updateAccountsTable (void);


    Ui::MainWindow *ui;

    Database mDatabase;
};
#endif // MAINWINDOW_H
