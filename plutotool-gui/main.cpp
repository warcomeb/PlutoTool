#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "payeemodel.h"
#include "payeelist.h"

//#include "categorymodel.h"
#include "categorylist.h"

#include "process.h"

#include "tableparser.h"

#include "configfile.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PayeeModel>("PlutoTool", 1, 0, "PayeeModel");
    qmlRegisterUncreatableType<PayeeList>("PlutoTool", 1, 0, "PayeeList",
        QStringLiteral("PayeeList should not be created in QML"));

    qmlRegisterType<ProcessStarter>("Process", 1, 0, "ProcessStarter");

    qmlRegisterType<ConfigFile,1>("ConfigFile", 1, 0, "ConfigFile");

    PayeeList lPayeeList;
    CategoryList lCategoryList;

    TableParser lTableParser;
    lTableParser.setPayeeList(&lPayeeList);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("lPayeeList"), &lPayeeList);
    engine.rootContext()->setContextProperty(QStringLiteral("lCategoryList"), &lCategoryList);
    engine.rootContext()->setContextProperty(QStringLiteral("lTableParser"), &lTableParser);

    //ProcessStarter starter;
    //engine.rootContext()->setContextProperty(QStringLiteral("starter"), &starter);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
