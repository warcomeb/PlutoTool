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
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QtGlobal>
#include <QString>
#include <QDate>

#include "account.h"
#include "payee.h"
#include "category.h"
#include "workorder.h"
#include "user.h"

class Transaction
{
public:

    enum Type
    {
        TYPE_INPUT   = 'i',
        TYPE_OUTPUT  = 'o',
        TYPE_NEUTRAL = 'n',
    };

    Transaction ();
    Transaction (Account from,
                 Account to,
                 Payee payee,
                 QDate date,
                 float amount,
                 Category category,
                 Type type,
                 WorkOrder workorder);

    void setId (quint32 id);
    quint32 id (void);

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json,
               QMap<quint32,Account> accounts,
               QMap<quint32,Payee> payees,
               QMap<quint32,Category> categories,
               QMap<quint32,WorkOrder> workorders);

private:
    quint32   mId;

    Account   mAccountFrom;
    Account   mAccountTo;

    Payee     mPayee;

    Type      mType;

    QDate     mDate;
    float     mAmount;

    WorkOrder mWorkOrder;

    Category  mCategory;

    bool      mChecked;

    //User      mUserDo;
    //User      mUserLog;
    QDate     mLogDate;

    QString   mNote;
};

#endif // TRANSACTION_H
