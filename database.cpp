#include "database.h"
#include "utils/wlog.h"
#include "metadata.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Database::Database()
{

}

void Database::readUsers (const QJsonObject &json)
{
    QJsonArray refs = json["Users"].toArray();
    for (int userIndex = 0; userIndex < refs.size(); ++userIndex)
    {
        QJsonObject userObject = refs[userIndex].toObject();
        User u;
        u.read(userObject["User"].toObject());
        mUsers.insert(u.id(),u);
    }

    if (json.contains("UserNextId") && json["UserNextId"].isDouble())
    {
        mUserNextId = json["UserNextId"].toInt();
    }
}

void Database::readCategories (const QJsonObject &json)
{
    QJsonArray refs = json["Categories"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        Category c;
        c.read(userObject["Category"].toObject());
        mCategories.insert(c.id(),c);
    }

    if (json.contains("CategoryNextId") && json["CategoryNextId"].isDouble())
    {
        mCategoryNextId = json["CategoryNextId"].toInt();
    }
}

void Database::readAccountTypes (const QJsonObject &json)
{
    QJsonArray refs = json["AccountTypes"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        AccountType at;
        at.read(userObject["AccountType"].toObject());
        mAccountTypes.insert(at.id(),at);
    }

    if (json.contains("AccountTypesNextId") && json["AccountTypesNextId"].isDouble())
    {
        mAccountTypeNextId = json["AccountTypesNextId"].toInt();
    }
}

void Database::readAccounts (const QJsonObject &json)
{
    QJsonArray refs = json["Accounts"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        Account a;
        a.read(userObject["Account"].toObject(),mAccountTypes);
        mAccounts.insert(a.id(),a);
    }

    if (json.contains("AccountNextId") && json["AccountNextId"].isDouble())
    {
        mAccountNextId = json["AccountNextId"].toInt();
    }
}

void Database::readPayeeTypes (const QJsonObject &json)
{
    QJsonArray refs = json["PayeeTypes"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        PayeeType pt;
        pt.read(userObject["PayeeType"].toObject());
        mPayeeTypes.insert(pt.id(),pt);
    }

    if (json.contains("PayeeTypesNextId") && json["PayeeTypesNextId"].isDouble())
    {
        mPayeeTypeNextId = json["PayeeTypesNextId"].toInt();
    }
}

void Database::readPayees (const QJsonObject &json)
{
    QJsonArray refs = json["Payees"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        Payee p;
        p.read(userObject["Payee"].toObject(),mPayeeTypes);
        mPayees.insert(p.id(),p);
    }

    if (json.contains("PayeesNextId") && json["PayeesNextId"].isDouble())
    {
        mPayeeNextId = json["PayeesNextId"].toInt();
    }
}

void Database::readWorkOrders (const QJsonObject &json)
{
    QJsonArray refs = json["WorkOrders"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        WorkOrder w;
        w.read(userObject["WorkOrder"].toObject());
        mWorkOrders.insert(w.id(),w);
    }

    if (json.contains("WorkOrderNextId") && json["WorkOrderNextId"].isDouble())
    {
        mWorkOrderNextId = json["WorkOrderNextId"].toInt();
    }
}

void Database::readTransactions (const QJsonObject &json)
{
    QJsonArray refs = json["Transactions"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        Transaction t;
        t.read(userObject["Transaction"].toObject(),mAccounts,mPayees,mCategories,mWorkOrders);
        mTransactions.insert(t.id(),t);
    }

    if (json.contains("TransactionNextId") && json["TransactionNextId"].isDouble())
    {
        mTransactionNextId = json["TransactionNextId"].toInt();
    }
}

void Database::readScheduled (const QJsonObject &json)
{
    QJsonArray refs = json["Scheduleds"].toArray();
    for (int index = 0; index < refs.size(); ++index)
    {
        QJsonObject userObject = refs[index].toObject();
        Scheduled s;
        s.read(userObject["Scheduled"].toObject(),mPayees,mCategories,mWorkOrders);
        mScheduled.insert(s.id(),s);
    }

    if (json.contains("ScheduledNextId") && json["ScheduledNextId"].isDouble())
    {
        mScheduledNextId = json["ScheduledNextId"].toInt();
    }
    else
    {
        mScheduledNextId = 1;
    }
}

