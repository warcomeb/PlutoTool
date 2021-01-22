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

#ifndef PLUTOTOOLREPORT_H
#define PLUTOTOOLREPORT_H

#if !defined (PLUTOTOOL_DEFINE_MESSAGE)
#define PLUTOTOOL_DEFINE_MESSAGE(id,unused1,unused2) \
   extern const char id[];
#endif

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_DATABASE_DOESNT_EXIST_,
                         0x01001,
                         "[01001] The database doesn\'t exist!")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_DATABASE_CANT_OPEN_,
                         0x01002,
                         "[01002] Fail open database!")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_DATABASE_JUST_EXIST_,
                         0x01003,
                         "[01002] Fail open, the database just exist!")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_ACCOUNT_FAIL_ADD_NEW_,
                         0x02001,
                         "[02001] Fail add new account, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_TRANSACTION_FAIL_ADD_NEW_,
                         0x03001,
                         "[03001] Fail add new transaction, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_PAYEE_FAIL_ADD_NEW_,
                         0x04001,
                         "[04001] Fail add new payee, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_PAYEETYPE_FAIL_ADD_NEW_,
                         0x05001,
                         "[05001] Fail add new payee type, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_ACCOUNTTYPE_FAIL_ADD_NEW_,
                         0x06001,
                         "[06001] Fail add new account type, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_USER_FAIL_ADD_NEW_,
                         0x07001,
                         "[07001] Fail add new user, wrong params.")

PLUTOTOOL_DEFINE_MESSAGE(PLUTOTOOL_WORKORDER_FAIL_ADD_NEW_,
                         0x08001,
                         "[08001] Fail add new workorder, wrong params.")

#endif // PLUTOTOOLREPORT_H
