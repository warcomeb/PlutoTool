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
    COMMAND_ADD_TRANSACTION,
    COMMAND_ERROR,
};

/*!
 * \brief The Config struct
 */
struct Config
{
    QString database;

    Command cmd;

    // User parameters
    QString uName;
    QString uSurname;
    QString uUsername;
};


#endif // CONFIG_H
