#include "headers/core.h"
#include"headers/models/alarmsModel.h"
#include"headers/models/timezonehandler.h"
#include"headers/models/worldtimelist.h"
#include<QQmlContext>



Core::Core(QObject *parent) : QObject(parent)
{
    isApplicationcreate = true;
    _helper = SavingSystemHelper::getInstance(COMPANYNAME,APPNAME);
}

Core::~Core()
{

}

void Core::setup()
{
    emit setupCompleted();
    emit _helper->read();

}

void Core::init(QString mainProgrameFileName, QQmlApplicationEngine *engine)
{
    registerQmlTypes(engine);
}

void Core::registerQmlTypes(QQmlApplicationEngine*engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("Vibration",&_vibration);
    context->setContextProperty("Notifier",&_notifier);
    context->setContextProperty("TimerHelper",&_timerHelper);
    context->setContextProperty("Stopwatch",&_stopwatch);
    context->setContextProperty("FileHelper",&_fileHelper);
    qmlRegisterType<TimeZoneHandler>("TimeZones",1,0,"TimeZones");
    qmlRegisterType<WorldTimeList>("WorldTimeList",1,0,"WorldTimeList");
    qmlRegisterType<AlarmsModel>("AlarmsModel",1,0,"AlarmsModel");
    context->setContextProperty("core",this);

}

/*int Core::invoke()
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/ClockApplication", "invoke", "(I)V", 30);
#endif
    return 1;
}*/

void Core::vibrate(int x)
{
#if defined(Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/ClockApplication", "vibrate", "(I)V",x);
#endif
}


void Core::reciveFromQml()
{

}

void Core::update()
{

}

void Core::onCriticalError(QString message)
{
    qDebug()<<"Critical error - "<<message;

}

void Core::appActivation()
{
    if(isApplicationcreate == false)
        return;

    // QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/ClockApplication", "pushNotification", "()V");
    qDebug()<<"appActivation";
    //emit notifier.notificationChanged();
    emit activation();

}

void Core::appDeactivation()
{
    if(isApplicationcreate==false)
        return;
    qDebug()<<"appDeactivation";
    emit deactivation();
    emit _helper->write();
}
