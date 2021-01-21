#pragma once
#include<QObject>

class TimerHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double maxValue READ getMaxValue)
private:
    int _hours;
    int _minutes;
    int _seconds;
    int _currentValue;
    int _maxValue;
public:
    explicit TimerHelper(QObject*pwgt = nullptr);
    ~TimerHelper();
    Q_INVOKABLE int getMaxValue() const;
    Q_INVOKABLE void setSeconds(int value);
    Q_INVOKABLE void setMinutes(int value);
    Q_INVOKABLE void setHours(int value);
    Q_INVOKABLE int getCurrentValue() const;
    Q_INVOKABLE void setCurrentValue(int value);
    Q_INVOKABLE void startTimer();
signals:
    void valueChanged();
private slots:
    void recalculate();
};
