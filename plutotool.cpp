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

#include "plutotool.h"

#include "utils/wlog.h"

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#include <QString>
#include <QDate>

PlutoTool::PlutoTool(Config config):
    mConfig(config)
{
    WLog& log = WLog::instance();
    // FIXME
    //log.setVerboseLevel(config.verboseLevel);
    log.setVerboseLevel(2);

    executeCommand();
}

User PlutoTool::createUser (quint32 id)
{
    string name, surname;
    cout << "Adding new user:" << endl;
    cout << "Insert name: ";
    getline(cin,name);
    cout << "Insert Surname: ";
    getline(cin,surname);

    User u = User(QString(name.c_str()),QString(surname.c_str()));
    u.setId(id);
    return u;
}

void PlutoTool::executeCommand (void)
{
    WLog& log = WLog::instance();

    if (mConfig.cmd == COMMAND_LIST)
    {
        cout << "\r\nCommand list:\r\n";
        cout << "  LIST: this command," << endl;
        cout << "  INIT: initialize new database" << endl;
    }
    else if (mConfig.cmd == COMMAND_INIT)
    {
        cout << "%%%%%%%%%% COMMAND INIT %%%%%%%%%%" << endl;

        log.log(QString("Create first user..."),1);
        mUserNextId = 1;
        User u = createUser(mUserNextId++);
        mUsers.insert(u.id(),u);
        log.log(QString("User %1 %2 (%3) has been added!").arg(u.name()).arg(u.surname()).arg(u.code()),1);

        log.log(QString("Create default workorder..."),1);
        mWorkOrderNextId = 1;
        WorkOrder w = WorkOrder("Undefined",QDate(2020,1,1),QDate(2099,12,31));
        w.setId(mWorkOrderNextId++);
        mWorkOrders.insert(w.id(),w);
        log.log(QString("Work Order %1 (%2) has been added!").arg(w.name()).arg(w.code()),1);

        log.log(QString("Create default account type..."),1);

        log.log(QString("Create default payee type..."),1);

        log.log(QString("Create default category..."),1);

        log.log(QString("Save database!"),1);

    }
    else if (mConfig.cmd == COMMAND_ERROR)
    {
        cout << "\r\nCommand NOT FOUND!" << endl;
    }
}
