#ifndef PROCESS_H
#define PROCESS_H

#include <QProcess>
#include <QVariant>


class ProcessStarter : public QProcess
{
    Q_OBJECT

public:
    ProcessStarter(QObject *parent = 0) : QProcess(parent) { }
    virtual ~ProcessStarter() = default;

    Q_INVOKABLE void start(const QString &program, const QVariantList &arguments)
    {
        QStringList args;

        // convert QVariantList from QML to QStringList for QProcess

        for (int i = 0; i < arguments.length(); i++)
            args << arguments[i].toString();

        QProcess::start(program, args);
    }

    Q_INVOKABLE QByteArray readAll()
    {
        return QProcess::readAll();
    }

};

#endif // PROCESS_H
