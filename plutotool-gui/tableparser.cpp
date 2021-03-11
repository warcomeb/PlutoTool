#include "tableparser.h"

#include <QTextStream>
#include <QDebug>

void TableParser::setPayeeList(PayeeList *list)
{
    mPayeeList = list;
}

void TableParser::parse (QByteArray data)
{
    if (data.startsWith(";PayeeTable"))
    {
        parsePayee(data);
    }
}

void TableParser::parsePayee(QByteArray data)
{
    QTextStream d(data);
    QString s;

    mPayeeList->clear();
    while (d.readLineInto(&s))
    {
        if (s.startsWith(";")) continue;

        QStringList l = s.split(";");
        PayeeType pt = PayeeType(l.at(4).simplified(),(quint32)l.at(3).toInt());
        Payee p = Payee(l.at(2).simplified(),pt,(quint32)l.at(0).toInt());

        mPayeeList->append(p);
    }
}
