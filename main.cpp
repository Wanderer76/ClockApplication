#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include<QQmlContext>
#include"vibration.h"
#include"timezonehandler.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Vibration vib;
    TimeZoneHandler handler;

    qmlRegisterType<TimeZoneHandler>("TimeZones",1,0,"TimeZones");
    engine.rootContext()->setContextProperty("Vibration",&vib);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
