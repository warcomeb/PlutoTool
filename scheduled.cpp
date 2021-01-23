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

#include "scheduled.h"

Scheduled::Scheduled ():
    mPayee(),
    mDeadline(),
    mAmount(0.0),
    mWorkOrder(),
    mCategory(),
    mPaid(false),
    mNote("")
{
}

Scheduled::Scheduled (Payee payee,
                      QDate deadline,
                      float amount,
                      WorkOrder workorder,
                      Category category):
    mPayee(payee),
    mDeadline(deadline),
    mAmount(amount),
    mWorkOrder(workorder),
    mCategory(category),
    mPaid(false),
    mNote("")
{

}

void Scheduled::setId (quint32 id)
{
    mId = id;
}

quint32 Scheduled::id (void)
{
    return mId;
}

void Scheduled::setNote (QString note)
{
    mNote = note;
}

QString Scheduled::note (void)
{
    return mNote;
}

void Scheduled::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]          = (int)mId;
    o["Payee"]       = (int)mPayee.id();
    o["Amount"]      = mAmount;
    o["Category"]    = (int)mCategory.id();
    o["WorkOrder"]   = (int)mWorkOrder.id();
    o["Deadline"]    = mDeadline.toString("yyyy-MM-dd");
    o["Paid"]        = mPaid;
    o["Note"]        = mNote;

    json.insert("Scheduled", o);
}

void Scheduled::read (const QJsonObject &json,
                        QMap<quint32,Payee> payees,
                        QMap<quint32,Category> categories,
                        QMap<quint32,WorkOrder> workorders)
{
    if (json.contains("Id") && json["Id"].isDouble())
    {
        mId = json["Id"].toInt();
    }

    if (json.contains("Payee") && json["Payee"].isDouble())
    {
        mPayee = payees[json["Payee"].toInt()];
    }

    if (json.contains("Amount") && json["Amount"].isDouble())
    {
        mAmount = json["Amount"].toDouble();
    }

    if (json.contains("Category") && json["Category"].isDouble())
    {
        mCategory = categories[json["Category"].toInt()];
    }

    if (json.contains("WorkOrder") && json["WorkOrder"].isDouble())
    {
        mWorkOrder = workorders[json["WorkOrder"].toInt()];
    }

    if (json.contains("Deadline") && json["Deadline"].isString())
    {
        mDeadline = QDate::fromString(json["Deadline"].toString(),"yyyy-MM-dd");
    }

    if (json.contains("Note") && json["Note"].isString())
    {
        mNote = json["Note"].toString();
    }

    if (json.contains("Paid") && json["Paid"].isBool())
    {
        mPaid = json["Paid"].toBool();
    }
}
