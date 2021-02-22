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

    static bool compareMovements (const Movement& m1, const Movement& m2)
    {
        if (m1.date() < m2.date())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static QList<Movement> getMovements (Database  db,
                                         QDate     start,
                                         QDate     end,
                                         quint32   accountId,
                                         quint32   workorderId,
                                         quint32   categoryId,
                                         quint32   payeeId)
    {
        QList<Movement> list;
        list.clear();

        bool checkWorkOrder = false;
        bool checkCategory  = false;
        bool checkPayee     = false;
        bool checkAccount   = false;

        // Set start date if not valid or null
        if (start.isNull() || (!start.isValid()))
        {
            start = QDate::fromString("2020-01-01","yyyy-MM-dd");
        }

        // Check end date, and in case replace with today!
        if (end.isNull() || (!end.isValid()))
        {
            end = QDate::currentDate();
        }

        // Check the account, if null return an empty list
        if (accountId > 0)
        {
            if (db.isAccountExist(accountId))
            {
                checkAccount = true;
            }
            else
            {
                return list;
            }
        }

        if (workorderId > 0) checkWorkOrder = true;
        if (categoryId > 0)  checkCategory  = true;
        if (payeeId > 0)     checkPayee     = true;

        QMap<quint32,Transaction> transaction = db.transaction();
        foreach (Transaction t, transaction)
        {
            if ((checkPayee)     && (t.payee().id()       != payeeId))      continue;
            if ((checkWorkOrder) && (t.workorder().id()   != workorderId))  continue;
            if ((checkCategory)  && (t.category().id()    != categoryId))   continue;
            if ((checkAccount)   && ((t.accoutTo().id()   != accountId) &&
                                     (t.accoutFrom().id() != accountId)))   continue;

            if ((t.date() > start) && (t.date() <= end))
            {
                float amount = t.amount();

                Account account;

                Payee payee;
                if (checkPayee == true)
                {
                    payee = db.getPayee(payeeId);
                }
                else
                {
                    payee = t.payee();
                }

                WorkOrder workorder;
                if (checkWorkOrder == true)
                {
                    workorder = db.getWorkOrder(workorderId);
                }
                else
                {
                    workorder = t.workorder();
                }

                Category category;
                if (checkCategory == true)
                {
                    category = db.getCategory(categoryId);
                }
                else
                {
                    category = t.category();
                }

                Movement m;
                switch (t.type())
                {
                case Transaction::TYPE_OUTPUT:
                    if (checkAccount == true)
                    {
                        if (t.accoutFrom().id() == accountId)
                        {
                            account = db.getAccount(accountId);
                        }
                        else
                        {
                            // Jump to the next transaction...
                            continue;
                        }
                    }
                    else
                    {
                        account = t.accoutFrom();
                    }
                    amount *= -1;

                    m = Movement(t.date(),account,amount,workorder,payee,category);
                    list.append(m);
                    break;

                case Transaction::TYPE_INPUT:
                    if (checkAccount == true)
                    {
                        if (t.accoutTo().id() == accountId)
                        {
                            account = db.getAccount(accountId);
                        }
                        else
                        {
                            // Jump to the next transaction...
                            continue;
                        }
                    }
                    else
                    {
                        account = t.accoutTo();
                    }

                    m = Movement(t.date(),account,amount,workorder,payee,category);
                    list.append(m);
                    break;

                case Transaction::TYPE_NEUTRAL:
                    if (checkAccount == true)
                    {
                        if (t.accoutTo().id() == accountId)
                        {
                            account = db.getAccount(accountId);
                        }
                        else if (t.accoutFrom().id() == accountId)
                        {
                            amount *= -1;
                            account = db.getAccount(accountId);
                        }
                        else
                        {
                            // Jump to the next transaction...
                            continue;
                        }
                        m = Movement(t.date(),account,amount,workorder,payee,category);
                        list.append(m);
                    }
                    else
                    {
                        m = Movement(t.date(),t.accoutTo(),amount,workorder,payee,category);
                        list.append(m);

                        amount *= -1;
                        m = Movement(t.date(),t.accoutFrom(),amount,workorder,payee,category);
                        list.append(m);
                    }
                    break;

                default:
                    break;
                }
            }
        }

        std::sort(list.begin(),list.end(),Counts::compareMovements);
        return list;
    };
};

#endif // COUNTS_H
