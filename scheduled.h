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

#ifndef SCHEDULED_H
#define SCHEDULED_H

#include <QtGlobal>
#include <QString>
#include <QDate>

#include "transaction.h"
#include "category.h"
#include "workorder.h"
#include "payee.h"

class Scheduled
{
public:
    Scheduled ();
    Scheduled (Payee payee,
               QDate deadline,
               float amount,
               WorkOrder workorder,
               Category category);

    void setId (quint32 id);
    quint32 id (void);

    void setNote (QString note);
    QString note (void);

    void setPaid (bool paid);
    bool paid (void);

    //void setAmount (float amount);
    float amount (void);

    Payee payee (void);

    QDate deadline (void);

    Category category (void);

    WorkOrder workorder (void);

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json,
               QMap<quint32,Payee> payees,
               QMap<quint32,Category> categories,
               QMap<quint32,WorkOrder> workorders);

private:
    quint32   mId;

    Payee     mPayee;

    QDate     mDeadline;
    float     mAmount;

    WorkOrder mWorkOrder;

    Category  mCategory;

    bool      mPaid;

    QString   mNote;
};

#endif // SCHEDULED_H
