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

#ifndef DATABASE_H
#define DATABASE_H

#include <QMap>
#include <QtGlobal>
#include <QFile>

#include "config.h"

#include "user.h"
#include "workorder.h"
#include "account.h"
#include "accounttype.h"
#include "payee.h"
#include "payeetype.h"
#include "transaction.h"
#include "category.h"
#include "scheduled.h"

#include "plutodefault.h"

class Database
{
public:
    Database();

    bool isValid (void);

    bool create (Config config);
    bool load (Config config);
    bool store (Config config);

    bool addUser (Config config);
    bool addAccount (Config config);
    bool addAccountType (Config config);
    bool addScheduled (Config config);
    bool addTransaction (Config config);
    bool addWorkOrder (Config config);
    bool addPayeeType (Config config);
    bool addPayee (Config config);

    QMap<quint32,Account> accounts (void)
    {
        return mAccounts;
    };

    bool isAccountExist (quint32 id)
    {
        if (mAccounts.contains(id))
        {
            return true;
        }
        return false;
    };

    Account& getAccount (quint32 id)
    {
        return mAccounts[id];
    }

    QMap<quint32,WorkOrder> workorders (void)
    {
        return mWorkOrders;
    };

    WorkOrder& getWorkOrder (quint32 id)
    {
        return mWorkOrders[id];
    }

    QMap<quint32,Payee> payees (void)
    {
        return mPayees;
    };

    Payee& getPayee (quint32 id)
    {
        return mPayees[id];
    }

    QMap<quint32,Category> categories (void)
    {
        return mCategories;
    };

    Category& getCategory (quint32 id)
    {
        return mCategories[id];
    }

    QMap<quint32,Scheduled> scheduled (void)
    {
        return mScheduled;
    };

    QMap<quint32,Transaction> transaction (void)
    {
        return mTransactions;
    };

private:

    bool save (QFile *file);
    bool read (QFile* file);

    bool openDatabaseFile (Config config, QFile& db, QIODevice::OpenMode flags, bool checkReplace = false);
    void closeDatabaseFile (QFile& db);

    void readUsers (const QJsonObject &json);
    void readCategories (const QJsonObject &json);
    void readAccountTypes (const QJsonObject &json);
    void readAccounts (const QJsonObject &json);
    void readPayeeTypes (const QJsonObject &json);
    void readPayees (const QJsonObject &json);
    void readWorkOrders (const QJsonObject &json);
    void readTransactions (const QJsonObject &json);
    void readScheduled (const QJsonObject &json);

    void writeUsers (QJsonObject &json) const;
    void writeCategories (QJsonObject &json) const;
    void writeAccountTypes (QJsonObject &json) const;
    void writeAccounts (QJsonObject &json) const;
    void writePayeeTypes (QJsonObject &json) const;
    void writePayees (QJsonObject &json) const;
    void writeWorkOrders (QJsonObject &json) const;
    void writeTransactions (QJsonObject &json) const;
    void writeScheduled (QJsonObject &json) const;

    void createDefaultAccountType (void);
    void createDefaultPayeeType (void);
    void createDefaultCategory (void);

    PlutoDefault              mDefault;

    QMap<quint32,User>        mUsers;
    quint32                   mUserNextId;

    QMap<quint32,Category>    mCategories;
    quint32                   mCategoryNextId;

    QMap<quint32,WorkOrder>   mWorkOrders;
    quint32                   mWorkOrderNextId;

    QMap<quint32,AccountType> mAccountTypes;
    quint32                   mAccountTypeNextId;

    QMap<quint32,Account>     mAccounts;
    quint32                   mAccountNextId;

    QMap<quint32,PayeeType>   mPayeeTypes;
    quint32                   mPayeeTypeNextId;

    QMap<quint32,Payee>       mPayees;
    quint32                   mPayeeNextId;

    QMap<quint32,Transaction> mTransactions;
    quint32                   mTransactionNextId;

    QMap<quint32,Scheduled>   mScheduled;
    quint32                   mScheduledNextId;

    bool                      mIsValid;
};

#endif // DATABASE_H
