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

#ifndef PLUTOPRINT_H
#define PLUTOPRINT_H

#include <QList>
#include <QtGlobal>

#include "scheduled.h"
#include "movement.h"

class PlutoPrint
{
public:

    virtual void printScheduled (QList<Scheduled> s) = 0;

    virtual void printMovements (QList<Movement> m) = 0;

    virtual void printAccounts (QMap<quint32, Account> a, bool format) = 0;
    virtual void printPayees (QMap<quint32,Payee> p, bool format) = 0;
    virtual void printCategories (QMap<quint32,Category> c, bool format) = 0;
    virtual void printWorkOrders (QMap<quint32,WorkOrder> w, bool format) = 0;

};
#endif // PLUTOPRINT_H
