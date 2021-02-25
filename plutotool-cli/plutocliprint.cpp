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

void PlutoCLIPrint::printScheduled (QList<Scheduled> s)
{
    out() << "\r\n";

    QString header = QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 \r\n")
                         .arg("Id"       ,CLI_PRINT_ID_SIZE)
                         .arg("Amount"   ,CLI_PRINT_AMOUNT_SIZE)
                         .arg("Payee"    ,CLI_PRINT_PAYEE_SIZE)
                         .arg("Deadline" ,CLI_PRINT_DEADLINE_SIZE)
                         .arg("Category" ,CLI_PRINT_CATEGORY_SIZE)
                         .arg("WorkOrder",CLI_PRINT_WORKORDER_SIZE)
                         .arg("P");
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    out() << headerLine;
    out() << header;
    out() << headerLine;

    // Print Element
    foreach (Scheduled e, s)
    {
        out() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7\r\n")
                    .arg((int)e.id()                                                     ,CLI_PRINT_ID_SIZE,10)
                    .arg((double)e.amount()                                              ,CLI_PRINT_AMOUNT_SIZE,'f',2)
                    .arg(e.payee().name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))               ,CLI_PRINT_PAYEE_SIZE)
                    .arg(e.deadline().toString("yyyy-MM-dd"))
                    .arg(e.category().completeName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)) ,CLI_PRINT_CATEGORY_SIZE)
                    .arg(e.workorder().name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE))       ,CLI_PRINT_WORKORDER_SIZE)
                    .arg((e.paid() == true) ? "Y" : "N");
        out() << headerLine;
    }

    out().flush();
}

void PlutoCLIPrint::printMovements (QList<Movement> m)
{
    out() << "\r\n";

    QString header = QString("%1 | %2 | %3 | %4 | %5 | %6 \r\n")
                        .arg("Date"     ,CLI_PRINT_DEADLINE_SIZE)
                        .arg("Amount"   ,CLI_PRINT_AMOUNT_SIZE)
                        .arg("Account"  ,CLI_PRINT_ACCOUNT_SIZE)
                        .arg("Payee"    ,CLI_PRINT_PAYEE_SIZE)
                        .arg("Category" ,CLI_PRINT_CATEGORY_SIZE)
                        .arg("WorkOrder",CLI_PRINT_WORKORDER_SIZE);
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    out() << headerLine;
    out() << header;
    out() << headerLine;

    float total = 0.0f;

    // Print Element
    foreach (Movement e, m)
    {
        out() << QString("%1 | %2 | %3 | %4 | %5 | %6\r\n")
                    .arg(e.date().toString("yyyy-MM-dd"))
                    .arg((double)e.amount()                                             ,CLI_PRINT_AMOUNT_SIZE,'f',2)
                    .arg(e.account().name().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))          ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg(e.payee().name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))              ,CLI_PRINT_PAYEE_SIZE)
                    .arg(e.category().completeName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)),CLI_PRINT_CATEGORY_SIZE)
                    .arg(e.workorder().name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE))      ,CLI_PRINT_WORKORDER_SIZE);
        total += (float)e.amount();
        out() << headerLine;
    }
    // Print total
    out() << headerLine;
    out() << QString("%1 | %2 |\r\n")
                .arg("Total"       ,CLI_PRINT_DEADLINE_SIZE)
                .arg((double)total ,CLI_PRINT_AMOUNT_SIZE,'f',2);
    out() << headerLine;
}

