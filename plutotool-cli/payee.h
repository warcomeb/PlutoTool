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
#ifndef PAYEE_H
#define PAYEE_H

#include <QtGlobal>
#include <QString>
#include <QJsonObject>

#include "payeetype.h"

class Payee
{
public:
    Payee ();
    Payee (PayeeType type);
    Payee (QString name, PayeeType type);
    Payee (QString name, PayeeType type, quint32 id);

    void defaultParams (void);

    QString name (void) const;

    void setId (quint32 id);
    quint32 id (void) const;

    QString code (void);

    PayeeType type (void) const;

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json, QMap<quint32,PayeeType> types);

    static bool compare (const Payee& p1, const Payee& p2)
    {
        if (p1.name() < p2.name())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    static QList<Payee> map2list (QMap<quint32,Payee> m)
    {
        QList<Payee> l;

        for (auto k : m.keys())
        {
            l.append(m[k]);
        }

        std::sort(l.begin(),l.end(),compare);
        return l;
    }

private:
    quint32    mId;
    QString    mCode;
    QString    mName;
    PayeeType  mType;
    QString    mEmail;
    QString    mPhoneNumber;
    // Address section
    QString    mStreet;
    QString    mCity;
    QString    mState;
    QString    mCountry;
    QString    mPostalCode;
    // Personal/Company code
    QString    mVATID;
    QString    mNIN;
    bool       mActive;
    QString    mNote;
};

#endif // PAYEE_H
