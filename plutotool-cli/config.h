#ifndef CONFIG_H
#define CONFIG_H

#include <QString>

/*!
 * \brief The BOM_Format enum
 */
enum Command
{
    COMMAND_LIST,
    COMMAND_INIT,
    COMMAND_STATUS,

    COMMAND_ADD_USER,
    COMMAND_ADD_ACCOUNT,
    COMMAND_ADD_ACCOUNTTYPE,
    COMMAND_ADD_PAYEE,
    COMMAND_ADD_PAYEETYPE,
    COMMAND_ADD_CATEGORY,
    COMMAND_ADD_WORKORDER,
    COMMAND_ADD_TRANSACTION,
    COMMAND_ADD_SCHEDULED,

    COMMAND_GET_ACCOUNTS,
    COMMAND_GET_PAYEES,
    COMMADN_GET_CATEGORIES,
    COMMADN_GET_WORKORDERS,
    COMMADN_GET_TRANSACTIONS,

    COMMAND_ERROR,
};

/*!
 * \brief The Config struct
 */
struct Config
{
    QString database;
    bool replace;

    bool noFormat;

    Command cmd;

    QString description;

    // Filter parameters
    quint32 account;
    quint32 payee;
    quint32 category;
    quint32 workorder;
    quint32 showUnpaidScheduled;

    // User parameters
    QString uName;
    QString uSurname;
    QString uUsername;

    // Account parameters
    QString aName;
    QString aNumber;
    QString aNote;
    quint32 aType;

    // AccountType parameters
    QString atName;
    QString atDescription;

    // Payee parameters
    QString pName;
    quint32 pType;

    // PayeeType parameters
    QString ptName;
    QString ptDescription;

    // Transaction parameters
    quint32 tAccountFrom;
    quint32 tAccountTo;
    quint32 tPayee;
    quint32 tCategory;
    quint32 tType;
    quint32 tWorkorder;
    float   tAmount;
    QString tDate;
    QString tNote;

    // Scheduled parameters
    quint32 sPayee;
    quint32 sCategory;
    quint32 sWorkorder;
    float   sAmount;
    QString sDeadline;
    QString sNote;
    bool    sPaid;

    // WorkOrder parameters
    QString wName;
    QString wStart;
    QString wEnd;
    QString wDescription;
};


#endif // CONFIG_H
