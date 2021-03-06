#pragma once
#include<QQmlApplicationEngine>
#include <QObject>
#include"headers/helpers/vibrationHelper.h"
#include"headers/helpers/stopwatchHelper.h"
#include"headers/helpers/timerHelper.h"
#include"headers/helpers/fileHelper.h"
#include"headers/helpers/savingSystemHelper.h"
#include"headers/helpers/audioHelper.h"
#include"headers/helpers/networkhelper.h"
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
    FileHelper _fileHelper;
    VibrationHelper _vibration;
    SavingSystemHelper *_helper;
    AudioHelper *_audioHelper;
    NetworkHelper* _networkHelper;
public:
    explicit Core(QObject *parent = nullptr);
    ~Core();

    void setup();
    void init(QQmlApplicationEngine*engine);
    void registerQmlTypes(QQmlApplicationEngine*engine);
    //int invoke();
    Q_INVOKABLE void vibrate(int x);

signals:
    void setupCompleted();
    void activation();
    void deactivation();
    void qmlCriticalError(QString message);
    void doAlarm();
    void startAlarmService(QString song,int hour,int minute);
    void stopAlarmService();
    void startTimerService(int time);
    void stopTimerService();
public slots:
    void reciveFromQml();
    void update();
    void onCriticalError(QString message);
    void appActivation();
    void appDeactivation();
};

