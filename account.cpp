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
#include "account.h"

Account::Account (QString name, QString number, AccountType type, bool active = false):
    mName(name),
    mNumber(number),
    mType(type),
    mActive(active),
    mNote("")
{
    setId(0); // Not valid Id!
}

Account::Account (QString name, QString number, AccountType type, quint32 id, bool active = false):
    mName(name),
    mNumber(number),
    mType(type),
    mActive(active),
    mNote("")
{
    setId(id);
}

QString Account::name (void)
{
    return mName;
}

void Account::setId (quint32 id)
{
    mId = id;
    mCode = QString("A%1").arg(id, 5, 10, QLatin1Char('0'));
}

quint32 Account::id (void) const
{
    return mId;
}

void Account::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]          = (int)mId;
    o["Code"]        = mCode;
    o["Name"]        = mName;
    o["Number"]      = mNumber;
    o["AccountType"] = (int)mType.id();
    o["Active"]      = mActive;
    o["Note"]        = mNote;

    json.insert("Account", o);
}
