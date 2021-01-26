#include <QApplication>
#include"headers/app.h"
#include"headers/main.h"


int main(int argc, char *argv[])
{
QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    App app(argc, argv);
    QQmlApplicationEngine engine;
    app.core.init(&engine);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if(engine.rootObjects().isEmpty())
        return -1;

    app.core.setup();

    return app.exec();
}
