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
    _running = true;
#if defined (Q_OS_ANDROID)
    QtAndroid::androidActivity().callMethod<void>("createNotifChannel","()V");

#endif
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
