/*
 * This file is part of PlutoTool
 *
 * Authors:
 *   Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * PlutoTool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * PlutoTool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QCoreApplication>

#include <QCommandLineParser>

#include "metadata.h"
#include "plutotool.h"
#include "config.h"

enum CLIParseResult
{
    CLI_PARSE_RESULT_OK,
    CLI_PARSE_RESULT_ERROR,
    CLI_PARSE_RESULT_VERSION,
    CLI_PARSE_RESULT_HELP,
};

Command getCommand (QString cmd)
{
    if ((cmd == "list") || (cmd == "LIST"))
    {
        return COMMAND_LIST;
    }
    else if ((cmd == "init") || (cmd == "INIT"))
    {
        return COMMAND_INIT;
    }
    else if ((cmd == "add-transaction") || (cmd == "ADD-TRANSACTION") ||
             (cmd == "add-trans")       || (cmd == "ADD-TRANS"))
    {
        return COMMAND_ADD_TRANSACTION;
    }
    return COMMAND_ERROR;
}

CLIParseResult parseCommandLine (QCommandLineParser &parser, Config *config, QString *errorMessage)
{
    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();

    const QCommandLineOption replaceOption(QStringList() << "r" << "replace",
            QCoreApplication::translate("main", "Replace the current database whether just exist"));
    parser.addOption(replaceOption);

    const QCommandLineOption uNameOption(QStringList() << "un" << "user-name",
            QCoreApplication::translate("main", "The <name> of the user to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(uNameOption);
    const QCommandLineOption uSurnameOption(QStringList() << "us" << "user-surname",
            QCoreApplication::translate("main", "The <surname> of the user to be added"),
            QCoreApplication::translate("main", "surname"));
    parser.addOption(uSurnameOption);
    const QCommandLineOption uUsernameOption(QStringList() << "uu" << "user-username",
            QCoreApplication::translate("main", "The <username> of the user that operate"),
            QCoreApplication::translate("main", "username"));
    parser.addOption(uUsernameOption);

    parser.addPositionalArgument("command", QCoreApplication::translate("main", "The command that must be executed."));
    parser.addPositionalArgument("database", QCoreApplication::translate("main", "The Pluto database in JSON format."));

    if (!parser.parse(QCoreApplication::arguments()))
    {
        *errorMessage = parser.errorText();
        return CLI_PARSE_RESULT_ERROR;
    }

    if (parser.isSet(replaceOption))
    {
        config->replace = true;
    }
    else
    {
        config->replace = false;
    }

    // USER options -----------------------------------------------------------
    if (parser.isSet(uNameOption))
    {
        config->uName = parser.value(uNameOption);
    }
    else
    {
        config->uName = QString::Null();
    }

    if (parser.isSet(uSurnameOption))
    {
        config->uSurname = parser.value(uSurnameOption);
    }
    else
    {
        config->uSurname = QString::Null();
    }

    if (parser.isSet(uUsernameOption))
    {
        config->uUsername = parser.value(uUsernameOption);
    }
    else
    {
        config->uUsername = QString::Null();
    }
    // ----------------------------------------------------------- USER options

    const QStringList positionalArguments = parser.positionalArguments();
    if (positionalArguments.isEmpty())
    {
        *errorMessage = "Error: Argument 'command' and 'database' missing.";
        return CLI_PARSE_RESULT_ERROR;
    }

    if (positionalArguments.size() != 2)
    {
        *errorMessage = "Wrong arguments number specified.";
        return CLI_PARSE_RESULT_ERROR;
    }

    config->cmd = getCommand(positionalArguments.at(0));

    // Save database file name
    config->database = positionalArguments.at(1);

    if (parser.isSet(helpOption))
    {
        return CLI_PARSE_RESULT_HELP;
    }

    if (parser.isSet(versionOption))
    {
        return CLI_PARSE_RESULT_VERSION;
    }

    return CLI_PARSE_RESULT_OK;
}

static PlutoTool* pluto;

int main (int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName(PROJECT_NAME);
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    QCommandLineParser parser;
    QString errorMessage;
    Config config;
    parser.setApplicationDescription(QCoreApplication::translate("main",PROJECT_DESCRIPTION));

    switch (parseCommandLine(parser,&config,&errorMessage))
    {
    case CLI_PARSE_RESULT_HELP:
        parser.showHelp();
        Q_UNREACHABLE();
    case CLI_PARSE_RESULT_VERSION:
        parser.showVersion();
        Q_UNREACHABLE();
    case CLI_PARSE_RESULT_ERROR:
        fputs(qPrintable("ERROR: "), stderr);
        fputs(qPrintable(errorMessage), stderr);
        fputs("\n\n", stderr);
        fputs(qPrintable(parser.helpText()), stderr);
        return 1;
    case CLI_PARSE_RESULT_OK:
        // Nothing to do!
        // Start parsing...
        break;
    default:
        return 1;
    }

    pluto = new PlutoTool(config);
    return 0;
}
