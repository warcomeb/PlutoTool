#include "payeemodel.h"

PayeeModel::PayeeModel (QObject *parent)
    : QAbstractTableModel(parent),
      mList(nullptr)
{
}

int PayeeModel::rowCount (const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !mList)
        return 0;

    qDebug() << "PayeeModel::rowCount - list size: " << mList->items().size();
    return mList->items().size() + 1;
}

int PayeeModel::columnCount (const QModelIndex &parent) const
{
    if (parent.isValid() || !mList)
        return 0;

    return 3;
}

QVariant PayeeModel::data (const QModelIndex &index, int role) const
{
    qDebug() << "PayeeModel::data - Enter";
    if (!index.isValid() || !mList)
        return QVariant();

    qDebug() << "PayeeModel::data - role: " << role;
    switch (role)
    {
    case DataRole:
    {
        qDebug() << "PayeeModel::data - index.row(): " << index.row();
        qDebug() << "PayeeModel::data - index.column(): " << index.column();
        if (index.row() > 0)
        {
            const Payee item = mList->items().at(index.row() - 1);

            switch (index.column())
            {
            case IdColumn:
                return QString::number(item.id());
                break;
            case NameColumn:
                return QString(item.name());
                break;
            case TypeColumn:
                return QString(item.type().name());
                break;
            }
        }
        else
        {
            switch (index.column())
            {
            case IdColumn:
                return QString("Id");
                break;
            case NameColumn:
                return QString("Name");
                break;
            case TypeColumn:
                return QString("Type");
                break;
            }
        }
    }
        break;

    case HeadingRole:
        if (index.row() == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
        break;

    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> PayeeModel::roleNames () const
{
    QHash<int, QByteArray> names;
    names[HeadingRole] = "tableheading";
    names[DataRole] = "tabledata";
    return names;
}

PayeeList *PayeeModel::list (void) const
{
    return mList;
}

void PayeeModel::setList (PayeeList *list)
{
    beginResetModel();

    if (mList)
    {
        mList->disconnect(this);
    }

    mList = list;

    if (mList)
    {
        connect(mList, &PayeeList::preItemAppended, this, [=]()
        {
            const int index = mList->items().size();
            qDebug() << "PayeeList::preItemAppended";
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(mList, &PayeeList::postItemAppended, this, [=]()
        {
            qDebug() << "PayeeList::postItemAppended";
            endInsertRows();
        });
    }

    endResetModel();
}
