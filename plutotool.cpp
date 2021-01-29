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

#include "plutocliprint.h"

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include "plutotoolreport.h"

#include <QString>
#include <QDate>
#include <QFile>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

PlutoTool::PlutoTool (Config config):
    mConfig(config)
{
    WLog& log = WLog::instance();
    // FIXME
    //log.setVerboseLevel(config.verboseLevel);
    log.setVerboseLevel(2);

    executeCommand();
}

bool PlutoTool::createUser (quint32 id, User& u)
{
    if ((!mConfig.uName.isNull()) && (!mConfig.uSurname.isNull()))
    {
        User my(mConfig.uName,mConfig.uSurname,id);
        u = my;
        return true;
    }
    return false;
}

bool PlutoTool::createAccount (quint32 id, Account& a)
{
    if ((!mConfig.aName.isNull()) && (!mConfig.aNumber.isNull()) && (mConfig.aType > 0))
    {
        if (mAccountTypes.contains(mConfig.aType))
        {
            Account my(mConfig.aName,mConfig.aNumber,mAccountTypes[mConfig.aType],id,true);
            a = my;
            return true;
        }
    }
    return false;
}

bool PlutoTool::createAccountType (quint32 id, AccountType& at)
{
    if (!mConfig.atName.isNull())
    {
        AccountType my(mConfig.atName,id);
        at = my;

        if (!mConfig.atDescription.isNull())
        {
            at.setDescription(mConfig.atDescription);
        }
        return true;
    }
    return false;
}

bool PlutoTool::createPayee (quint32 id, Payee& p)
{
    if ((!mConfig.pName.isNull()) && (mConfig.pType > 0))
    {
        if (mPayeeTypes.contains(mConfig.pType))
        {
            Payee my(mConfig.pName,mPayeeTypes[mConfig.pType],id);
            p = my;
            return true;
        }
    }
    return false;
}

bool PlutoTool::createPayeeType (quint32 id, PayeeType& pt)
{
    if (!mConfig.ptName.isNull())
    {
        PayeeType my(mConfig.ptName,id);
        pt = my;

        if (!mConfig.ptDescription.isNull())
        {
            pt.setDescription(mConfig.ptDescription);
        }
        return true;
    }
    return false;
}

bool PlutoTool::createWorkOrder (quint32 id, WorkOrder& w)
{
    if (!mConfig.wName.isNull() && !mConfig.wEnd.isNull())
    {
        QDate dStart;
        QDate dEnd;

        dEnd = QDate::fromString(mConfig.wEnd,"yyyy-MM-dd");
        if (!dEnd.isValid()) return false;

        if (mConfig.wStart.isNull())
        {
            dStart = QDate::currentDate();
        }
        else
        {
            dStart = QDate::fromString(mConfig.wStart,"yyyy-MM-dd");
            if (!dStart.isValid()) return false;
        }

        WorkOrder my(mConfig.wName,dStart,dEnd,id);
        w = my;

        if (!mConfig.wDescription.isNull())
        {
            w.setDescription(mConfig.wDescription);
        }
        return true;
    }
    return false;
}

