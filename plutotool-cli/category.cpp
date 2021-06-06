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
#include "category.h"

Category::Category ()
{
    mName    = "Undefined";
    mSubName = "Undefined";
    setId(0); // Invalid Id
}

Category::Category (QString name, QString subName):
    mName(name),
    mSubName(subName)
{
    setId(0); // Invalid Id
}

Category::Category (QString name, QString subName, quint32 id):
    mName(name),
    mSubName(subName)
{
    setId(id);
}

QString Category::name (void) const
{
    return mName;
}

QString Category::subName (void) const
{
    return mSubName;
}

QString Category::completeName (void) const
{
    return QString(mName + "/" + mSubName);
}

QString Category::description (void)
{
    return mDescription;
}

void Category::setId (quint32 id)
{
    mId = id;
}

quint32 Category::id (void) const
{
    return mId;
}

void Category::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]          = (int)mId;
    o["Name"]        = mName;
    o["SubName"]     = mSubName;
    o["Description"] = mDescription;

    json.insert("Category", o);
}

void Category::read (const QJsonObject &json)
{
    if (json.contains("Name") && json["Name"].isString())
    {
        mName = json["Name"].toString();
    }

    if (json.contains("SubName") && json["SubName"].isString())
    {
        mSubName = json["SubName"].toString();
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
