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
#include "workorder.h"

WorkOrder::WorkOrder ()
{
    mName  = QString("Undefined");
    mStart = QDate(2020,1,1);
    mEnd   = QDate(2099,12,31);
    mDescription = QString("");
    setId(0); // Not valid Id!
}

WorkOrder::WorkOrder (QString name, QDate start, QDate end):
    mName(name),
    mStart(start),
    mEnd(end)
{
    mDescription = "";
    setId(0); // Not valid Id!
}

WorkOrder::WorkOrder (QString name, QString description, QDate start, QDate end):
    mName(name),
    mDescription(description),
    mStart(start),
    mEnd(end)
{
    setId(0); // Not valid Id!
}

WorkOrder::WorkOrder (QString name, QString description, QDate start, QDate end, quint32 id):
    mName(name),
    mDescription(description),
    mStart(start),
    mEnd(end)
{
    setId(id);
}

QString WorkOrder::name (void)
{
    return mName;
}

void WorkOrder::setId (quint32 id)
{
    mId = id;
    mCode = QString("W%1").arg(id, 5, 10, QLatin1Char('0'));
}

quint32 WorkOrder::id (void) const
{
    return mId;
}

QString WorkOrder::code (void)
{
    return mCode;
}

void WorkOrder::write (QJsonObject &json) const
{
    QJsonObject o;
    // Save name...
    o["Id"]          = (int)mId;
    o["Code"]        = mCode;
    o["Name"]        = mName;
    o["Start"]       = mStart.toString("yyyy-MM-dd");
    o["End"]         = mEnd.toString("yyyy-MM-dd");
    o["Description"] = mDescription;

    json.insert("WorkOrder", o);
}

void WorkOrder::read (const QJsonObject &json)
{
    if (json.contains("Code") && json["Code"].isString())
    {
        mCode = json["Code"].toString();
    }

    if (json.contains("Name") && json["Name"].isString())
    {
        mName = json["Name"].toString();
    }

    if (json.contains("Start") && json["Start"].isString())
    {
        mStart = QDate::fromString(json["Start"].toString(),"yyyy-MM-dd");
    }

    if (json.contains("End") && json["End"].isString())
    {
        mEnd = QDate::fromString(json["End"].toString(),"yyyy-MM-dd");
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
