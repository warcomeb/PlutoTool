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

#ifndef WLOG_H
#define WLOG_H

#include <QString>
#include <QDateTime>

#include "iostream"
using namespace std;

class WLog
{
private:
    WLog() {};

    quint8 verbose;

public:

    static WLog& instance (void)
    {
        static WLog _instance;
//        if (_instance == 0)
//        {
//            _instance = new WLog();
//        }
        return _instance;
    };

    void setVerboseLevel (qint8 level)
    {
        verbose = level;
    }

    static QString currentTime (void)
    {
        QDateTime c = QDateTime::currentDateTime();
        return c.toString("yyyy.MM.dd hh:mm:ss.zzz");
    };

    void log (QString text, quint8 level)
    {
        if (level <= verbose)
        {
            cout << currentTime().toUtf8().data()  << " " << text.toUtf8().data() << "\r\n";
        }
    };

//    static void info (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [INFO] " << text.toUtf8().data() << "\r\n";
//    };

//    static void warning (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [WARN] " << text.toUtf8().data() << "\r\n";
//    };

//    static void danger (QString text)
//    {
//        cout << currentTime().toUtf8().data()  << " [DANG] " << text.toUtf8().data() << "\r\n";
//    };

    void error (QString text)
    {
        cerr << currentTime().toUtf8().data()  << " [ERR_] " << text.toUtf8().data() << "\r\n";
    };


};

#endif // WLOG_H
