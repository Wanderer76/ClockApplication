#include "headers/core.h"
#include"headers/models/alarmsModel.h"
#include"headers/models/globalWorldtimeModel.h"
#include"headers/models/userWorldtimeModel.h"
#include<QQmlContext>



Core::Core(QObject *parent) : QObject(parent)
{
    isApplicationcreate = true;
    _helper = SavingSystemHelper::getInstance();
    _audioHelper = AudioHelper::getInstance();
    _networkHelper = NetworkHelper::getInstance();
}

Core::~Core()
{

}

void Core::setup()
{
    emit setupCompleted();
    emit _helper->read();
  //  emit needAlarm(true);
}

void Core::init(QQmlApplicationEngine *engine)
{
    registerQmlTypes(engine);
}

void Core::registerQmlTypes(QQmlApplicationEngine*engine)
{
    QQmlContext *context = engine->rootContext();
    context->setContextProperty("Vibration",&_vibration);
    context->setContextProperty("TimerHelper",&_timerHelper);
    context->setContextProperty("Stopwatch",&_stopwatch);
    context->setContextProperty("FileHelper",&_fileHelper);
    context->setContextProperty("AudioHelper",_audioHelper);

    qmlRegisterType<GlobalWorldtimeModel>("GlobalWorldtimeModel",1,0,"GlobalWorldtimeModel");
    qmlRegisterType<UserWorldtimeModel>("UserWorldTimeModel",1,0,"UserWorldTimeModel");
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
    QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/MainActivity", "vibrate", "(I)V",x);
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

#if defined (Q_OS_ANDROID)
   JNIEXPORT void JNICALL Java_org_artcompany_clock_NativeHelper_invokeVoidMethod
   (JNIEnv *env, jclass jClass, jint val)
    {
        Q_UNUSED(env);
        Q_UNUSED(jClass);
  /*      if(isApplicationcreate==false)
            return;
*/
        int arg = static_cast<int>(val);
        if (arg == 100) {
            qDebug()<<"ACTIVATE!!!!!!!!!";
           APPCORE.appActivation();
        }
        else if (arg == 101)
            APPCORE.appDeactivation();

        else if (arg == 50)
        {
            qDebug()<<"Invoke ALAAAARM;););)";
            emit APPCORE.doAlarm();
        }
        else if (arg == 200)
        {
            auto activity = QtAndroid::androidActivity();
            auto packageManager = activity.callObjectMethod("getPackageManager",
                                                            "()Landroid/content/pm/PackageManager;");

            auto activityIntent = packageManager.callObjectMethod("getLaunchIntentForPackage",
                                                                  "(Ljava/lang/String;)Landroid/content/Intent;",
                                                                  activity.callObjectMethod("getPackageName",
                                                                  "()Ljava/lang/String;").object());

            auto pendingIntent = QAndroidJniObject::callStaticObjectMethod("android/app/PendingIntent", "getActivity",
                                                                           "(Landroid/content/Context;ILandroid/content/Intent;I)Landroid/app/PendingIntent;",
                                                                           activity.object(), jint(0), activityIntent.object(),
                                                                           QAndroidJniObject::getStaticField<jint>("android/content/Intent",
                                                                                                                   "FLAG_ACTIVITY_CLEAR_TOP"));

            auto alarmManager = activity.callObjectMethod("getSystemService",
                                                          "(Ljava/lang/String;)Ljava/lang/Object;",
                                                          QAndroidJniObject::getStaticObjectField("android/content/Context",
                                                                                                  "ALARM_SERVICE",
                                                                                                  "Ljava/lang/String;").object());

            alarmManager.callMethod<void>("set",
                                          "(IJLandroid/app/PendingIntent;)V",
                                          QAndroidJniObject::getStaticField<jint>("android/app/AlarmManager", "RTC"),
                                          jlong(QDateTime::currentMSecsSinceEpoch() + 100), pendingIntent.object());

            qApp->quit();
        }
    }
#endif
