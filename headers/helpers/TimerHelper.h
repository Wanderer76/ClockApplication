#pragma once
#include<QObject>

class TimerHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double maxValue READ getMaxValue)
private:
    int seconds;
    int minutes;
    int hours;
    int currentValue;
    int maxValue;
public:
    TimerHelper(QObject*pwgt = nullptr);
    Q_INVOKABLE int getMaxValue() const;
    Q_INVOKABLE void setSeconds(int value);
    Q_INVOKABLE void setMinutes(int value);
    Q_INVOKABLE void setHours(int value);
    Q_INVOKABLE int getCurrentValue() const;
    Q_INVOKABLE void setCurrentValue(int value);
signals:
    void valueChanged();
private slots:
    void recalculate();
};
