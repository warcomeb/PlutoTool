#ifndef PAYEEMODEL_H
#define PAYEEMODEL_H

#include <QAbstractTableModel>

#include "payeelist.h"

//class PayeeList;

class PayeeModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(PayeeList *list READ list WRITE setList)

public:
    explicit PayeeModel(QObject *parent = nullptr);

    enum
    {
        HeadingRole = Qt::UserRole + 1,
        DataRole
    };

    enum
    {
        IdColumn = 0,
        NameColumn,
        TypeColumn
    };

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QHash<int, QByteArray> roleNames() const override;

    PayeeList *list (void) const;
    void setList (PayeeList *list);

private:
    PayeeList *mList;
};

#endif // PAYEEMODEL_H
