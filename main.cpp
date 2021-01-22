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
    else if ((cmd == "add-account") || (cmd == "ADD-ACCOUNT"))
    {
        return COMMAND_ADD_ACCOUNT;
    }
    else if ((cmd == "add-user") || (cmd == "ADD-USER"))
    {
        return COMMAND_ADD_USER;
    }
    else if ((cmd == "add-accounttype") || (cmd == "ADD-ACCOUNTTYPE"))
    {
        return COMMAND_ADD_ACCOUNTTYPE;
    }
    else if ((cmd == "add-payee") || (cmd == "ADD-PAYEE"))
    {
        return COMMAND_ADD_PAYEE;
    }
    else if ((cmd == "add-payeetype") || (cmd == "ADD-PAYEETYPE"))
    {
        return COMMAND_ADD_PAYEETYPE;
    }
    else if ((cmd == "add-workorder") || (cmd == "ADD-WORKORDER"))
    {
        return COMMAND_ADD_WORKORDER;
    }
    else if ((cmd == "get-accounts") || (cmd == "GET-ACCOUNTS"))
    {
        return COMMAND_GET_ACCOUNTS;
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

    const QCommandLineOption aNameOption(QStringList() << "an" << "account-name",
            QCoreApplication::translate("main", "The <name> of the account to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(aNameOption);
    const QCommandLineOption aNumberOption(QStringList() << "au" << "account-number",
            QCoreApplication::translate("main", "The <number> of the account to be added"),
            QCoreApplication::translate("main", "number"));
    parser.addOption(aNumberOption);
    const QCommandLineOption aTypeOption(QStringList() << "at" << "account-type",
            QCoreApplication::translate("main", "The <type> of the account to be added"),
            QCoreApplication::translate("main", "type"));
    parser.addOption(aTypeOption);
    const QCommandLineOption aNoteOption(QStringList() << "ae" << "account-note",
            QCoreApplication::translate("main", "The <note> of the account to be added"),
            QCoreApplication::translate("main", "note"));
    parser.addOption(aNoteOption);

    const QCommandLineOption atNameOption(QStringList() << "atn" << "accounttype-name",
            QCoreApplication::translate("main", "The <name> of the account type to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(atNameOption);
    const QCommandLineOption atDescriptionOption(QStringList() << "atd" << "accounttype-desc",
            QCoreApplication::translate("main", "The <description> of the account type to be added"),
            QCoreApplication::translate("main", "description"));
    parser.addOption(atDescriptionOption);

    const QCommandLineOption tAccountFromOption(QStringList() << "tf" << "transaction-accountfrom",
            QCoreApplication::translate("main", "The <id> number of the account where money comes from"),
            QCoreApplication::translate("main", "id"));
    parser.addOption(tAccountFromOption);
    const QCommandLineOption tAccountToOption(QStringList() << "tt" << "transaction-accountto",
            QCoreApplication::translate("main", "The <id> number of the account where money will go"),
            QCoreApplication::translate("main", "id"));
    parser.addOption(tAccountToOption);
    const QCommandLineOption tPayeeOption(QStringList() << "tp" << "transaction-payee",
            QCoreApplication::translate("main", "The <id> of the selected payee"),
            QCoreApplication::translate("main", "id"));
    parser.addOption(tPayeeOption);
    const QCommandLineOption tAmountOption(QStringList() << "ta" << "transaction-amount",
            QCoreApplication::translate("main", "The <ampount> of transaction"),
            QCoreApplication::translate("main", "amount"));
    parser.addOption(tAmountOption);
    const QCommandLineOption tTypeOption(QStringList() << "ty" << "transaction-type",
            QCoreApplication::translate("main", "The <type> of transaction: i input, o output, n neutral"),
            QCoreApplication::translate("main", "type"));
    parser.addOption(tTypeOption);
    const QCommandLineOption tCategoryOption(QStringList() << "tc" << "transaction-category",
            QCoreApplication::translate("main", "The <id> of transaction category"),
            QCoreApplication::translate("main", "id"));
    parser.addOption(tCategoryOption);
    const QCommandLineOption tDateOption(QStringList() << "td" << "transaction-date",
            QCoreApplication::translate("main", "The <date> of transaction, format is YYYY-MM-DD"),
            QCoreApplication::translate("main", "date"));
    parser.addOption(tDateOption);
    const QCommandLineOption tWorkorderOption(QStringList() << "tw" << "transaction-workorder",
            QCoreApplication::translate("main", "The workorder <id> to which to associate the transaction"),
            QCoreApplication::translate("main", "id"));
    parser.addOption(tWorkorderOption);

    const QCommandLineOption pNameOption(QStringList() << "pn" << "payee-name",
            QCoreApplication::translate("main", "The <name> of the payee to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(pNameOption);
    const QCommandLineOption pTypeOption(QStringList() << "pt" << "payee-type",
            QCoreApplication::translate("main", "The <type> of the payee to be added"),
            QCoreApplication::translate("main", "type"));
    parser.addOption(pTypeOption);

    const QCommandLineOption ptNameOption(QStringList() << "ptn" << "payeetype-name",
            QCoreApplication::translate("main", "The <name> of the payee type to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(ptNameOption);
    const QCommandLineOption ptDescriptionOption(QStringList() << "ptd" << "payeetype-desc",
            QCoreApplication::translate("main", "The <description> of the payee type to be added"),
            QCoreApplication::translate("main", "description"));
    parser.addOption(ptDescriptionOption);

    const QCommandLineOption wNameOption(QStringList() << "wn" << "workorder-name",
            QCoreApplication::translate("main", "The <name> of the workorder to be added"),
            QCoreApplication::translate("main", "name"));
    parser.addOption(wNameOption);
    const QCommandLineOption wDescriptionOption(QStringList() << "wd" << "workorder-desc",
            QCoreApplication::translate("main", "The <description> of the payee type to be added"),
            QCoreApplication::translate("main", "description"));
    parser.addOption(wDescriptionOption);
    const QCommandLineOption wStartDateOption(QStringList() << "ws" << "workorder-start",
            QCoreApplication::translate("main", "The start <date> of workorder, format is YYYY-MM-DD"),
            QCoreApplication::translate("main", "date"));
    parser.addOption(wStartDateOption);
    const QCommandLineOption wEndDateOption(QStringList() << "we" << "workorder-end",
            QCoreApplication::translate("main", "The end <date> of workorder, format is YYYY-MM-DD"),
            QCoreApplication::translate("main", "date"));
    parser.addOption(wEndDateOption);

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

    // PAYEE options ----------------------------------------------------------
    if (parser.isSet(pNameOption))
    {
        config->pName = parser.value(pNameOption);
    }
    else
    {
        config->pName = QString::Null();
    }

    if (parser.isSet(pTypeOption))
    {
        const QString type = parser.value(pTypeOption);
        bool conversionValue = false;
        const qint32 typeValue = type.toUInt(&conversionValue);
        if ((typeValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'pt' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->pType = (quint32)typeValue;
    }
    else
    {
        config->pType = 0;
    }
    // ---------------------------------------------------------- PAYEE options

    // PAYEE TYPE options -----------------------------------------------------
    if (parser.isSet(ptNameOption))
    {
        config->ptName = parser.value(ptNameOption);
    }
    else
    {
        config->ptName = QString::Null();
    }

    if (parser.isSet(ptDescriptionOption))
    {
        config->ptDescription = parser.value(ptDescriptionOption);
    }
    else
    {
        config->ptDescription = QString::Null();
    }
    // ----------------------------------------------------- PAYEE TYPE options


    // TRANSACTION options ----------------------------------------------------
    if (parser.isSet(tAccountToOption))
    {
        const QString aTo = parser.value(tAccountToOption);
        bool conversionValue = false;
        const qint32 aToValue = aTo.toUInt(&conversionValue);
        if ((aToValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'tt' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tAccountTo = (quint32)aToValue;
    }
    else
    {
        config->tAccountTo = 0;
    }

    if (parser.isSet(tAccountFromOption))
    {
        const QString aFrom = parser.value(tAccountFromOption);
        bool conversionValue = false;
        const qint32 aFromValue = aFrom.toUInt(&conversionValue);
        if ((aFromValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'tf' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tAccountFrom = (quint32)aFromValue;
    }
    else
    {
        config->tAccountFrom = 0;
    }

    if (parser.isSet(tPayeeOption))
    {
        const QString p = parser.value(tPayeeOption);
        bool conversionValue = false;
        const qint32 pValue = p.toUInt(&conversionValue);
        if ((pValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'tp' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tPayee = (quint32)pValue;
    }
    else
    {
        config->tPayee = 0;
    }

    if (parser.isSet(tWorkorderOption))
    {
        const QString w = parser.value(tWorkorderOption);
        bool conversionValue = false;
        const qint32 wValue = w.toUInt(&conversionValue);
        if ((wValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'tw' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tWorkorder = (quint32)wValue;
    }
    else
    {
        config->tWorkorder = 0;
    }

    if (parser.isSet(tCategoryOption))
    {
        const QString c = parser.value(tCategoryOption);
        bool conversionValue = false;
        const qint32 cValue = c.toUInt(&conversionValue);
        if ((cValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'tc' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tCategory = (quint32)cValue;
    }
    else
    {
        config->tCategory = 0;
    }

    if (parser.isSet(tAmountOption))
    {
        const QString amount = parser.value(tAmountOption);
        bool conversionValue = false;
        const float amountValue = amount.toFloat(&conversionValue);
        if ((amountValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'ta' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->tAmount = (quint32)amountValue;
    }
    else
    {
        config->tAmount = 0.0f;
    }

    if (parser.isSet(tTypeOption))
    {
        const QString t = parser.value(tTypeOption);
        if (t.length() == 1)
        {
            char c = t.at(0).toLatin1();
            if ((c == Transaction::TYPE_INPUT)  ||
                (c == Transaction::TYPE_OUTPUT) ||
                (c == Transaction::TYPE_NEUTRAL))
            {
                config->tType = c;
            }
            else
            {
                *errorMessage = "Error: Option 'ty' is not valid.";
                return CLI_PARSE_RESULT_ERROR;
            }
        }
        else
        {
            *errorMessage = "Error: Option 'ty' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
    }
    else
    {
        config->tType = Transaction::TYPE_ERROR;
    }

    if (parser.isSet(tDateOption))
    {
        config->tDate = parser.value(tDateOption);
    }
    else
    {
        config->tDate = QString::Null();
    }
    // ---------------------------------------------------- TRANSACTION options

    // ACCOUNT options --------------------------------------------------------
    if (parser.isSet(aNameOption))
    {
        config->aName = parser.value(aNameOption);
    }
    else
    {
        config->aName = QString::Null();
    }

    if (parser.isSet(aNumberOption))
    {
        config->aNumber = parser.value(aNumberOption);
    }
    else
    {
        config->aNumber = QString::Null();
    }

    if (parser.isSet(aNoteOption))
    {
        config->aNote = parser.value(aNoteOption);
    }
    else
    {
        config->aNote = QString::Null();
    }

    if (parser.isSet(aTypeOption))
    {
        const QString type = parser.value(aTypeOption);
        bool conversionValue = false;
        const qint32 typeValue = type.toUInt(&conversionValue);
        if ((typeValue < 1) || (conversionValue == false))
        {
            *errorMessage = "Error: Option 'at' is not valid.";
            return CLI_PARSE_RESULT_ERROR;
        }
        config->aType = (quint32)typeValue;
    }
    else
    {
        config->aType = 0;
    }
    // -------------------------------------------------------- ACCOUNT options

    // ACCOUNT TYPE options ---------------------------------------------------
    if (parser.isSet(atNameOption))
    {
        config->atName = parser.value(atNameOption);
    }
    else
    {
        config->atName = QString::Null();
    }

    if (parser.isSet(atDescriptionOption))
    {
        config->atDescription = parser.value(atDescriptionOption);
    }
    else
    {
        config->atDescription = QString::Null();
    }
    // -------------------------------------------------- ACCOUNT TYPE options

    // WORKORDER options -----------------------------------------------------
    if (parser.isSet(wNameOption))
    {
        config->wName = parser.value(wNameOption);
    }
    else
    {
        config->wName = QString::Null();
    }

    if (parser.isSet(wDescriptionOption))
    {
        config->wDescription = parser.value(wDescriptionOption);
    }
    else
    {
        config->wDescription = QString::Null();
    }

    if (parser.isSet(wStartDateOption))
    {
        config->wStart = parser.value(wStartDateOption);
    }
    else
    {
        config->wStart = QString::Null();
    }

    if (parser.isSet(wEndDateOption))
    {
        config->wEnd = parser.value(wEndDateOption);
    }
    else
    {
        config->wEnd = QString::Null();
    }
    // ----------------------------------------------------- WORKORDER options

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