bool PlutoTool::createTransaction (quint32 id, Transaction& t)
{
    // Check if all values are valid
    if ((mConfig.tAmount != 0.0f) &&
        (mConfig.tType != Transaction::TYPE_ERROR) &&
        (((mConfig.tType == Transaction::TYPE_INPUT) && (mConfig.tAccountTo > 0)) ||
         ((mConfig.tType == Transaction::TYPE_OUTPUT) && (mConfig.tAccountFrom > 0)) ||
         ((mConfig.tType == Transaction::TYPE_NEUTRAL) && (mConfig.tAccountTo > 0) && (mConfig.tAccountFrom > 0))) &&
        /*(mConfig.tPayee > 0) &&*/ (mConfig.tType > 0) && /*(mConfig.tWorkorder > 0) &&*/ (mConfig.tCategory > 0))
    {
        Account   aTo;
        Account   aFrom;
        Payee     p;
        WorkOrder w;
        Category  c;
        QDate     d;

        if ((mConfig.tType != Transaction::TYPE_INPUT)  &&
            (mConfig.tType != Transaction::TYPE_OUTPUT) &&
            (mConfig.tType != Transaction::TYPE_NEUTRAL))
        {
            return false;
        }

        if (mConfig.tAccountTo > 0)
        {
            if (mAccounts.contains(mConfig.tAccountTo))
            {
                aTo = mAccounts[mConfig.tAccountTo];
            }
            else
            {
                return false;
            }
        }

        if (mConfig.tAccountFrom > 0)
        {
            if (mAccounts.contains(mConfig.tAccountFrom))
            {
                aFrom = mAccounts[mConfig.tAccountFrom];
            }
            else
            {
                return false;
            }
        }

        // Category
        if (mConfig.tCategory > 0)
        {
            if (mCategories.contains(mConfig.tCategory))
            {
                c = mCategories[mConfig.tCategory];
            }
            else
            {
                return false;
            }
        }

        if (mConfig.tDate.isNull())
        {
            d = QDate::currentDate();
        }
        else
        {
            d = QDate::fromString(mConfig.tDate,"yyyy-MM-dd");
            if (!d.isValid()) return false;
        }

        if (mConfig.tPayee > 0)
        {
            if (mPayees.contains(mConfig.tPayee))
            {
                p = mPayees[mConfig.tPayee];
            }
            else
            {
                return false;
            }
        }
        else
        {
            p = mPayees[1]; // Undefined
        }

        // WorkOrder
        if (mConfig.tWorkorder > 0)
        {
            if (mWorkOrders.contains(mConfig.tWorkorder))
            {
                w = mWorkOrders[mConfig.tWorkorder];
            }
            else
            {
                return false;
            }
        }
        else
        {
            w = mWorkOrders[1]; // Undefined
        }

        // Create object!
        Transaction my(aFrom,aTo,p,d,mConfig.tAmount,c,(Transaction::Type)mConfig.tType,w);
        my.setId(id);
        t = my;
        return true;
    }
    return false;
}

bool PlutoTool::createScheduled (quint32 id, Scheduled &s)
{
    // Check if all values are valid
    if ((mConfig.sAmount != 0.0f) &&
        (mConfig.sPayee > 0) &&
        (!mConfig.sDeadline.isNull()) &&
        (mConfig.sCategory > 0))
    {
        Payee     p;
        WorkOrder w;
        Category  c;
        QDate     d;

        if (mCategories.contains(mConfig.sCategory))
        {
            c = mCategories[mConfig.sCategory];
        }
        else
        {
            return false;
        }

        d = QDate::fromString(mConfig.sDeadline,"yyyy-MM-dd");
        if (!d.isValid())
        {
            return false;
        }

        if (mPayees.contains(mConfig.sPayee))
        {
            p = mPayees[mConfig.sPayee];
        }
        else
        {
            return false;
        }

        // WorkOrder
        if (mWorkOrders.contains(mConfig.sWorkorder))
        {
            w = mWorkOrders[mConfig.sWorkorder];
        }
        else
        {
            return false;
        }

        // Create object!
        Scheduled my(p,d,mConfig.sAmount,w,c);
        my.setId(id);
        s = my;
        return true;
    }
    return false;
}

