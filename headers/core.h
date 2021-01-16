#pragma once
#include<QQmlApplicationEngine>
#include <QObject>
#include"headers/helpers/notifierclient.h"
#include"headers/helpers/vibration.h"
#include"headers/helpers/stopwatch.h"

#if defined (Q_OS_ANDROID)
#include <QtAndroid>
#include"headers/org_artcompany_clock_NativeHelper.h"
#endif


static bool isApplicationcreate = false;

class Core : public QObject
{
    Q_OBJECT
private:
    Vibration vib;
    StopWatch stopwatch;
    NotifierClient notifier;

public:
    explicit Core(QObject *parent = nullptr);
    void setup();
    void init(QString mainProgrameFileName,QQmlApplicationEngine*engine);
    void registerQmlTypes(QQmlApplicationEngine*engine);
    int cpp_to_java_and_java_to_cpp();
#if defined (Q_OS_ANDROID)
   JNIEXPORT void JNICALL Java_org_artcompany_clock_NativeHelper_invokeVoidMethod
   (JNIEnv *env, jclass jClass, jint val)
    {
        Q_UNUSED(env);
        Q_UNUSED(jClass);
        if(isApplicationcreate==false)
            return;

        int arg = static_cast<int>(val);
        if(arg==100)
            appActivation();
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

