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
    Transaction();

private:
    quint32   mId;

    Account   mAccountFrom;
    Account   mAccountTo;

    Payee     mPayee;

    Type      mType;

    QDate     mDate;
    float     mAmount;

    WorkOrder mWorkOrder;

    // TODO: Subcategory

    bool      mChecked;

    User      mUserDo;
    User      mUserLog;
    QDate     mLogDate;

    QString   mNote;
};

#endif // TRANSACTION_H