void PlutoTool::executeCommand (void)
{
    WLog& log = WLog::instance();

    if (mConfig.cmd == COMMAND_LIST)
    {
        cout << "\r\nCommand list:\r\n";
        cout << "  LIST: this command," << endl;
        cout << "  INIT: initialize new database" << endl;
        cout << "  ADD-ACCOUNT: Add new account" << endl;
        cout << "  ADD-TRANSACTION: Add new transaction" << endl;
        cout << "  GET-ACCOUNT: List of all accounts" << endl;
    }
    else if (mConfig.cmd == COMMAND_INIT)
    {
        cout << "%%%%%%%%%% COMMAND INIT %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!

        log.log(QString("Create first user..."),LOG_IMPORTANT_INFORMATION);
        mUserNextId = 1;
        User u;
        if (!createUser(mUserNextId++,u))
        {
            log.log(QString(PLUTOTOOL_USER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        createUser(mUserNextId,u);
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

        mScheduledNextId = 1;

        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        save(&data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_STATUS)
    {
        cout << "%%%%%%%%%% COMMAND STATUS %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        QList<Scheduled> toBePay;
        foreach (Scheduled s, mScheduled)
        {
            if (s.paid() == false)
            {
                toBePay.append(s);
            }
        }
        PlutoCLIPrint print;
        print.printScheduled(toBePay);
    }
    else if (mConfig.cmd == COMMAND_ADD_USER)
    {
        cout << "%%%%%%%%%% COMMAND ADD USER %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create user
        User u;
        if (!createUser(mUserNextId++,u))
        {
            log.log(QString(PLUTOTOOL_USER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mUsers.insert(u.id(),u);
        log.log(QString("User %1 %2 (%3) has been added!").arg(u.name()).arg(u.surname()).arg(u.code()),LOG_MEDIUM_INFORMATION);

        // Save the new database....
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_TRANSACTION)
    {
        cout << "%%%%%%%%%% COMMAND ADD TRANSACTION %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create transaction
        Transaction t;
        if (!createTransaction(mTransactionNextId++,t))
        {
            log.log(QString(PLUTOTOOL_TRANSACTION_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mTransactions.insert(t.id(),t);
        log.log(QString("Transaction %1 has been added!").arg(t.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database...
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_SCHEDULED)
    {
        cout << "%%%%%%%%%% COMMAND ADD SCHEDULED %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create Scheduled
        Scheduled s;
        if (!createScheduled(mScheduledNextId++,s))
        {
            log.log(QString(PLUTOTOOL_SCHEDULED_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mScheduled.insert(s.id(),s);
        log.log(QString("Scheduled %1 has been added!").arg(s.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database...
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_ACCOUNT)
    {
        cout << "%%%%%%%%%% COMMAND ADD ACCOUNT %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create accout
        Account a;
        if (!createAccount(mAccountNextId++,a))
        {
            log.log(QString(PLUTOTOOL_ACCOUNT_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mAccounts.insert(a.id(),a);
        log.log(QString("Account %1 has been added!").arg(a.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database...
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_ACCOUNTTYPE)
    {
        cout << "%%%%%%%%%% COMMAND ADD ACCOUNT TYPE %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create payee
        AccountType at;
        if (!createAccountType(mAccountTypeNextId++,at))
        {
            log.log(QString(PLUTOTOOL_ACCOUNTTYPE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mAccountTypes.insert(at.id(),at);
        log.log(QString("Account Type %1 has been added!").arg(at.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database....
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_PAYEE)
    {
        cout << "%%%%%%%%%% COMMAND ADD PAYEE %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create payee
        Payee p;
        if (!createPayee(mPayeeNextId++,p))
        {
            log.log(QString(PLUTOTOOL_PAYEE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mPayees.insert(p.id(),p);
        log.log(QString("Payee %1 (%2) has been added!").arg(p.id()).arg(p.code()),LOG_MEDIUM_INFORMATION);

        // Save the new database....
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_PAYEETYPE)
    {
        cout << "%%%%%%%%%% COMMAND ADD PAYEE TYPE %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create payee
        PayeeType pt;
        if (!createPayeeType(mPayeeTypeNextId++,pt))
        {
            log.log(QString(PLUTOTOOL_PAYEETYPE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mPayeeTypes.insert(pt.id(),pt);
        log.log(QString("Payee Type %1 has been added!").arg(pt.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database....
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_ADD_WORKORDER)
    {
        cout << "%%%%%%%%%% COMMAND ADD WORKORDER %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (openDatabaseFile(data,QIODevice::ReadOnly) == false) return; // FAIL!

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        closeDatabaseFile(data);

        // Create workorder
        WorkOrder w;
        if (!createWorkOrder(mWorkOrderNextId++,w))
        {
            log.log(QString(PLUTOTOOL_WORKORDER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mWorkOrders.insert(w.id(),w);
        log.log(QString("WorkOrder %1 has been added!").arg(w.id()),LOG_MEDIUM_INFORMATION);

        // Save the new database....
        log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
        if (openDatabaseFile(data,QIODevice::WriteOnly) == false) return; // FAIL!
        save(&data);
        closeDatabaseFile(data);
        log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);
    }
    else if (mConfig.cmd == COMMAND_GET_ACCOUNTS)
    {
        cout << "%%%%%%%%%% COMMAND GET ACCOUNTS %%%%%%%%%%" << endl;

        log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
        QFile data(mConfig.database);
        if (!data.exists())
        {
            log.log(QString("The database doesn't exist!"),LOG_VIP_INFORMATION);
            return;
        }

        if (!data.open(QIODevice::ReadOnly))
        {
            //TODO: message
            log.log(QString("FAIL open database file!"),LOG_VIP_INFORMATION);
            return;
        }

        // Read current database status...
        log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
        read(&data);
        // TODO
    }
    else if (mConfig.cmd == COMMAND_ERROR)
    {
        cout << "\r\nCommand NOT FOUND!" << endl;
    }
}
