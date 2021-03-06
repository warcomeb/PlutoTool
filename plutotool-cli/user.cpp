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
#include "user.h"

User::User ():
    mName(""),
    mSurname("")
{
    mUsername = "";
    setId(0);
}

User::User (QString name, QString surname):
    mName(name),
    mSurname(surname)
{
    mUsername = mName.toLower() + "." + mSurname.toLower();
    setId(0);
}

User::User (QString name, QString surname, quint32 id):
    mName(name),
    mSurname(surname)
{
    mUsername = mName.toLower() + "." + mSurname.toLower();
    setId(id);
}

QString User::name (void)
{
    return mName;
}

QString User::surname (void)
{
    return mSurname;
}

QString User::username (void)
{
    return mUsername;
}

void User::setId (quint32 id)
{
    mId = id;
    mCode = QString("U%1").arg(id, 5, 10, QLatin1Char('0'));
}

quint32 User::id (void)
{
    return mId;
}

QString User::code (void)
{
    return mCode;
}

void User::write (QJsonObject &json) const
{
    QJsonObject o;
    // Save name...
    o["Id"]       = (int)mId;
    o["Code"]     = mCode;
    o["Name"]     = mName;
    o["Surname"]  = mSurname;
    o["Username"] = mUsername;

    json.insert("User", o);
}

void User::read (const QJsonObject &json)
{
    if (json.contains("Code") && json["Code"].isString())
    {
        mCode = json["Code"].toString();
    }

    if (json.contains("Name") && json["Name"].isString())
    {
        mName = json["Name"].toString();
    }

    if (json.contains("Surname") && json["Surname"].isString())
    {
        mSurname = json["Surname"].toString();
    }

    if (json.contains("Username") && json["Username"].isString())
    {
        mUsername = json["Username"].toString();
    }

    if (json.contains("Id") && json["Id"].isDouble())
    {
        mId = json["Id"].toInt();
    }
}
