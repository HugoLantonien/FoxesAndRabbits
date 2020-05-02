#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include "territories.h"
#include "territoriestodraw.h"
#include "yearscounter.h"
#include "lapin.h"
#include "renard.h"
#include "chartdatas.h"

//#define NO_MMI

int main(int argc, char *argv[])
{

#ifdef NO_MMI
    Q_UNUSED(argc);
    Q_UNUSED(argv);



    yearsCounter::getInstance()->setNbOfYearToPlay(2000);
    yearsCounter::getInstance()->playYears();
    return 0;

#else


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    qmlRegisterType<TerritoriesToDraw>("myNature2", 1, 0, "TerritoriesToDraw" );

    qmlRegisterUncreatableType <Territories>("myNature2", 1, 0, "Territories", QStringLiteral("Territories shalln't be created in qml"));
    qmlRegisterUncreatableType <yearsCounter>("myNature2", 1, 0, "YearsCounter", QStringLiteral("yearsCounter shalln't be created in qml"));
    qmlRegisterUncreatableType <Lapin>("myNature2", 1, 0, "Lapin", QStringLiteral("Lapin shalln't be created in qml"));
    qmlRegisterUncreatableType <Renard>("myNature2", 1, 0, "Renard", QStringLiteral("Renard shalln't be created in qml"));
    qmlRegisterUncreatableType <ChartDatas>("myNature2", 1, 0, "ChartDatas", QStringLiteral("ChartDatas shalln't be created in qml"));

    yearsCounter *myYearCounter= yearsCounter::getInstance();
    Territories *myTerritories = Territories::getInstance();
    ChartDatas *myChartDatas = ChartDatas::getInstance();
    QQmlApplicationEngine engine;

    qDebug()<<engine.importPathList();

    engine.rootContext()->setContextProperty(QStringLiteral("yearCounterQml"), myYearCounter);
    engine.rootContext()->setContextProperty(QStringLiteral("territoriesQml"), myTerritories);
    engine.rootContext()->setContextProperty(QStringLiteral("chartDatasQml"), myChartDatas);
    engine.rootContext()->setContextProperty(QStringLiteral("applicationDirPath"), QGuiApplication::applicationDirPath());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
#endif
}
