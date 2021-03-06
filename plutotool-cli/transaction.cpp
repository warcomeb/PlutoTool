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
#include "transaction.h"

Transaction::Transaction ():
    mAccountFrom(),
    mAccountTo(),
    mPayee(),
    mType(),
    mDate(),
    mAmount(0.0),
    mWorkOrder(),
    mCategory()
{

}

Transaction::Transaction (Account from,
                          Account to,
                          Payee payee,
                          QDate date,
                          float amount,
                          Category category,
                          Type type,
                          WorkOrder workorder):
    mAccountFrom(from),
    mAccountTo(to),
    mPayee(payee),
    mType(type),
    mDate(date),
    mAmount(amount),
    mWorkOrder(workorder),
    mCategory(category)
{

}

void Transaction::setId (quint32 id)
{
    mId = id;
}

quint32 Transaction::id (void)
{
    return mId;
}

Payee Transaction::payee (void)
{
    return mPayee;
}

QDate Transaction::date (void)
{
    return mDate;
}

Category Transaction::category (void)
{
    return mCategory;
}

WorkOrder Transaction::workorder (void)
{
    return mWorkOrder;
}

Account Transaction::accoutTo (void)
{
    return mAccountTo;
}

Account Transaction::accoutFrom (void)
{
    return mAccountFrom;
}

float Transaction::amount (void)
{
    return mAmount;
}

Transaction::Type Transaction::type (void)
{
    return mType;
}

void Transaction::setNote(QString note)
{
    mNote = note;
}

QString Transaction::note()
{
    return mNote;
}

void Transaction::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]          = (int)mId;
    o["AccountFrom"] = (int)mAccountFrom.id();
    o["AccountTo"]   = (int)mAccountTo.id();
    o["Payee"]       = (int)mPayee.id();
    o["Amount"]      = mAmount;
    o["Type"]        = mType;
    o["Category"]    = (int)mCategory.id();
    o["WorkOrder"]   = (int)mWorkOrder.id();
    o["Date"]        = mDate.toString("yyyy-MM-dd");
    o["Checked"]     = mChecked;
    o["Note"]        = mNote;

    json.insert("Transaction", o);
}

void Transaction::read (const QJsonObject &json,
                        QMap<quint32,Account> accounts,
                        QMap<quint32,Payee> payees,
                        QMap<quint32,Category> categories,
                        QMap<quint32,WorkOrder> workorders)
{
    if (json.contains("Id") && json["Id"].isDouble())
    {
        mId = json["Id"].toInt();
    }

    if (json.contains("AccountFrom") && json["AccountFrom"].isDouble())
    {
        mAccountFrom = accounts[json["AccountFrom"].toInt()];
    }

    if (json.contains("AccountTo") && json["AccountTo"].isDouble())
    {
        mAccountTo = accounts[json["AccountTo"].toInt()];
    }

    if (json.contains("Payee") && json["Payee"].isDouble())
    {
        mPayee = payees[json["Payee"].toInt()];
    }

    if (json.contains("Amount") && json["Amount"].isDouble())
    {
        mAmount = json["Amount"].toDouble();
    }

    if (json.contains("Type") && json["Type"].isDouble())
    {
        mType = (Transaction::Type)json["Type"].toInt();
    }

    if (json.contains("Category") && json["Category"].isDouble())
    {
        mCategory = categories[json["Category"].toInt()];
    }

    if (json.contains("WorkOrder") && json["WorkOrder"].isDouble())
    {
        mWorkOrder = workorders[json["WorkOrder"].toInt()];
    }

    if (json.contains("Date") && json["Date"].isString())
    {
        mDate = QDate::fromString(json["Date"].toString(),"yyyy-MM-dd");
    }

    if (json.contains("Note") && json["Note"].isString())
    {
        mNote = json["Note"].toString();
    }

    if (json.contains("Checked") && json["Checked"].isBool())
    {
        mChecked = json["Checked"].toBool();
    }
}
