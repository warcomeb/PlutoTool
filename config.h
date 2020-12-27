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
    COMMAND_ERROR,
};

/*!
 * \brief The Config struct
 */
struct Config
{
    QString database;

    Command cmd;
};


#endif // CONFIG_H
