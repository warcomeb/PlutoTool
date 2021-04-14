#include "payeelist.h"

PayeeList::PayeeList(QObject *parent) : QObject(parent)
{

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

