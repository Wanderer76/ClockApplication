#include "headers/core.h"
#include<QQmlContext>

#include"headers/models/timezonehandler.h"
#include"headers/models/worldtimelist.h"



Core::Core(QObject *parent) : QObject(parent)
{
    isApplicationcreate = true;
}

void Core::setup()
{
    emit setupCompleted();
}

void Core::init(QString mainProgrameFileName, QQmlApplicationEngine *engine)
{
    registerQmlTypes(engine);
}

void Core::registerQmlTypes(QQmlApplicationEngine*engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("Vibration",&vib);
    context->setContextProperty("Notifier",&notifier);
    context->setContextProperty("Stopwatch",&stopwatch);
    qmlRegisterType<TimeZoneHandler>("TimeZones",1,0,"TimeZones");
    qmlRegisterType<WorldTimeList>("WorldTimeList",1,0,"WorldTimeList");
    context->setContextProperty("core",this);

}

int Core::cpp_to_java_and_java_to_cpp()
{
    qWarning() << "Invoke: C++";
#if defined(Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/ClockApplication", "invoke", "(I)V", 30);
#endif
    return 1;
}
void Core::reciveFromQml()
{

}

void Core::update()
{

}

void Core::onCriticalError(QString message)
{

}

void Core::appActivation()
{

}

void Core::appDeactivation()
{

}
