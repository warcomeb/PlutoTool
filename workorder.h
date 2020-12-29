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
#ifndef WORKORDER_H
#define WORKORDER_H

#include <QtGlobal>
#include <QString>
#include <QDate>
#include <QJsonObject>

class WorkOrder
{
public:
    WorkOrder ();
    WorkOrder (QString name, QDate start, QDate end);
    WorkOrder (QString name, QString description, QDate start, QDate end);
    WorkOrder (QString name, QString description, QDate start, QDate end, quint32 id);

    QString name (void);

    void setId (quint32 id);
    quint32 id (void);

    QString code (void);

    void write (QJsonObject &json) const;

private:
    quint32 mId;
    QString mCode;
    QString mName;
    QString mDescription;
    QDate   mStart;
    QDate   mEnd;
};

#endif // WORKORDER_H
