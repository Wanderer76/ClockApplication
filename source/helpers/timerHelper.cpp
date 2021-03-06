#include"headers/helpers/timerHelper.h"
#include<QDebug>
#include"headers/main.h"

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
    //QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/TimerService","startTimerService","(Landroid/content/Context;)V",QtAndroid::androidActivity().object());
    emit APPCORE.startTimerService(_maxValue);
}

void TimerHelper::stopTimer()
{
     //QtAndroid::androidContext().callMethod<void>("stopTimerService","()V");
    emit APPCORE.stopTimerService();
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

