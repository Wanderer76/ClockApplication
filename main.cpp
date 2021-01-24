#include <QApplication>
#include"headers/app.h"
#include"headers/main.h"


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

#if defined (Q_OS_ANDROID)
    auto result = QtAndroid::checkPermission(QString("android.permission.READ_EXTERNAL_STORAGE"));
       if(result == QtAndroid::PermissionResult::Denied){
           QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.READ_EXTERNAL_STORAGE","android.permission.WRITE_EXTERNAL_STORAGE"}));
           if(resultHash["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
               return 0;
       }
#endif


    return app.exec();
}
