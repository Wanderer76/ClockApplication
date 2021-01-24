#include"headers/helpers/timerHelper.h"
#include<QDebug>

#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

TimerHelper::TimerHelper(QObject *pwgt)
    :QObject{pwgt},
      _hours{0},
      _minutes {0},
      _seconds {0},
      _currentValue{0},
      _maxValue {0}
{
    connect(this,&TimerHelper::valueChanged,this,&TimerHelper::recalculate);
}

TimerHelper::~TimerHelper()
{}

int TimerHelper::getCurrentValue() const
{
    return _currentValue;
}

void TimerHelper::setCurrentValue(int value)
{
    _currentValue = value;
}

void TimerHelper::startTimer()
{
#if defined (Q_OS_ANDROID)
     QtAndroid::androidContext().callMethod<void>("startService","()V");
#endif
}

void TimerHelper::stopTimer()
{
#if defined (Q_OS_ANDROID)
     QtAndroid::androidContext().callMethod<void>("stopService","()V");
#endif
}

void TimerHelper::recalculate()
{
    _maxValue = _seconds + _minutes * 60 + _hours * 3600;
    qDebug()<<_maxValue;
}


void TimerHelper::setSeconds(int value)
{
    _seconds = value;
    emit valueChanged();
}

void TimerHelper::setMinutes(int value)
{
    _minutes = value;
    emit valueChanged();
}

void TimerHelper::setHours(int value)
{
    _hours = value;
    emit valueChanged();
}


int TimerHelper::getMaxValue() const
{
    return _maxValue;
}

