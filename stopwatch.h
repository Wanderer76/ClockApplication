#pragma once
#include<QTimer>
#include <QObject>

class StopWatch : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(bool isRunning READ isActive)
private:
    bool isRunning;
    quint32 MillisecondTime;
    quint32 StartTime;
    quint32 TimeBuff;
    quint32 UpdateTime;
    QTimer _timer;
public:
    explicit StopWatch(QObject *parent = nullptr);
    ~StopWatch();
    Q_INVOKABLE void startTimer();
public slots:
    void onTime();
    void startStop();
    void reset();
    bool isActive() const;
signals:
    void sendTime(QString time);
    void sendState(bool isActive);
};