void PlutoCLIPrint::printAccounts (QMap<quint32,Account> a, bool format)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 | %6 \r\n";
    if (format == true)
    {
        headerFormat = "%1;%2;%3;%4;%5;%6\r\n";
    }

    QString header = QString(headerFormat)
                           .arg("Id  "     ,CLI_PRINT_ID_SIZE)
                           .arg("Code"     ,CLI_PRINT_CODE_SIZE)
                           .arg("Name"     ,CLI_PRINT_ACCOUNT_SIZE)
                           .arg("Number"   ,CLI_PRINT_ACCOUNT_SIZE)
                           .arg("Type"     ,CLI_PRINT_ACCOUNT_TYPE_SIZE)
                           .arg("A");
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!format) out() << headerLine;
    out() << header;
    if (!format) out() << headerLine;

    // Print Element
    foreach (Account e, a)
    {
        out() << QString(headerFormat)
                    .arg(e.id()                                                 ,CLI_PRINT_ID_SIZE)
                    .arg(e.code()                                               ,CLI_PRINT_CODE_SIZE)
                    .arg(e.name().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))            ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg(e.number().mid(0,abs(CLI_PRINT_ACCOUNT_SIZE))          ,CLI_PRINT_ACCOUNT_SIZE)
                    .arg(e.type().name().mid(0,abs(CLI_PRINT_ACCOUNT_TYPE_SIZE)),CLI_PRINT_ACCOUNT_TYPE_SIZE)
                    .arg((e.active() == true) ? "Y" : "N");
        if (!format) out() << headerLine;
    }
}
void PlutoCLIPrint::printPayees (QMap<quint32,Payee> p, bool format)
{
    QString headerFormat = "%1 | %2 | %3 | %4 \r\n";
    if (format == true)
    {
        headerFormat = "%1;%2;%3;%4\r\n";
    }

    QString header = QString(headerFormat)
                           .arg("Id  "     ,CLI_PRINT_ID_SIZE)
                           .arg("Code"     ,CLI_PRINT_CODE_SIZE)
                           .arg("Name"     ,CLI_PRINT_PAYEE_SIZE)
                           .arg("Type"     ,CLI_PRINT_PAYEE_TYPE_SIZE);
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!format) out() << headerLine;
    out() << header;
    if (!format) out() << headerLine;

    // Print Element
    foreach (Payee e, p)
    {
        out() << QString(headerFormat)
                    .arg(e.id()                                               ,CLI_PRINT_ID_SIZE)
                    .arg(e.code()                                             ,CLI_PRINT_CODE_SIZE)
                    .arg(e.name().mid(0,abs(CLI_PRINT_PAYEE_SIZE))            ,CLI_PRINT_PAYEE_SIZE)
                    .arg(e.type().name().mid(0,abs(CLI_PRINT_PAYEE_TYPE_SIZE)),CLI_PRINT_PAYEE_TYPE_SIZE);
        if (!format) out() << headerLine;
    }
}

void PlutoCLIPrint::printCategories (QMap<quint32,Category> c, bool format)
{
    QString headerFormat = "%1 | %2 | %3 \r\n";
    if (format == true)
    {
        headerFormat = "%1;%2;%3\r\n";
    }

    QString header = QString(headerFormat)
                           .arg("Id  "     ,CLI_PRINT_ID_SIZE)
                           .arg("Name"     ,CLI_PRINT_CATEGORY_SIZE)
                           .arg("SubName"  ,CLI_PRINT_CATEGORY_SIZE);
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!format) out() << headerLine;
    out() << header;
    if (!format) out() << headerLine;

    // Print Element
    foreach (Category e, c)
    {
        out() << QString(headerFormat)
                    .arg(e.id()                                         ,CLI_PRINT_ID_SIZE)
                    .arg(e.name().mid(0,abs(CLI_PRINT_CATEGORY_SIZE))   ,CLI_PRINT_CATEGORY_SIZE)
                    .arg(e.subName().mid(0,abs(CLI_PRINT_CATEGORY_SIZE)),CLI_PRINT_CATEGORY_SIZE);
        if (!format) out() << headerLine;
    }
}

void PlutoCLIPrint::printWorkOrders (QMap<quint32,WorkOrder> w, bool format)
{
    QString headerFormat = "%1 | %2 | %3 | %4 | %5 \r\n";
    if (format == true)
    {
        headerFormat = "%1;%2;%3;%4;%5\r\n";
    }

    QString header = QString(headerFormat)
                           .arg("Id  "     ,CLI_PRINT_ID_SIZE)
                           .arg("Code"     ,CLI_PRINT_CODE_SIZE)
                           .arg("Name"     ,CLI_PRINT_WORKORDER_SIZE)
                           .arg("Start"    ,CLI_PRINT_DEADLINE_SIZE)
                           .arg("End"      ,CLI_PRINT_DEADLINE_SIZE);
    int headerLen = header.length() - 2;
    QString headerLine = QString("%1\r\n").arg("",headerLen,QChar('-'));

    // Print table header
    if (!format) out() << headerLine;
    out() << header;
    if (!format) out() << headerLine;

    // Print Element
    foreach (WorkOrder e, w)
    {
        out() << QString(headerFormat)
                    .arg(e.id()                                       ,CLI_PRINT_ID_SIZE)
                    .arg(e.code()                                     ,CLI_PRINT_CODE_SIZE)
                    .arg(e.name().mid(0,abs(CLI_PRINT_WORKORDER_SIZE)),CLI_PRINT_WORKORDER_SIZE)
                    .arg(e.start().toString("yyyy-MM-dd"))
                    .arg(e.end().toString("yyyy-MM-dd"));
        if (!format) out() << headerLine;
    }
}

QTextStream& PlutoCLIPrint::out (void)
{
    static QTextStream ts( stdout );
    return ts;
}
