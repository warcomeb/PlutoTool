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
#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H

#include <QObject>
#include <QList>
#include "category.h"

class CategoryList : public QObject
{
    Q_OBJECT
public:
    explicit CategoryList(QObject *parent = nullptr);

    QList<Category> items() const;

    void clear (void);
    void append (const Category& item);

signals:
    void preItemAppended ();
    void postItemAppended ();

    void preItemRemoved (int index);
    void postItemRemoved ();

private:
    QList<Category> mItems;
};

#endif // CATEGORYLIST_H
