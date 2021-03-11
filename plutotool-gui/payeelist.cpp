#include "payeelist.h"

PayeeList::PayeeList(QObject *parent) : QObject(parent)
{
//    PayeeType pt("madona");
//    Payee p("porcodio",pt,3);
//    Payee p2("porcamadonna",pt,3);
//    append(p);
//    append(p2)
}

QList<Payee> PayeeList::items () const
{
    return mItems;
}

void PayeeList::clear ()
{
    mItems.clear();
}

void PayeeList::append (const Payee &item)
{
    emit preItemAppended();
    mItems.append(item);
    emit postItemAppended();
}

