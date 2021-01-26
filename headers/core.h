#pragma once
#include<QQmlApplicationEngine>
#include <QObject>
#include"headers/helpers/notifierHelper.h"
#include"headers/helpers/vibrationHelper.h"
#include"headers/helpers/stopwatchHelper.h"
#include"headers/helpers/timerHelper.h"
#include"headers/helpers/fileHelper.h"
#include"headers/helpers/savingSystemHelper.h"
#include"headers/helpers/audioHelper.h"

#if defined (Q_OS_ANDROID)
#include <QtAndroid>
#include"headers/org_artcompany_clock_NativeHelper.h"
#endif


static bool isApplicationcreate = false;

class Core : public QObject
{
    Q_OBJECT
private:
    StopWatchHelper _stopwatch;
    TimerHelper _timerHelper;
    NotifierHelper _notifier;
    FileHelper _fileHelper;
    VibrationHelper _vibration;
    SavingSystemHelper *_helper;
    AudioHelper *_audioHelper;
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    void setup();
    void init(QQmlApplicationEngine*engine);
    void registerQmlTypes(QQmlApplicationEngine*engine);
    //int invoke();
    Q_INVOKABLE void vibrate(int x);
#if defined (Q_OS_ANDROID)
   JNIEXPORT void JNICALL Java_org_artcompany_clock_NativeHelper_invokeVoidMethod
   (JNIEnv *env, jclass jClass, jint val)
    {
        Q_UNUSED(env);
        Q_UNUSED(jClass);
        if(isApplicationcreate==false)
            return;

        int arg = static_cast<int>(val);
        if(arg==100){
            qDebug()<<"ACTIVATE!!!!!!!!!";
            appActivation();
        }
        if(arg==101)
            appDeactivation();
    }
#endif
signals:
    void setupCompleted();
    void activation();
    void deactivation();
    void qmlCriticalError(QString message);
public slots:
    void reciveFromQml();
    void update();
    void onCriticalError(QString message);
    void appActivation();
    void appDeactivation();
};

