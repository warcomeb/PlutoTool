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
#ifndef PAYEETYPE_H
#define PAYEETYPE_H

#include <QtGlobal>
#include <QString>

#include <QJsonObject>

class PayeeType
{
public:
    PayeeType ();
    PayeeType (QString name);
    PayeeType (QString name, quint32 id);

    QString name (void);

    QString description (void);
    void setDescription (QString desc);

    void setId (quint32 id);
    quint32 id (void) const;

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json);

private:
    quint32 mId;
    QString mName;
    QString mDescription;
};

#endif // PAYEETYPE_H
