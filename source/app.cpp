#include "headers/app.h"

App::App(int &argc, char **argv)
    :QApplication(argc,argv)
{
    running = false;
    connect(this,&App::applicationStateChanged,this,&App::onApplicationStateChange);
    connect(this,&App::aboutToQuit,&core,&Core::appDeactivation);
}

int App::exec()
{
    running = true;
    return QApplication::exec();
}

bool App::isRunning()
{
    return running;
}

void App::onApplicationStateChange(const Qt::ApplicationState state)
{
    if(state == Qt::ApplicationActive)
        core.appActivation();
    if(state == Qt::ApplicationSuspended)
        core.appDeactivation();
}
