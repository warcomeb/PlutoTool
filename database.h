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

class Database
{
public:
    Database();

    bool save (QFile *file);
    bool read (QFile* file);

    bool openDatabaseFile (QFile& db, QIODevice::OpenMode flags, bool checkReplace = false);
    void closeDatabaseFile (QFile& db);

private:
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
};

#endif // DATABASE_H
