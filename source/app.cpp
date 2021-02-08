#include "headers/app.h"


App::App(int &argc, char **argv)
    :QApplication(argc,argv)
{
    _running = false;
    connect(this,&QApplication::applicationStateChanged,this,&App::onApplicationStateChange);
    connect(this,&QApplication::aboutToQuit,&core,&Core::appDeactivation);

#if defined (Q_OS_ANDROID)
    connect(&core,&Core::startAlarmService,this,[](int hour,int minute){
        QtAndroid::androidActivity().callMethod<void>("startAlarmService","(II)V", hour, minute);
    });

    connect(&core,&Core::stopAlarmService,this,[](){
        QtAndroid::androidActivity().callMethod<void>("stopAlarmService");
    });

    connect(&core,&Core::startTimerService,this,[](int time){
        QtAndroid::androidActivity().callMethod<void>("startTimerService","(I)V",time);
    });

    connect(&core,&Core::stopTimerService,this,[](){
        QtAndroid::androidActivity().callMethod<void>("stopTimerService");
    });
#endif

}

App::~App()
{

}

int App::exec()
{
#if defined (Q_OS_ANDROID)
    auto result = QtAndroid::checkPermission(QString("android.permission.READ_EXTERNAL_STORAGE"));
    auto result1 = QtAndroid::checkPermission(QString("android.permission.WRITE_EXTERNAL_STORAGE"));
    auto result2 = QtAndroid::checkPermission(QString("android.permission.FOREGROUND_SERVICE"));
       if(result == QtAndroid::PermissionResult::Denied || result1 == QtAndroid::PermissionResult::Denied || result2 == QtAndroid::PermissionResult::Denied){
           QtAndroid::PermissionResultMap resultHash = QtAndroid::requestPermissionsSync(QStringList({"android.permission.READ_EXTERNAL_STORAGE","android.permission.WRITE_EXTERNAL_STORAGE","android.permission.FOREGROUND_SERVICE"}));
           if(resultHash["android.permission.READ_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied && resultHash["android.permission.WRITE_EXTERNAL_STORAGE"] == QtAndroid::PermissionResult::Denied &&resultHash["android.permission.FOREGROUND_SERVICE"] == QtAndroid::PermissionResult::Denied)
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
