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
#include "accounttype.h"

AccountType::AccountType ()
{

}

AccountType::AccountType (QString name):
    mName(name),
    mDescription("")
{
    setId(0); // It's not a valid ID!
}

AccountType::AccountType (QString name, quint32 id):
    mName(name),
    mDescription("")
{
    setId(id);
}

QString AccountType::name (void)
{
    return mName;
}

void AccountType::setDescription (QString desc)
{
    mDescription = desc;
}

QString AccountType::description (void)
{
    return mDescription;
}

void AccountType::setId (quint32 id)
{
    mId = id;
}

quint32 AccountType::id (void) const
{
    return mId;
}

void AccountType::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]          = (int)mId;
    o["Name"]        = mName;
    o["Description"] = mDescription;

    json.insert("AccountType", o);
}

void AccountType::read (const QJsonObject &json)
{
    if (json.contains("Name") && json["Name"].isString())
    {
        mName = json["Name"].toString();
    }

    if (json.contains("Description") && json["Description"].isString())
    {
        mDescription = json["Description"].toString();
    }

    if (json.contains("Id") && json["Id"].isDouble())
    {
        mId = json["Id"].toInt();
    }
}
