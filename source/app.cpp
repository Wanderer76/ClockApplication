#include "headers/app.h"

App::App(int &argc, char **argv)
    :QApplication(argc,argv)
{
    _running = false;
    connect(this,&QApplication::applicationStateChanged,this,&App::onApplicationStateChange);
    connect(this,&QApplication::aboutToQuit,&core,&Core::appDeactivation);   
}

App::~App()
{

}

int App::exec()
{
#if defined (Q_OS_ANDROID)
    auto result = QtAndroid::checkPermission(QString("android.permission.READ_EXTERNAL_STORAGE"));
       if(result == QtAndroid::PermissionResult::Denied){
           QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.READ_EXTERNAL_STORAGE","android.permission.WRITE_EXTERNAL_STORAGE"}));
           if(resultHash["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied && resultHash["android.permission.WRITE_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied)
               return 0;
       }

#endif
    _running = true;
    return QApplication::exec();
}

bool App::isRunning() const
{
    return _running;
}

void App::onApplicationStateChange(const Qt::ApplicationState state)
{
    if(state == Qt::ApplicationActive)
        core.appActivation();
    if(state == Qt::ApplicationSuspended)
        core.appDeactivation();
}
