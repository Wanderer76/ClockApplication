#pragma once
#include<QTimer>
#include <QObject>

class StopWatch : public QObject
{
    Q_OBJECT
private:
    bool _isRunning;
    quint32 _millisecondTime;
    quint32 _startTime;
    quint32 _timeBuff;
    quint32 _updateTime;
    QTimer _timer;
public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();
    Q_INVOKABLE void startTimer();
public slots:
    void onTime();
    void startStop();
    void reset();
    void lap();
    bool isActive() const;
signals:
    void sendTime(QString time);
    void sendState(bool isActive);
    void sendLap(QString timeOfLap);
};

