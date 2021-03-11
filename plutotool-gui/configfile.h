#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <QObject>

#include <QSettings>

class ConfigFile : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString cliToolPath
               READ cliToolPath
               WRITE setCliToolPath
               NOTIFY cliToolPathChanged)

    Q_PROPERTY(QString databasePath
               READ databasePath
               WRITE setDatabasePath
               NOTIFY databasePathChanged)

    explicit ConfigFile (QObject *parent = 0);

    Q_INVOKABLE void read(void);
    Q_INVOKABLE bool write (const QString& data);

    QString cliToolPath() { return mCliToolPath; };
    QString databasePath() { return mDatabasePath; };

public slots:
    void setCliToolPath(const QString& path) { mCliToolPath = path; };
    void setDatabasePath(const QString& path) { mDatabasePath = path; };

signals:
    void cliToolPathChanged (const QString& path);
    void databasePathChanged (const QString& path);
    void error (const QString& msg);

private:
    QSettings mSettings;

    QString   mCliToolPath;
    QString   mDatabasePath;
};

#endif // CONFIGFILE_H