void Database::writeUsers (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (User u, mUsers)
    {
        QJsonObject o;
        u.write(o);
        refs.push_back(o);
    }
    json["Users"] = refs;
    json["UserNextId"] = (int)mUserNextId;
}

void Database::writeCategories (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Category c, mCategories)
    {
        QJsonObject o;
        c.write(o);
        refs.push_back(o);
    }
    json["Categories"] = refs;
    json["CategoryNextId"] = (int)mCategoryNextId;
}

void Database::writeAccountTypes (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (AccountType at, mAccountTypes)
    {
        QJsonObject o;
        at.write(o);
        refs.push_back(o);
    }
    json["AccountTypes"] = refs;
    json["AccountTypesNextId"] = (int)mAccountTypeNextId;
}

void Database::writeAccounts (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Account a, mAccounts)
    {
        QJsonObject o;
        a.write(o);
        refs.push_back(o);
    }
    json["Accounts"] = refs;
    json["AccountNextId"] = (int)mAccountNextId;
}

void Database::writeTransactions (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Transaction t, mTransactions)
    {
        QJsonObject o;
        t.write(o);
        refs.push_back(o);
    }
    json["Transactions"] = refs;
    json["TransactionNextId"] = (int)mTransactionNextId;
}

void Database::writeScheduled (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Scheduled s, mScheduled)
    {
        QJsonObject o;
        s.write(o);
        refs.push_back(o);
    }
    json["Scheduleds"] = refs;
    json["ScheduledNextId"] = (int)mScheduledNextId;
}

void Database::writePayeeTypes (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (PayeeType p, mPayeeTypes)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["PayeeTypes"] = refs;
    json["PayeeTypesNextId"] = (int)mPayeeTypeNextId;
}

void Database::writePayees (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (Payee p, mPayees)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["Payees"] = refs;
    json["PayeesNextId"] = (int)mPayeeNextId;
}

void Database::writeWorkOrders (QJsonObject &json) const
{
    QJsonArray refs;
    foreach (WorkOrder p, mWorkOrders)
    {
        QJsonObject o;
        p.write(o);
        refs.push_back(o);
    }
    json["WorkOrders"] = refs;
    json["WorkOrderNextId"] = (int)mWorkOrderNextId;
}

bool Database::read (QFile* file)
{
    WLog& log = WLog::instance();

    QByteArray saveData = file->readAll();

    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject obj = loadDoc.object();

    log.log(QString("Read database: users information..."),LOG_MEDIUM_INFORMATION);
    readUsers(obj);

    log.log(QString("Read database: categories information..."),LOG_MEDIUM_INFORMATION);
    readCategories(obj);

    log.log(QString("Read database: accounts type information..."),LOG_MEDIUM_INFORMATION);
    readAccountTypes(obj);

    log.log(QString("Read database: accounts information..."),LOG_MEDIUM_INFORMATION);
    readAccounts(obj);

    log.log(QString("Read database: payees type information..."),LOG_MEDIUM_INFORMATION);
    readPayeeTypes(obj);

    log.log(QString("Read database: payees information..."),LOG_MEDIUM_INFORMATION);
    readPayees(obj);

    log.log(QString("Read database: work orders information..."),LOG_MEDIUM_INFORMATION);
    readWorkOrders(obj);

    log.log(QString("Read database: transactions information..."),LOG_MEDIUM_INFORMATION);
    readTransactions(obj);

    log.log(QString("Read database: scheduled information..."),LOG_MEDIUM_INFORMATION);
    readScheduled(obj);

    return true;
}

