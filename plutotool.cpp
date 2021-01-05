/*
 * This file is part of PlutoTool
 *
 * Authors:
 *   Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * PlutoTool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * PlutoTool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plutotool.h"
#include "metadata.h"

#include "utils/wlog.h"

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include <QString>
#include <QDate>
#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

PlutoTool::PlutoTool(Config config):
    mConfig(config)
{
    WLog& log = WLog::instance();
    // FIXME
    //log.setVerboseLevel(config.verboseLevel);
    log.setVerboseLevel(2);

    executeCommand();
}

User PlutoTool::createUser (quint32 id)
{
    string name, surname;
    cout << "Adding new user:" << endl;
    cout << "Insert name: ";
    getline(cin,name);
    cout << "Insert Surname: ";
    getline(cin,surname);

    User u = User(QString(name.c_str()),QString(surname.c_str()),id);
    return u;
}

Transaction PlutoTool::createTransaction (quint32 id)
{

}

void PlutoTool::createDefaultAccountType (void)
{
    WLog& log = WLog::instance();

    AccountType a = AccountType("Bank Account",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Wallet",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Credit Card",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Virtual Wallet",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Saving Account",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
}

void PlutoTool::createDefaultPayeeType (void)
{
    WLog& log = WLog::instance();

    PayeeType p = PayeeType("Undefined",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("People",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Bank",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Bar",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Shop",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Resturant",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Health",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Transport",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Utilities",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Mechanic",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);
}

void PlutoTool::createDefaultCategory (void)
{
    WLog& log = WLog::instance();

    Category c = Category("Undefined","Undefined",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Transfer","",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Salary",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Refunds",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Gift",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Electricity",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Gas",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Internet",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Water",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Garbage",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","PayTV",mCategoryNextId++); // Netflix, Disney+
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Home Needs","Domestic Worker",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    // ---------- Automobile
    c = Category("Automobile","Parking",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Maintenance",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Fuel",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Insurance",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Highway",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Tax",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Buy",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Rent",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Penalty",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);
}

void PlutoTool::executeCommand (void)
{
    WLog& log = WLog::instance();

    if (mConfig.cmd == COMMAND_LIST)
    {
        cout << "\r\nCommand list:\r\n";
        cout << "  LIST: this command," << endl;
        cout << "  INIT: initialize new database" << endl;
        cout << "  ADD-TRANSACTION: Add new transaction" << endl;
    }
    else if (mConfig.cmd == COMMAND_INIT)
    {
        cout << "%%%%%%%%%% COMMAND INIT %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (data.exists())
        {
            string reply;
            cout << "The database file just exists, would you replace? (y/n)" << endl;
            getline(cin,reply);
            if (reply == "n")
            {
                log.log(QString("FAIL open database file!"),LOG_VIP_INFORMATION);
                return;
            }
        }

        if (!data.open(QIODevice::WriteOnly))
        {
            //TODO: message
            log.log(QString("FAIL open database file!"),LOG_VIP_INFORMATION);
            return;
        }

        log.log(QString("Create first user..."),LOG_IMPORTANT_INFORMATION);
        mUserNextId = 1;
        User u = createUser(mUserNextId++);
        mUsers.insert(u.id(),u);
        log.log(QString("User %1 %2 (%3) has been added!").arg(u.name()).arg(u.surname()).arg(u.code()),LOG_MEDIUM_INFORMATION);

        log.log(QString("Create default categories..."),LOG_MEDIUM_INFORMATION);
        mCategoryNextId = 1;
        createDefaultCategory();

        log.log(QString("Create default workorder..."),LOG_MEDIUM_INFORMATION);
        mWorkOrderNextId = 1;
        WorkOrder w = WorkOrder();
        w.setId(mWorkOrderNextId++);
        mWorkOrders.insert(w.id(),w);
        log.log(QString("Work Order %1 (%2) has been added!").arg(w.name()).arg(w.code()),LOG_MEDIUM_INFORMATION);

        log.log(QString("Create default account type..."),LOG_MEDIUM_INFORMATION);
        mAccountTypeNextId = 1;
        createDefaultAccountType();

        mAccountNextId = 1;

        log.log(QString("Create default payee type..."),LOG_MEDIUM_INFORMATION);
        mPayeeTypeNextId = 1;
        createDefaultPayeeType();

        log.log(QString("Create default payee..."),LOG_MEDIUM_INFORMATION);
        mPayeeNextId = 1;
        Payee p = Payee(mPayeeTypes[1]);
        p.setId(mPayeeNextId++);
        mPayees.insert(p.id(),p);
        log.log(QString("Payee %1 (%2) has been added!").arg(p.name()).arg(p.code()),LOG_MEDIUM_INFORMATION);

        mTransactionNextId = 1;

        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        save(&data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_TRANSACTION)
    {
        cout << "%%%%%%%%%% COMMAND ADD TRANSACTION %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (!data.exists())
        {
            log.log(QString("The database doesn't exist!"),LOG_VIP_INFORMATION);
            return;
        }

        if (!data.open(QIODevice::ReadWrite))
        {
            //TODO: message
            log.log(QString("FAIL open database file!"),LOG_VIP_INFORMATION);
            return;
        }

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        // Create transaction
        Transaction t = createTransaction(mTransactionNextId++);
        mTransactions.insert(t.id(),t);
        log.log(QString("Transaction %1 has been added!").arg(t.id()),LOG_MEDIUM_INFORMATION);
        // Save the new database...
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        save(&data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ERROR)
    {
        cout << "\r\nCommand NOT FOUND!" << endl;
    }
}

void PlutoTool::readUsers (const QJsonObject &json)
{
    QJsonArray refs = json["Users"].toArray();
    for (int userIndex = 0; userIndex < refs.size(); ++userIndex)
    {
        QJsonObject userObject = refs[userIndex].toObject();
        User u;
        u.read(userObject["User"].toObject());
        mUsers.insert(u.id(),u);
    }

    QJsonValue::Type my = json["UserNextId"].type();
    if (json.contains("UserNextId") && json["UserNextId"].isDouble())
    {
        mUserNextId = json["UserNextId"].toInt();
    }
}

void PlutoTool::writeUsers (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (User u, mUsers)
    {
        QJsonObject o;
        u.write(o);
        refs.push_back(o);
    }
    json["Users"] = refs;
    json["UserNextId"] = (int)mUserNextId;
}

void PlutoTool::writeCategories (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Category c, mCategories)
    {
        QJsonObject o;
        c.write(o);
        refs.push_back(o);
    }
    json["Categories"] = refs;
    json["CategoryNextId"] = (int)mCategoryNextId;
}

void PlutoTool::writeAccountTypes (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (AccountType at, mAccountTypes)
    {
        QJsonObject o;
        at.write(o);
        refs.push_back(o);
    }
    json["AccountTypes"] = refs;
    json["AccountTypesNextId"] = (int)mAccountTypeNextId;
}

void PlutoTool::writeAccounts (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Account a, mAccounts)
    {
        QJsonObject o;
        a.write(o);
        refs.push_back(o);
    }
    json["Accounts"] = refs;
    json["AccountNextId"] = (int)mAccountNextId;
}

void PlutoTool::writeTransactions (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Transaction t, mTransactions)
    {
        QJsonObject o;
        t.write(o);
        refs.push_back(o);
    }
    json["Transaction"] = refs;
    json["TransactionNextId"] = (int)mTransactionNextId;
}

void PlutoTool::writePayeeTypes (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (PayeeType p, mPayeeTypes)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["PayeeTypes"] = refs;
    json["PayeeTypesNextId"] = (int)mPayeeTypeNextId;
}

void PlutoTool::writePayees (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Payee p, mPayees)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["Payees"] = refs;
    json["PayeesNextId"] = (int)mPayeeNextId;
}

void PlutoTool::writeWorkOrders (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (WorkOrder p, mWorkOrders)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["WorkOrders"] = refs;
    json["WorkOrderNextId"] = (int)mWorkOrderNextId;
}

bool PlutoTool::read (QFile* file)
{
    WLog& log = WLog::instance();

    QByteArray saveData = file->readAll();

    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject obj = loadDoc.object();

    log.log(QString("Read database: users information..."),LOG_MEDIUM_INFORMATION);
    readUsers(obj);

    return true;
}

bool PlutoTool::save (QFile* file)
{
    WLog& log = WLog::instance();

    QJsonObject obj;

    log.log(QString("Save database: write users information..."),LOG_MEDIUM_INFORMATION);
    writeUsers(obj);

    log.log(QString("Save database: write categories information..."),LOG_MEDIUM_INFORMATION);
    writeCategories(obj);

    log.log(QString("Save database: write accounts type information..."),LOG_MEDIUM_INFORMATION);
    writeAccountTypes(obj);

    log.log(QString("Save database: write accounts information..."),LOG_MEDIUM_INFORMATION);
    writeAccounts(obj);

    log.log(QString("Save database: write payees type information..."),LOG_MEDIUM_INFORMATION);
    writePayeeTypes(obj);

    log.log(QString("Save database: write payees information..."),LOG_MEDIUM_INFORMATION);
    writePayees(obj);

    log.log(QString("Save database: write work orders information..."),LOG_MEDIUM_INFORMATION);
    writeWorkOrders(obj);

    log.log(QString("Save database: write transactions information..."),LOG_MEDIUM_INFORMATION);
    writeTransactions(obj);

    QJsonDocument doc(obj);

    file->write(doc.toJson());
    return true;
}
