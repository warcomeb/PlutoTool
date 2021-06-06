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
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QtGlobal>
#include <QString>

#include "accounttype.h"

class Account
{
public:
    Account ();
    Account (QString name, QString number, AccountType type, bool active);
    Account (QString name, QString number, AccountType type, quint32 id, bool active);

    QString name (void) const;
    QString number (void) const;
    AccountType type (void);
    bool active (void);

    void setId (quint32 id);
    quint32 id (void) const;

    QString code (void);

    bool isValid (void);

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json, QMap<quint32,AccountType> types);

    static bool compare (const Account& a1, const Account& a2)
    {
        if (a1.name() < a2.name())
        {
            return true;
        }
        else if (a1.name() > a2.name())
        {
            return false;
        }
        else
        {
            if (a1.number() < a2. number())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    static QList<Account> map2list (QMap<quint32,Account> m)
    {
        QList<Account> l;

        for (auto k : m.keys())
        {
            l.append(m[k]);
        }

        std::sort(l.begin(),l.end(),compare);
        return l;
    }

private:
    quint32     mId;
    QString     mCode;
    QString     mName;
    QString     mNumber;
    AccountType mType;
//    Payee       mPayee;
    bool        mActive;
    QString     mNote;
};

#endif // ACCOUNT_H
