#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include"vibration.h"
#include"timezonehandler.h"
#include"stopwatch.h"
#include"worldtimelist.h"
#include"notifierclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Vibration vib;
    NotifierClient notifier;
    StopWatch stopwatch;
    qmlRegisterType<TimeZoneHandler>("TimeZones",1,0,"TimeZones");
    qmlRegisterType<WorldTimeList>("WorldTimeList",1,0,"WorldTimeList");
    engine.rootContext()->setContextProperty("Vibration",&vib);
    engine.rootContext()->setContextProperty("Notifier",&notifier);
    engine.rootContext()->setContextProperty("Stopwatch",&stopwatch);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
