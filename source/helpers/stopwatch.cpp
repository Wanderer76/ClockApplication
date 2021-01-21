#include "headers/helpers/stopwatch.h"
#include<QDebug>
#include<QTime>
#include<QApplication>

StopWatch::StopWatch(QObject *parent)
    : QObject{parent},
      _isRunning{false},
      _millisecondTime{0},
      _startTime{0},
      _timeBuff{0},
      _updateTime{0}

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
    return _isRunning;
}

void StopWatch::startStop()
{
    if(_timer.isActive())
    {
        _timeBuff+=_millisecondTime;
        _timer.stop();
        _isRunning = false;

    }
    else {
        _startTime = QTime::currentTime().msecsSinceStartOfDay();
        _timer.start();
        _isRunning = true;
    }
    emit sendState(_isRunning);
}

void StopWatch::onTime()
{
    _millisecondTime = QTime::currentTime().msecsSinceStartOfDay() - _startTime;
    _updateTime = _timeBuff + _millisecondTime;
    auto time = QTime::fromMSecsSinceStartOfDay(_updateTime);
    emit sendTime(time.toString("mm:ss:zzz"));
    QApplication::processEvents();
}

void StopWatch::reset()
{
    _timer.stop();
    _millisecondTime = 0;
    _timeBuff = 0;
    _updateTime = 0;
    _isRunning = false;
    auto time = "00:00:00";
    emit sendTime(time);
    emit sendState(_isRunning);
}

void StopWatch::lap()
{
    auto time = QTime::fromMSecsSinceStartOfDay(_updateTime);
    emit sendLap(time.toString("mm:ss:zzz"));
}
