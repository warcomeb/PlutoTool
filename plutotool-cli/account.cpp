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

Account::Account ():
    mName(""),
    mNumber(""),
    mType(NULL),
    mActive(false),
    mNote("")
{
    setId(0); // Not valid Id!
}

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

QString Account::number (void)
{
    return mNumber;
}

AccountType Account::type (void)
{
    return mType;
}

bool Account::active (void)
{
    return mActive;
}

QString Account::code (void)
{
    return mCode;
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

bool Account::isValid (void)
{
    if ((mId > 0) && (!mName.isNull()) && (!mName.isEmpty()))
    {
        return true;
    }
    return false;
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

void Account::read (const QJsonObject &json, QMap<quint32,AccountType> types)
{
    if (json.contains("Code") && json["Code"].isString())
    {
        mCode = json["Code"].toString();
    }

    if (json.contains("Name") && json["Name"].isString())
    {
        mName = json["Name"].toString();
    }

    if (json.contains("Number") && json["Number"].isString())
    {
        mNumber = json["Number"].toString();
    }

    if (json.contains("AccountType") && json["AccountType"].isDouble())
    {
        mType = types[json["AccountType"].toInt()];
    }

    if (json.contains("Note") && json["Note"].isString())
    {
        mNote = json["Note"].toString();
    }

    if (json.contains("Active") && json["Active"].isBool())
    {
        mActive = json["Active"].toBool();
    }

    if (json.contains("Id") && json["Id"].isDouble())
    {
        mId = json["Id"].toInt();
    }
}
