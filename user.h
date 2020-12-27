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
#ifndef USER_H
#define USER_H

#include <QtGlobal>
#include <QString>

class User
{
public:
    User(QString name, QString surname);

    QString name (void);
    QString surname (void);

    void setId (quint32 id);
    quint32 id (void);

    QString code (void);

private:
    quint32 mId;
    QString mCode;

    QString mName;
    QString mSurname;
};

#endif // USER_H
