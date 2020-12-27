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

#ifndef PLUTOTOOL_H
#define PLUTOTOOL_H

#include <QMap>
#include <QtGlobal>

#include "config.h"

#include "user.h"
#include "workorder.h"

class PlutoTool
{
public:
    PlutoTool (Config config);

private:
    void executeCommand (void);

    User createUser (quint32 id);

    Config mConfig;

    QMap<quint32,User> mUsers;
    quint32            mUserNextId;

    QMap<quint32,WorkOrder> mWorkOrders;
    quint32                 mWorkOrderNextId;
};

#endif // PLUTOTOOL_H
