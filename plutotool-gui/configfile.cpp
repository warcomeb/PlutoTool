#include "configfile.h"
#include <QFile>
#include <QTextStream>
#include <QSettings>

#include <QDebug>

ConfigFile::ConfigFile (QObject *parent) :
    QObject(parent)
{

}

void ConfigFile::read (void)
{
    QSettings settings("config.ini",QSettings::IniFormat);

    settings.beginGroup("CLI");
    mCliToolPath = settings.value("path").toString();
    settings.endGroup();

    settings.beginGroup("DATABASE");
    mDatabasePath = settings.value("path").toString();
    settings.endGroup();
}

bool ConfigFile::write (const QString& data)
{
//    QFile file(mSource);
//    if (!file.open(QFile::WriteOnly))
//        return false;

//    QTextStream out(&file);
//    out << data;

//    qDebug() << file.;

//    file.close();
    return true;
}
