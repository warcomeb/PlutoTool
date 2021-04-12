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

#include "movement.h"

Movement::Movement()
{
    // Nothing to do...
}

Movement::Movement (QDate     date,
                    Account   account,
                    float     amount,
                    WorkOrder workorder,
                    Payee     payee,
                    Category  category):
    mDate(date),
    mAccount(account),
    mAmount(amount),
    mWorkOrder(workorder),
    mPayee(payee),
    mCategory(category)
{
    // Nothing to do...
}

Account Movement::account (void)
{
    return mAccount;
}

float Movement::amount (void) const
{
    return mAmount;
}

Payee Movement::payee (void)
{
    return mPayee;
}

Category Movement::category (void)
{
    return mCategory;
}

WorkOrder Movement::workorder (void)
{
    return mWorkOrder;
}

QDate Movement::date (void) const
{
    return mDate;
}
