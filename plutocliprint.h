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

#ifndef PLUTOCLIPRINT_H
#define PLUTOCLIPRINT_H

#include "plutoprint.h"

class PlutoCLIPrint : public PlutoPrint
{
public:
    PlutoCLIPrint ();
    ~PlutoCLIPrint ();

    void printScheduled (QList<Scheduled> s);

    void printMovements (QList<Movement> m);

    void printAccounts (QMap<quint32, Account> a);
    void printPayees (QList<Payee> p);
    void printCategories (QList<Category> c);
    void printWorkOrders (QList<WorkOrder> w);

private:

    const int CLI_PRINT_ID_SIZE           = -6;
    const int CLI_PRINT_CODE_SIZE         = -10;
    const int CLI_PRINT_AMOUNT_SIZE       = 10;
    const int CLI_PRINT_PAYEE_SIZE        = -30;
    const int CLI_PRINT_ACCOUNT_SIZE      = -30;
    const int CLI_PRINT_ACCOUNT_TYPE_SIZE = -20;
    const int CLI_PRINT_DEADLINE_SIZE     = -10;
    const int CLI_PRINT_WORKORDER_SIZE    = -15;
    const int CLI_PRINT_CATEGORY_SIZE     = -20;
    //const int CLI_PRINT_PAID_SIZE      = -1;

    QString mScheduledHeader;
    QString mScheduledHeaderLine;
    int     mScheduledHeaderLength;

    QString mMovementsHeader;
    QString mMovementsHeaderLine;
    int     mMovementsHeaderLength;

    QTextStream& out (void);
};

#endif // PLUTOCLIPRINT_H
