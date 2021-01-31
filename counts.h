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

#ifndef COUNTS_H
#define COUNTS_H

#include "database.h"
#include "scheduled.h"
#include "movement.h"

class Counts
{
public:
    Counts();

    static QList<Scheduled> getScheduled (Database db)
    {
        QList<Scheduled> list;
        QMap<quint32,Scheduled> scheduled = db.scheduled();
        foreach (Scheduled s, scheduled)
        {
            if (s.paid() == false)
            {
                list.append(s);
            }
        }
        return list;
    };

    static QList<Movement> getMovements (Database db)
    {
        QList<Movement> list;

        return list;
    };
};

#endif // COUNTS_H
