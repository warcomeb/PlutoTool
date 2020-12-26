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

#include "payeetype.h"

class Payee
{
public:
    Payee();

private:
    quint32   mId;
    QString   mCode;
    QString   mName;
    PayeeType mType;
    QString   mEmail;
    QString   mPhoneNumber;
    // Address section
    QString   mStreet;
    QString   mCity;
    QString   mState;
    QString   mCountry;
    QString   mPostalCode;
    // Personal/Company code
    QString   mVATID;
    QString   mNIN;
    bool      mActive;
    QString   mNote;
};

#endif // PAYEE_H
