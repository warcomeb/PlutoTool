#ifndef TABLEPARSER_H
#define TABLEPARSER_H

#include <QObject>
#include <QByteArray>

#include "payeelist.h"

class TableParser : public QObject
{
    Q_OBJECT

public:
    TableParser(QObject *parent = 0) : QObject(parent) { }
    virtual ~TableParser() = default;

    void setPayeeList (PayeeList* list);

public slots:
    void parse (QByteArray data);

private:

    void parsePayee (QByteArray data);

    PayeeList* mPayeeList;
};

#endif // TABLEPARSER_H
