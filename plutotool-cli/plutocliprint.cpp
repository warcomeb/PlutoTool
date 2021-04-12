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
#include "plutocliprint.h"

#include <QString>

PlutoCLIPrint::PlutoCLIPrint ()
{

}

PlutoCLIPrint::~PlutoCLIPrint ()
{

}

void PlutoCLIPrint::printScheduled (QList<Scheduled> s, bool noFormat)
{
    out() << "\r\n";
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 | %6 | %7 \r\n";
    if (noFormat == true)
    {
        out() << ";ScheduledTable \r\n";
        headerFormat = "%1;%2;%3;%4;%5;%6;%7\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";" + headerFormat)
                         .arg("Id")
                         .arg("Amount")
                         .arg("Payee")
                         .arg("Deadline")
                         .arg("Category")
                         .arg("WorkOrder")
                         .arg("P");
    }
    else
    {
        header = QString(headerFormat)
                         .arg("Id"       ,CLI_PRINT_ID_SIZE)
                         .arg("Amount"   ,CLI_PRINT_AMOUNT_SIZE)
                         .arg("Payee"    ,CLI_PRINT_PAYEE_SIZE)
                         .arg("Deadline" ,CLI_PRINT_DEADLINE_SIZE)
                         .arg("Category" ,CLI_PRINT_CATEGORY_SIZE)
                         .arg("WorkOrder",CLI_PRINT_WORKORDER_SIZE)
                         .arg("P");
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (Scheduled e, s)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg((int)e.id()                                                     ,CLI_PRINT_ID_SIZE,10)
                        .arg((double)e.amount()                                              ,CLI_PRINT_AMOUNT_SIZE,'f',2)
                        .arg(e.payee().name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))               ,CLI_PRINT_PAYEE_SIZE)
                        .arg(e.deadline().toString("yyyy-MM-dd"))
                        .arg(e.category().completeName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)) ,CLI_PRINT_CATEGORY_SIZE)
                        .arg(e.workorder().name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE))       ,CLI_PRINT_WORKORDER_SIZE)
                        .arg((e.paid() == true) ? "Y" : "N");
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg((int)e.id())
                        .arg((double)e.amount(),0,'f',2)
                        .arg(e.payee().name())
                        .arg(e.deadline().toString("yyyy-MM-dd"))
                        .arg(e.category().completeName())
                        .arg(e.workorder().name())
                        .arg((e.paid() == true) ? "Y" : "N");
        }
    }

    out().flush();
}

void PlutoCLIPrint::printMovements (QList<Movement> m, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 | %6 \r\n";
    out() << "\r\n";
    if (noFormat == true)
    {
        out() << ";MovementsTable \r\n";
        headerFormat = "%1;%2;%3;%4;%5;%6\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";" + headerFormat)
                    .arg("Date")
                    .arg("Amount")
                    .arg("Account")
                    .arg("Payee")
                    .arg("Category")
                    .arg("WorkOrder");
    }
    else
    {
        header = QString(headerFormat)
                    .arg("Date"     ,CLI_PRINT_DEADLINE_SIZE)
                    .arg("Amount"   ,CLI_PRINT_AMOUNT_SIZE)
                    .arg("Account"  ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg("Payee"    ,CLI_PRINT_PAYEE_SIZE)
                    .arg("Category" ,CLI_PRINT_CATEGORY_SIZE)
                    .arg("WorkOrder",CLI_PRINT_WORKORDER_SIZE);
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    float total = 0.0f;

    // Print Element
    foreach (Movement e, m)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.date().toString("yyyy-MM-dd"))
                        .arg((double)e.amount()                                             ,CLI_PRINT_AMOUNT_SIZE,'f',2)
                        .arg(e.account().name().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))          ,CLI_PRINT_ACCOUNT_SIZE)
                        .arg(e.payee().name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))              ,CLI_PRINT_PAYEE_SIZE)
                        .arg(e.category().completeName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)),CLI_PRINT_CATEGORY_SIZE)
                        .arg(e.workorder().name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE))      ,CLI_PRINT_WORKORDER_SIZE);
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.date().toString("yyyy-MM-dd"))
                        .arg((double)e.amount(),0,'f',2)
                        .arg(e.account().name())
                        .arg(e.payee().name())
                        .arg(e.category().completeName())
                        .arg(e.workorder().name());
        }
        total += (float)e.amount();
    }

    // Print total
    if (!noFormat)
    {
        out() << headerLine;
        out() << QString("%1 | %2 |\r\n")
                    .arg("Total"       ,CLI_PRINT_DEADLINE_SIZE)
                    .arg((double)total ,CLI_PRINT_AMOUNT_SIZE,'f',2);
        out() << headerLine;
    }
}

