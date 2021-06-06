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
#ifndef CATEGORY_H
#define CATEGORY_H

#include <QtGlobal>
#include <QString>

#include <QJsonObject>

class Category
{
public:
    Category ();
    Category (QString name, QString subName);
    Category (QString name, QString subName, quint32 id);

    QString name (void) const;
    QString subName (void) const;
    QString completeName (void) const;
    QString description (void);

    void setId (quint32 id);
    quint32 id (void) const;

    void write (QJsonObject &json) const;
    void read (const QJsonObject &json);

    QString toString (void);

    static bool compare (const Category& c1, const Category& c2)
    {
        if (c1.name() < c2.name())
        {
            return true;
        }
        else if (c1.name() > c2.name())
        {
            return false;
        }
        else
        {
            if (c1.subName() < c2. subName())
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

    static QList<Category> map2list (QMap<quint32,Category> m)
    {
        QList<Category> l;

        for (auto k : m.keys())
        {
          l.append(m[k]);
        }

        std::sort(l.begin(),l.end(),compare);
        return l;
    }

private:
    quint32 mId;
    QString mName;
    QString mSubName;
    QString mDescription;
};

#endif // CATEGORY_H
