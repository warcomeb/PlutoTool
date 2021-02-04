#include "plutocliprint.h"

#include <QString>

PlutoCLIPrint::PlutoCLIPrint ()
{
    mHeader = QString("%1 | %2 | %3 | %4 | %5 | %6 | %7 \r\n")
                .arg("Id"       ,SCHEDULED_ID_SIZE)
                .arg("Amount"   ,SCHEDULED_AMOUNT_SIZE)
                .arg("Payee"    ,SCHEDULED_PAYEE_SIZE)
                .arg("Deadline" ,SCHEDULED_DEADLINE_SIZE)
                .arg("Category" ,SCHEDULED_CATEGORY_SIZE)
                .arg("WorkOrder",SCHEDULED_WORKORDER_SIZE)
                .arg("P");
    mHeaderLength = mHeader.length() - 2;
    mHeaderLine = QString("%1\r\n")
                    .arg("",mHeaderLength,QChar('-'));
}

PlutoCLIPrint::~PlutoCLIPrint ()
{

}

void PlutoCLIPrint::printScheduled (QList<Scheduled> s)
{
    out() << "\r\n";

    // Print table header
    out() << mHeaderLine;
    out() << mHeader;
    out() << mHeaderLine;

    // Print Element
    foreach (Scheduled e, s)
    {
        out() << QString("%1 | %2 | %3 | %4 | %5 | %6 | %7\r\n")
                    .arg((int)e.id()         ,SCHEDULED_ID_SIZE,10)
                    .arg((double)e.amount()  ,SCHEDULED_AMOUNT_SIZE,'f',2)
                    .arg(e.payee().name()    ,SCHEDULED_PAYEE_SIZE)
                    .arg(e.deadline().toString("yyyy-MM-dd"))
                    .arg(e.category().name()  ,SCHEDULED_CATEGORY_SIZE)
                    .arg(e.workorder().name() ,SCHEDULED_WORKORDER_SIZE)
                    .arg((e.paid() == true) ? "Y" : "N");
        out() << mHeaderLine;
    }

    out().flush();
}

void PlutoCLIPrint::printMovements (QList<Movement> m)
{
    // Print Element
    foreach (Movement e, m)
    {

    }
}

QTextStream& PlutoCLIPrint::out (void)
{
    static QTextStream ts( stdout );
    return ts;
}