void PlutoCLIPrint::printAccounts (QMap<quint32,Account> a, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 | %6 \r\n";
    if (noFormat == true)
    {
        out() << ";AccountsTable \r\n";
        headerFormat = "%1;%2;%3;%4;%5;%6\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";" + headerFormat)
                    .arg("Id")
                    .arg("Code")
                    .arg("Name")
                    .arg("Number")
                    .arg("Type")
                    .arg("A");
    }
    else
    {
        header = QString(headerFormat)
                    .arg("Id  "     ,CLI_PRINT_ID_SIZE)
                    .arg("Code"     ,CLI_PRINT_CODE_SIZE)
                    .arg("Name"     ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg("Number"   ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg("Type"     ,CLI_PRINT_ACCOUNT_TYPE_SIZE)
                    .arg("A");
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (Account e, a)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.id()                                                 ,CLI_PRINT_ID_SIZE)
                        .arg(e.code()                                               ,CLI_PRINT_CODE_SIZE)
                        .arg(e.name().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))            ,CLI_PRINT_ACCOUNT_SIZE)
                        .arg(e.number().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))          ,CLI_PRINT_ACCOUNT_SIZE)
                        .arg(e.type().name().mid(0,abs(CLI_PRINT_ACCOUNT_TYPE_SIZE)),CLI_PRINT_ACCOUNT_TYPE_SIZE)
                        .arg((e.active() == true) ? "Y" : "N");
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.id())
                        .arg(e.code())
                        .arg(e.name())
                        .arg(e.number())
                        .arg(e.type().name())
                        .arg((e.active() == true) ? "Y" : "N");
        }
    }
}
void PlutoCLIPrint::printPayees (QMap<quint32,Payee> p, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 \r\n";
    if (noFormat == true)
    {
        out() << ";PayeeTable \r\n";
        headerFormat = "%1;%2;%3;%4;%5\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";" + headerFormat)
                    .arg("Id")
                    .arg("Code")
                    .arg("Name")
                    .arg("TypeId")
                    .arg("Type");
    }
    else
    {
        header = QString(headerFormat)
                    .arg("Id"       ,CLI_PRINT_ID_SIZE)
                    .arg("Code"     ,CLI_PRINT_CODE_SIZE)
                    .arg("Name"     ,CLI_PRINT_PAYEE_SIZE)
                    .arg("TypeId"   ,CLI_PRINT_ID_SIZE)
                    .arg("Type"     ,CLI_PRINT_PAYEE_TYPE_SIZE);
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (Payee e, p)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.id()                                               ,CLI_PRINT_ID_SIZE)
                        .arg(e.code()                                             ,CLI_PRINT_CODE_SIZE)
                        .arg(e.name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))            ,CLI_PRINT_PAYEE_SIZE)
                        .arg(e.type().id()                                        ,CLI_PRINT_ID_SIZE)
                        .arg(e.type().name().mid(0,abs(CLI_PRINT_PAYEE_TYPE_SIZE)),CLI_PRINT_PAYEE_TYPE_SIZE);
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.id())
                        .arg(e.code())
                        .arg(e.name())
                        .arg(e.type().id())
                        .arg(e.type().name());
        }
    }
}

void PlutoCLIPrint::printCategories (QMap<quint32,Category> c, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 \r\n";
    if (noFormat == true)
    {
        out() << ";Categories Table \r\n";
        headerFormat = "%1;%2;%3\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";"+ headerFormat)
                           .arg("Id"     ,CLI_PRINT_ID_SIZE)
                           .arg("Name"     ,CLI_PRINT_CATEGORY_SIZE)
                           .arg("SubName"  ,CLI_PRINT_CATEGORY_SIZE);
    }
    else
    {
        header = QString(headerFormat)
                           .arg("Id")
                           .arg("Name")
                           .arg("SubName");
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (Category e, c)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.id()                                         ,CLI_PRINT_ID_SIZE)
                        .arg(e.name().mid(0,abs(CLI_PRINT_CATEGORY_SIZE))   ,CLI_PRINT_CATEGORY_SIZE)
                        .arg(e.subName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)),CLI_PRINT_CATEGORY_SIZE);
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.id())
                        .arg(e.name())
                        .arg(e.subName());
        }
    }
}

