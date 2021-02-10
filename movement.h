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

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <QDate>

#include "account.h"
#include "workorder.h"
#include "category.h"
#include "payee.h"

class Movement
{
public:
    Movement ();
    Movement (QDate     date,
              Account   account,
              float     amount,
              WorkOrder workorder,
              Payee     payee,
              Category  category);

    Account   account (void);
    float     amount (void);
    Payee     payee (void);
    Category  category (void);
    WorkOrder workorder (void);
    QDate     date (void);

private:

    QDate     mDate;
    Account   mAccount;
    float     mAmount;
    WorkOrder mWorkOrder;
    Payee     mPayee;
    Category  mCategory;
};

#endif // MOVEMENT_H
