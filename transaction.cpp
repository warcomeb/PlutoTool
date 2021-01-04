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

    json.insert("Account", o);
}
