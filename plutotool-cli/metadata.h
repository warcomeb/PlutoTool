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

#ifndef METADATA_H
#define METADATA_H

#define PROJECT_NAME                                 "PlutoTool"

#define PROJECT_VERSION_MAJOR                         1
#define PROJECT_VERSION_MINOR                         0
#define PROJECT_VERSION_SUBMINOR                      0

#define UTILITY_STRING(x)                             #x
#define UTILITY_STRING1(x)                            UTILITY_STRING(x)

#define PROJECT_VERSION_STRING1(x,y,z)                UTILITY_STRING1(x)"." UTILITY_STRING1(y) "." UTILITY_STRING1(z)
#define PROJECT_VERSION                               PROJECT_VERSION_STRING1(PROJECT_VERSION_MAJOR,PROJECT_VERSION_MINOR,PROJECT_VERSION_SUBMINOR)


//#define PROJECT_VERSION       "1.0.0.0"
#define PROJECT_DESCRIPTION   "Pluto - Family Cash Tool"

#define LOG_VIP_INFORMATION          0
#define LOG_IMPORTANT_INFORMATION    1
#define LOG_MEDIUM_INFORMATION       2
#define LOG_NOTIMPORTANT_INFORMATION 3
#endif // METADATA_H
