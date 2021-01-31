#include "database.h"
#include "utils/wlog.h"
#include "metadata.h"
#include "config.h"
#include "plutotoolreport.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Database::Database()
{

}

bool Database::create (Config config)
{
    WLog& log = WLog::instance();

    log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
    QFile data(config.database);
    if (openDatabaseFile(config,data,QIODevice::WriteOnly) == false) return false; // FAIL!

    log.log(QString("Create first user..."),LOG_IMPORTANT_INFORMATION);
    mUserNextId = 1;
    if (!addUser(config))
    {
        log.log(QString(PLUTOTOOL_USER_FAIL_ADD_NEW_),LOG_VIP_INFORMATION);
        return false;
    }

    log.log(QString("Create default categories..."),LOG_MEDIUM_INFORMATION);
    mCategoryNextId = 1;
    createDefaultCategory();

    log.log(QString("Create default workorder..."),LOG_MEDIUM_INFORMATION);
    mWorkOrderNextId = 1;
    WorkOrder w = WorkOrder();
    w.setId(mWorkOrderNextId++);
    mWorkOrders.insert(w.id(),w);
    log.log(QString("Work Order %1 (%2) has been added!").arg(w.name()).arg(w.code()),LOG_MEDIUM_INFORMATION);

    log.log(QString("Create default account type..."),LOG_MEDIUM_INFORMATION);
    mAccountTypeNextId = 1;
    createDefaultAccountType();

    mAccountNextId = 1;

    log.log(QString("Create default payee type..."),LOG_MEDIUM_INFORMATION);
    mPayeeTypeNextId = 1;
    createDefaultPayeeType();

    log.log(QString("Create default payee..."),LOG_MEDIUM_INFORMATION);
    mPayeeNextId = 1;
    Payee p = Payee(mPayeeTypes[1]);
    p.setId(mPayeeNextId++);
    mPayees.insert(p.id(),p);
    log.log(QString("Payee %1 (%2) has been added!").arg(p.name()).arg(p.code()),LOG_MEDIUM_INFORMATION);

    mTransactionNextId = 1;

    mScheduledNextId = 1;

    log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
    save(&data);
    log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);

    return true;
}

bool Database::load (Config config)
{
    WLog& log = WLog::instance();

    log.log(QString("Check database file: open file..."),LOG_IMPORTANT_INFORMATION);
    QFile data(config.database);
    if (openDatabaseFile(config,data,QIODevice::ReadOnly) == false) return false; // FAIL!

    // Read current database status...
    log.log(QString("Read database..."),LOG_IMPORTANT_INFORMATION);
    read(&data);
    closeDatabaseFile(data);

    return true;
}

