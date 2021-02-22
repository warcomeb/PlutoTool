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

#ifndef PLUTODEFAULT_H
#define PLUTODEFAULT_H

#include <QString>
#include <QList>
#include <QMultiMap>

class PlutoDefault
{
public:
    PlutoDefault();

    QList<QString> accountType (void)
    {
        return mAccountType;
    }

    QList<QString> payeeType (void)
    {
        return mPayeeType;
    }

    QMultiMap<QString,QString> category (void)
    {
        return mCategory;
    }

private:
    QList<QString>             mAccountType;
    QList<QString>             mPayeeType;
    QMultiMap<QString,QString> mCategory;
};

#endif // PLUTODEFAULT_H
