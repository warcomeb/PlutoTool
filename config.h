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
    COMMAND_ADD_ACCOUNT,
    COMMAND_ADD_TRANSACTION,
    COMMAND_GET_ACCOUNTS,
    COMMAND_GET_PAYEES,
    COMMADN_GET_CATEGORIES,
    COMMADN_GET_WORKORDERS,
    COMMAND_ERROR,
};

/*!
 * \brief The Config struct
 */
struct Config
{
    QString database;
    bool replace;

    Command cmd;

    // User parameters
    QString uName;
    QString uSurname;
    QString uUsername;

    // Account parameters
    QString aName;
    QString aNumber;
    QString aNote;
    quint32 aType;
};


#endif // CONFIG_H
