#ifndef PAYEELIST_H
#define PAYEELIST_H

#include <QObject>
#include <QList>
#include "payee.h"

class PayeeList : public QObject
{
    Q_OBJECT
public:
    explicit PayeeList (QObject *parent = nullptr);

    QList<Payee> items() const;

    void clear (void);
    void append (const Payee& item);

signals:
    void preItemAppended ();
    void postItemAppended ();

    void preItemRemoved (int index);
    void postItemRemoved ();

//public slots:
//    void appendItem ();

private:
    QList<Payee> mItems;
};

#endif // PAYEELIST_H