bool Database::store (Config config)
{
    WLog& log = WLog::instance();

    // Save the new database....
    log.log(QString("Save database..."),LOG_IMPORTANT_INFORMATION);
    QFile data(config.database);
    if (openDatabaseFile(config,data,QIODevice::WriteOnly) == false) return false; // FAIL!
    save(&data);
    closeDatabaseFile(data);
    log.log(QString("Save database END!"),LOG_IMPORTANT_INFORMATION);

    return true;
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


bool Database::openDatabaseFile (Config config, QFile& db, QIODevice::OpenMode flags, bool checkReplace)
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
            if (config.replace == false)
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

bool Database::addUser (Config config)
{
    WLog& log = WLog::instance();

    if ((!config.uName.isNull()) && (!config.uSurname.isNull()))
    {
        User u(config.uName,config.uSurname,mUserNextId);
        mUsers.insert(u.id(),u);
        mUserNextId++;

        log.log(QString("User %1 %2 (%3) has been added!").arg(u.name()).arg(u.surname()).arg(u.code()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}

bool Database::addAccount (Config config)
{
    WLog& log = WLog::instance();

    if ((!config.aName.isNull()) && (!config.aNumber.isNull()) && (config.aType > 0))
    {
        if (mAccountTypes.contains(config.aType))
        {
            Account a(config.aName,config.aNumber,mAccountTypes[config.aType],mAccountNextId,true);
            mAccounts.insert(a.id(),a);
            mAccountNextId++;

            log.log(QString("Account %1 has been added!").arg(a.id()),LOG_MEDIUM_INFORMATION);
            return true;
        }
    }
    return false;
}

bool Database::addAccountType (Config config)
{
    WLog& log = WLog::instance();

    if (!config.atName.isNull())
    {
        AccountType at(config.atName,mAccountTypeNextId);

        if (!config.atDescription.isNull())
        {
            at.setDescription(config.atDescription);
        }
        mAccountTypes.insert(at.id(),at);
        mAccountTypeNextId++;

        log.log(QString("Account Type %1 has been added!").arg(at.id()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}

bool Database::addPayee (Config config)
{
    WLog& log = WLog::instance();

    if ((!config.pName.isNull()) && (config.pType > 0))
    {
        if (mPayeeTypes.contains(config.pType))
        {
            Payee p(config.pName,mPayeeTypes[config.pType],mPayeeNextId);
            mPayees.insert(p.id(),p);
            mPayeeNextId++;

            log.log(QString("Payee %1 has been added!").arg(p.id()),LOG_MEDIUM_INFORMATION);
            return true;
        }
    }
    return false;
}

bool Database::addPayeeType (Config config)
{
    WLog& log = WLog::instance();

    if (!config.ptName.isNull())
    {
        PayeeType pt(config.ptName,mPayeeTypeNextId);

        if (!config.ptDescription.isNull())
        {
            pt.setDescription(config.ptDescription);
        }
        mPayeeTypes.insert(pt.id(),pt);
        mPayeeTypeNextId++;

        log.log(QString("Payee Type %1 has been added!").arg(pt.id()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}

bool Database::addWorkOrder (Config config)
{
    WLog& log = WLog::instance();

    if (!config.wName.isNull() && !config.wEnd.isNull())
    {
        QDate dStart;
        QDate dEnd;

        dEnd = QDate::fromString(config.wEnd,"yyyy-MM-dd");
        if (!dEnd.isValid()) return false;

        if (config.wStart.isNull())
        {
            dStart = QDate::currentDate();
        }
        else
        {
            dStart = QDate::fromString(config.wStart,"yyyy-MM-dd");
            if (!dStart.isValid()) return false;
        }

        WorkOrder w(config.wName,dStart,dEnd,mWorkOrderNextId);
        if (!config.wDescription.isNull())
        {
            w.setDescription(config.wDescription);
        }
        mWorkOrders.insert(w.id(),w);
        mWorkOrderNextId++;

        log.log(QString("Workorder %1 has been added!").arg(w.id()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}

bool Database::addTransaction (Config config)
{
    WLog& log = WLog::instance();

    // Check if all values are valid
    if ((config.tAmount != 0.0f) &&
        (config.tType != Transaction::TYPE_ERROR) &&
        (((config.tType == Transaction::TYPE_INPUT) && (config.tAccountTo > 0)) ||
         ((config.tType == Transaction::TYPE_OUTPUT) && (config.tAccountFrom > 0)) ||
         ((config.tType == Transaction::TYPE_NEUTRAL) && (config.tAccountTo > 0) && (config.tAccountFrom > 0))) &&
        /*(config.tPayee > 0) &&*/ (config.tType > 0) && /*(config.tWorkorder > 0) &&*/ (config.tCategory > 0))
    {
        Account   aTo;
        Account   aFrom;
        Payee     p;
        WorkOrder w;
        Category  c;
        QDate     d;

        if ((config.tType != Transaction::TYPE_INPUT)  &&
            (config.tType != Transaction::TYPE_OUTPUT) &&
            (config.tType != Transaction::TYPE_NEUTRAL))
        {
            return false;
        }

        if (config.tAccountTo > 0)
        {
            if (mAccounts.contains(config.tAccountTo))
            {
                aTo = mAccounts[config.tAccountTo];
            }
            else
            {
                return false;
            }
        }

        if (config.tAccountFrom > 0)
        {
            if (mAccounts.contains(config.tAccountFrom))
            {
                aFrom = mAccounts[config.tAccountFrom];
            }
            else
            {
                return false;
            }
        }

        // Category
        if (config.tCategory > 0)
        {
            if (mCategories.contains(config.tCategory))
            {
                c = mCategories[config.tCategory];
            }
            else
            {
                return false;
            }
        }

        if (config.tDate.isNull())
        {
            d = QDate::currentDate();
        }
        else
        {
            d = QDate::fromString(config.tDate,"yyyy-MM-dd");
            if (!d.isValid()) return false;
        }

        if (config.tPayee > 0)
        {
            if (mPayees.contains(config.tPayee))
            {
                p = mPayees[config.tPayee];
            }
            else
            {
                return false;
            }
        }
        else
        {
            p = mPayees[1]; // Undefined
        }

        // WorkOrder
        if (config.tWorkorder > 0)
        {
            if (mWorkOrders.contains(config.tWorkorder))
            {
                w = mWorkOrders[config.tWorkorder];
            }
            else
            {
                return false;
            }
        }
        else
        {
            w = mWorkOrders[1]; // Undefined
        }

        // Create object!
        Transaction t(aFrom,aTo,p,d,config.tAmount,c,(Transaction::Type)config.tType,w);
        t.setId(mTransactionNextId);
        mTransactions.insert(t.id(),t);
        mTransactionNextId++;

        log.log(QString("Transaction %1 has been added!").arg(t.id()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}

bool Database::addScheduled (Config config)
{
    WLog& log = WLog::instance();

    // Check if all values are valid
    if ((config.sAmount != 0.0f) &&
        (config.sPayee > 0) &&
        (!config.sDeadline.isNull()) &&
        (config.sCategory > 0))
    {
        Payee     p;
        WorkOrder w;
        Category  c;
        QDate     d;

        if (mCategories.contains(config.sCategory))
        {
            c = mCategories[config.sCategory];
        }
        else
        {
            return false;
        }

        d = QDate::fromString(config.sDeadline,"yyyy-MM-dd");
        if (!d.isValid())
        {
            return false;
        }

        if (mPayees.contains(config.sPayee))
        {
            p = mPayees[config.sPayee];
        }
        else
        {
            return false;
        }

        // WorkOrder
        if (mWorkOrders.contains(config.sWorkorder))
        {
            w = mWorkOrders[config.sWorkorder];
        }
        else
        {
            return false;
        }

        // Create object!
        Scheduled s(p,d,config.sAmount,w,c);
        s.setId(mScheduledNextId);
        mScheduled.insert(s.id(),s);
        mScheduledNextId++;

        log.log(QString("Scheduled %1 has been added!").arg(s.id()),LOG_MEDIUM_INFORMATION);
        return true;
    }
    return false;
}
