#include "stopwatch.h"
#include<QDebug>
#include<QTime>
#include<QCoreApplication>

StopWatch::StopWatch(QObject *parent)
    : QObject{parent},
      isRunning{false},
      MillisecondTime{0},
      StartTime{0},
      TimeBuff{0},
      UpdateTime{0}

{
    _timer.setInterval(20);
    connect(&_timer,&QTimer::timeout,this,&StopWatch::onTime);
}

StopWatch::~StopWatch()
{}

void StopWatch::startTimer()
{
    startStop();
}

bool StopWatch::isActive() const
{
    return isRunning;
}

void StopWatch::startStop()
{
    if(_timer.isActive())
    {
        TimeBuff+=MillisecondTime;
        _timer.stop();
        isRunning = false;

    }
    else {
        StartTime = QTime::currentTime().msecsSinceStartOfDay();
        _timer.start();
        isRunning = true;
    }
    emit sendState(isRunning);
}

void StopWatch::onTime()
{
    MillisecondTime = QTime::currentTime().msecsSinceStartOfDay() - StartTime;
    UpdateTime = TimeBuff + MillisecondTime;
    auto time = QTime::fromMSecsSinceStartOfDay(UpdateTime);
    emit sendTime(time.toString("mm:ss:zzz"));
    QCoreApplication::processEvents();
}

void StopWatch::reset()
{
    _timer.stop();
    MillisecondTime = 0;
    TimeBuff = 0;
    UpdateTime = 0;
    isRunning = false;
    auto time = "00:00:00";
    emit sendTime(time);
    emit sendState(isRunning);
}