bool Database::save (QFile* file)
{
    WLog& log = WLog::instance();

    QJsonObject obj;

    log.log(QString("Save database: write users information..."),LOG_MEDIUM_INFORMATION);
    writeUsers(obj);

    log.log(QString("Save database: write categories information..."),LOG_MEDIUM_INFORMATION);
    writeCategories(obj);

    log.log(QString("Save database: write accounts type information..."),LOG_MEDIUM_INFORMATION);
    writeAccountTypes(obj);

    log.log(QString("Save database: write accounts information..."),LOG_MEDIUM_INFORMATION);
    writeAccounts(obj);

    log.log(QString("Save database: write payees type information..."),LOG_MEDIUM_INFORMATION);
    writePayeeTypes(obj);

    log.log(QString("Save database: write payees information..."),LOG_MEDIUM_INFORMATION);
    writePayees(obj);

    log.log(QString("Save database: write work orders information..."),LOG_MEDIUM_INFORMATION);
    writeWorkOrders(obj);

    log.log(QString("Save database: write transactions information..."),LOG_MEDIUM_INFORMATION);
    writeTransactions(obj);

    log.log(QString("Save database: write scheduled information..."),LOG_MEDIUM_INFORMATION);
    writeScheduled(obj);

    QJsonDocument doc(obj);

    file->write(doc.toJson());
    return true;
}

void Database::createDefaultAccountType (void)
{
    WLog& log = WLog::instance();

    AccountType a = AccountType("Bank Account",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Wallet",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Credit Card",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Virtual Wallet",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
    a = AccountType("Saving Account",mAccountTypeNextId++);
    mAccountTypes.insert(a.id(),a);
    log.log(QString("Account Type %1 has been added!").arg(a.name()),1);
}

void Database::createDefaultPayeeType (void)
{
    WLog& log = WLog::instance();

    PayeeType p = PayeeType("Undefined",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("People",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Bank",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Bar",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Shop",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Resturant",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Health",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Transport",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Utilities",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);

    p = PayeeType("Mechanic",mPayeeTypeNextId++);
    mPayeeTypes.insert(p.id(),p);
    log.log(QString("Payee Type %1 has been added!").arg(p.name()),1);
}

void Database::createDefaultCategory (void)
{
    WLog& log = WLog::instance();

    Category c = Category("Undefined","Undefined",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Transfer","",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Salary",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Refunds",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Income","Gift",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Electricity",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Gas",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Internet",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Water",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","Garbage",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Bills","PayTV",mCategoryNextId++); // Netflix, Disney+
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Home Needs","Domestic Worker",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    // ---------- Automobile
    c = Category("Automobile","Parking",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Maintenance",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Fuel",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Insurance",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Highway",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Tax",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Buy",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Car Rent",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);

    c = Category("Automobile","Penalty",mCategoryNextId++);
    mCategories.insert(c.id(),c);
    log.log(QString("Category <%1 - %2> has been added!").arg(c.name()).arg(c.subName()),LOG_MEDIUM_INFORMATION);
}


bool Database::openDatabaseFile (QFile& db, QIODevice::OpenMode flags, bool checkReplace)
{
    WLog& log = WLog::instance();
    if (flags == QIODevice::ReadOnly)
    {
        if (!db.exists())
        {
            log.log(QString(PLUTOTOOL_DATABASE_DOESNT_EXIST_),LOG_VIP_INFORMATION);
            return false;
        }
    }
    else if (flags == QIODevice::WriteOnly)
    {
        if (db.exists() && (checkReplace == true))
        {
            if (mConfig.replace == false)
            {
                log.log(QString(PLUTOTOOL_DATABASE_JUST_EXIST_),LOG_VIP_INFORMATION);
                return false;
            }
        }
    }
    else
    {
        return false;
    }

    if (!db.open(flags))
    {
        log.log(QString(PLUTOTOOL_DATABASE_CANT_OPEN_),LOG_VIP_INFORMATION);
        return false;
    }
    return true;
}

void Database::closeDatabaseFile (QFile& db)
{
    if (db.isOpen())
    {
        db.close();
    }
}

