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
#include "counts.h"

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
    log.setVerboseLevel(0);

    executeCommand();
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

        if (mDatabase.create(mConfig) == false)
        {
            // TODO: fail message!
            return;
        }
    }
    else if (mConfig.cmd == COMMAND_STATUS)
    {
        cout << "%%%%%%%%%% COMMAND STATUS %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        PlutoCLIPrint print;

        if (mConfig.showUnpaidScheduled > 0)
        {
            QList<Scheduled> toBePay = Counts::getScheduled(mDatabase);
            print.printScheduled(toBePay,mConfig.noFormat);
        }

        QList<Movement> mov = Counts::getMovements(mDatabase,
                                                   QDate(),
                                                   QDate(),
                                                   mConfig.account,
                                                   mConfig.workorder,
                                                   mConfig.category,
                                                   mConfig.payee);
        print.printMovements(mov,mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMAND_ADD_USER)
    {
        cout << "%%%%%%%%%% COMMAND ADD USER %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        // Create user
        if (!mDatabase.addUser(mConfig))
        {
            log.log(QString(PLUTOTOOL_USER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database....
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_TRANSACTION)
    {
        cout << "%%%%%%%%%% COMMAND ADD TRANSACTION %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        if (mDatabase.addTransaction(mConfig) == false)
        {
            log.log(QString(PLUTOTOOL_TRANSACTION_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database...
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_SCHEDULED)
    {
        cout << "%%%%%%%%%% COMMAND ADD SCHEDULED %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        // Create Scheduled
        if (!mDatabase.addScheduled(mConfig))
        {
            log.log(QString(PLUTOTOOL_SCHEDULED_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database...
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_ACCOUNT)
    {
        cout << "%%%%%%%%%% COMMAND ADD ACCOUNT %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        if (mDatabase.addAccount(mConfig) == false)
        {
            log.log(QString(PLUTOTOOL_ACCOUNT_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database...
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_ACCOUNTTYPE)
    {
        cout << "%%%%%%%%%% COMMAND ADD ACCOUNT TYPE %%%%%%%%%%" << endl;

         mDatabase.load(mConfig);
         if (mDatabase.addAccountType(mConfig) == false)
         {
             log.log(QString(PLUTOTOOL_ACCOUNTTYPE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
             return;
         }
        // Save the new database....
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_PAYEE)
    {
        cout << "%%%%%%%%%% COMMAND ADD PAYEE %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        if (mDatabase.addPayee(mConfig) == false)
        {
            log.log(QString(PLUTOTOOL_PAYEE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database....
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_PAYEETYPE)
    {
        cout << "%%%%%%%%%% COMMAND ADD PAYEE TYPE %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        if (mDatabase.addPayeeType(mConfig) == false)
        {
            log.log(QString(PLUTOTOOL_PAYEETYPE_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        // Save the new database....
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_ADD_WORKORDER)
    {
        cout << "%%%%%%%%%% COMMAND ADD WORKORDER %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        if (mDatabase.addWorkOrder(mConfig) == false)
        {
            log.log(QString(PLUTOTOOL_WORKORDER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
            return;
        }
        mDatabase.store(mConfig);
    }
    else if (mConfig.cmd == COMMAND_GET_ACCOUNTS)
    {
        //cout << "%%%%%%%%%% COMMAND GET ACCOUNTS %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        PlutoCLIPrint print;
        print.printAccounts(mDatabase.accounts(),mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMAND_GET_PAYEES)
    {
        //cout << "%%%%%%%%%% COMMAND GET PAYEES %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        PlutoCLIPrint print;
        print.printPayees(mDatabase.payees(),mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMADN_GET_CATEGORIES)
    {
        //cout << "%%%%%%%%%% COMMAND GET CATEGORIES %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        PlutoCLIPrint print;
        print.printCategories(mDatabase.categories(),mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMADN_GET_WORKORDERS)
    {
        //cout << "%%%%%%%%%% COMMAND GET WORKORDERS %%%%%%%%%%" << endl;

        mDatabase.load(mConfig);
        PlutoCLIPrint print;
        print.printWorkOrders(mDatabase.workorders(),mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMADN_GET_TRANSACTIONS)
    {
        mDatabase.load(mConfig);
        PlutoCLIPrint print;
        print.printTransactions(mDatabase.transaction(),mConfig.noFormat);
    }
    else if (mConfig.cmd == COMMAND_ERROR)
    {
        cout << "\r\nCommand NOT FOUND!" << endl;
    }
}