void PlutoCLIPrint::printWorkOrders (QMap<quint32,WorkOrder> w, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 \r\n";
    if (noFormat == true)
    {
        out() << ";WorkOrders Table \r\n";
        headerFormat = "%1;%2;%3;%4;%5\r\n";
    }

    QString header;
    if (noFormat == true)
    {
        header = QString(";"+ headerFormat)
                    .arg("Id")
                    .arg("Code")
                    .arg("Name")
                    .arg("Start")
                    .arg("End");
    }
    else
    {
        header = QString(headerFormat)
                    .arg("Id"    ,CLI_PRINT_ID_SIZE)
                    .arg("Code"  ,CLI_PRINT_CODE_SIZE)
                    .arg("Name"  ,CLI_PRINT_WORKORDER_SIZE)
                    .arg("Start" ,CLI_PRINT_DEADLINE_SIZE)
                    .arg("End"   ,CLI_PRINT_DEADLINE_SIZE);
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (WorkOrder e, w)
    {
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.id()                                       ,CLI_PRINT_ID_SIZE)
                        .arg(e.code()                                     ,CLI_PRINT_CODE_SIZE)
                        .arg(e.name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE)),CLI_PRINT_WORKORDER_SIZE)
                        .arg(e.start().toString("yyyy-MM-dd"))
                        .arg(e.end().toString("yyyy-MM-dd"));
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.id())
                        .arg(e.code())
                        .arg(e.name())
                        .arg(e.start().toString("yyyy-MM-dd"))
                        .arg(e.end().toString("yyyy-MM-dd"));
        }
    }
}

void PlutoCLIPrint::printTransactions (QMap<quint32,Transaction> t, bool noFormat)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9\r\n";
    if (noFormat == true)
    {
        out() << ";Transactions Table \r\n";
        headerFormat = "%1;%2;%3;%4;%5;%6;%7;%8;%9\r\n";
    }

    QString header;
    if (noFormat == false)
    {
        header = QString(";"+ headerFormat)
                           .arg("Id"       ,CLI_PRINT_ID_SIZE)
                           .arg("Date"     ,CLI_PRINT_DEADLINE_SIZE)
                           .arg("Amount"   ,CLI_PRINT_AMOUNT_SIZE)
                           .arg("From"     ,CLI_PRINT_ACCOUNT_STRICT_SIZE)
                           .arg("To"       ,CLI_PRINT_ACCOUNT_STRICT_SIZE)
                           .arg("Payee"    ,CLI_PRINT_PAYEE_STRICT_SIZE)
                           .arg("Category" ,CLI_PRINT_CATEGORY_STRICT_SIZE)
                           .arg("WorkOrder",CLI_PRINT_WORKORDER_STRICT_SIZE)
                           .arg("C"        ,1);
    }
    else
    {
        header = QString(headerFormat)
                    .arg("Id")
                    .arg("Date")
                    .arg("Amount")
                    .arg("From")
                    .arg("To")
                    .arg("Payee")
                    .arg("Category")
                    .arg("WorkOrder")
                    .arg("C");
    }

    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!noFormat) out() << headerLine;
    out() << header;
    if (!noFormat) out() << headerLine;

    // Print Element
    foreach (Transaction e, t)
    {
        // FIXME: add print without format to use with GUI!
        if (noFormat == false)
        {
            out() << QString(headerFormat)
                        .arg(e.id()                                                                 ,CLI_PRINT_ID_SIZE)
                        .arg(e.date().toString("yyyy-MM-dd")                                        ,CLI_PRINT_DEADLINE_SIZE)
                        .arg((double)e.amount()                                                     ,CLI_PRINT_AMOUNT_SIZE,'f',2)
                        .arg(e.accoutFrom().name().mid(0,abs(CLI_PRINT_ACCOUNT_STRICT_SIZE))        ,CLI_PRINT_ACCOUNT_STRICT_SIZE)
                        .arg(e.accoutTo().name().mid(0,abs(CLI_PRINT_ACCOUNT_STRICT_SIZE))          ,CLI_PRINT_ACCOUNT_STRICT_SIZE)
                        .arg(e.payee().name().mid(0,abs(CLI_PRINT_PAYEE_STRICT_SIZE))               ,CLI_PRINT_PAYEE_STRICT_SIZE)
                        .arg(e.category().completeName().mid(0,abs(CLI_PRINT_CATEGORY_STRICT_SIZE)) ,CLI_PRINT_CATEGORY_STRICT_SIZE)
                        .arg(e.workorder().name().mid(0,abs(CLI_PRINT_WORKORDER_STRICT_SIZE))       ,CLI_PRINT_WORKORDER_STRICT_SIZE)
                        .arg(e.checked() == true ? "Y" : "N");
            out() << headerLine;
        }
        else
        {
            out() << QString(headerFormat)
                        .arg(e.id())
                        .arg(e.date().toString("yyyy-MM-dd"))
                        .arg((double)e.amount(),0,'f',2)
                        .arg(e.accoutFrom().name())
                        .arg(e.accoutTo().name())
                        .arg(e.payee().name())
                        .arg(e.category().completeName())
                        .arg(e.workorder().name())
                        .arg(e.checked() == true ? "Y" : "N");
        }
    }
}

QTextStream& PlutoCLIPrint::out (void)
{
    static QTextStream ts( stdout );
    return ts;
}
