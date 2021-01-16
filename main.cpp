#include <QApplication>

#include"headers/app.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    App app(argc, argv);
    QQmlApplicationEngine engine;
    app.core.init(argv[0],&engine);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    if(engine.rootObjects().isEmpty())
        return -1;

    app.core.setup();

    return app.exec();
}
