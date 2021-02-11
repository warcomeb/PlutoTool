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

#include "plutodefault.h"

PlutoDefault::PlutoDefault()
{
    mAccountType << "Bank Account"
                 << "Wallet"
                 << "Credit Card"
                 << "Virtual Wallet"
                 << "Saving Account";

    mPayeeType << "Undefined"
               << "People"
               << "Bank"
               << "Bar"
               << "Shop"
               << "Resturant"
               << "Hospital"
               << "Doctor"
               << "Transport"
               << "Utilities"
               << "Mechanic";

    mCategory.insert("Transfer"     ,"-");
    // Income
    mCategory.insert("Income"       ,"Salary");
    mCategory.insert("Income"       ,"Refunds");
    mCategory.insert("Income"       ,"Gift");
    mCategory.insert("Income"       ,"Bank Loan");
    // Bills
    mCategory.insert("Bills"        ,"Electricity");
    mCategory.insert("Bills"        ,"Gas");
    mCategory.insert("Bills"        ,"Internet");
    mCategory.insert("Bills"        ,"Water");
    mCategory.insert("Bills"        ,"Garbage");
    mCategory.insert("Bills"        ,"PayTV");
    // Home
    mCategory.insert("Home Needs"   ,"Domestic Worker");
    mCategory.insert("Home Needs"   ,"Rent");
    mCategory.insert("Home Needs"   ,"Bank Loan");
    mCategory.insert("Home Needs"   ,"Repair");
    mCategory.insert("Home Needs"   ,"Food and co.");
    mCategory.insert("Home Needs"   ,"Other");
    // People
    mCategory.insert("People"       ,"Clothes");
    mCategory.insert("People"       ,"Breakfast");
    mCategory.insert("People"       ,"Lunch");
    mCategory.insert("People"       ,"Dinner");
    // Automobile
    mCategory.insert("Automobile"   ,"Parking");
    mCategory.insert("Automobile"   ,"Maintenance");
    mCategory.insert("Automobile"   ,"Fuel");
    mCategory.insert("Automobile"   ,"Insurance");
    mCategory.insert("Automobile"   ,"Highway");
    mCategory.insert("Automobile"   ,"Tax");
    mCategory.insert("Automobile"   ,"Buy");
    mCategory.insert("Automobile"   ,"Rent");
    mCategory.insert("Automobile"   ,"Penalty");
    // Entertainment
    mCategory.insert("Entertainment","Cinema");
}
