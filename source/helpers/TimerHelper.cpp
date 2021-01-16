#include"headers/helpers/TimerHelper.h"
#include<QDebug>


TimerHelper::TimerHelper(QObject *pwgt)
    :QObject(pwgt)
{
    hours = 0;
    minutes = 0;
    seconds = 0;
    currentValue = 0;
    maxValue = 0;
    connect(this,&TimerHelper::valueChanged,this,&TimerHelper::recalculate);

}

int TimerHelper::getCurrentValue() const
{
    return currentValue;
}

void TimerHelper::setCurrentValue(int value)
{
    currentValue = value;
}

void TimerHelper::recalculate()
{
    maxValue = seconds + minutes * 60 + hours * 3600;
    qDebug()<<maxValue;
}


void TimerHelper::setSeconds(int value)
{
    seconds = value;
    emit valueChanged();
}

void TimerHelper::setMinutes(int value)
{
    minutes = value;
    emit valueChanged();
}

void TimerHelper::setHours(int value)
{
    hours = value;
    emit valueChanged();
}


int TimerHelper::getMaxValue() const
{
    return maxValue;
}

