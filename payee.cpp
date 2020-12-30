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
#include "payee.h"

Payee::Payee (PayeeType type):
    mType(type)
{
    mName = QString("Undefined");
    setId(0); // Not valid Id!
    defaultParams();
}

Payee::Payee (QString name, PayeeType type):
    mName(name),
    mType(type)
{
    setId(0); // Not valid Id!
    defaultParams();
}

void Payee::defaultParams (void)
{
    mEmail = QString("-");
    mPhoneNumber = QString("-");
    mStreet = QString("-");
    mCity = QString("-");
    mState = QString("-");
    mCountry = QString("-");
    mPostalCode = QString("-");
    mVATID = QString("-");
    mNIN = QString("-");
    mActive = true;
    mNote = QString("-");
}

QString Payee::name (void)
{
    return mName;
}

void Payee::setId (quint32 id)
{
    mId = id;
    mCode = QString("P%1").arg(id, 5, 10, QLatin1Char('0'));
}

quint32 Payee::id (void) const
{
    return mId;
}

QString Payee::code (void)
{
    return mCode;
}

void Payee::write (QJsonObject &json) const
{
    QJsonObject o;

    o["Id"]        = (int)mId;
    o["Code"]      = mCode;
    o["Name"]      = mName;
    o["PayeeType"] = (int)mType.id();

    json.insert("Payee", o);
}
