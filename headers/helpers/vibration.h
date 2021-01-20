#pragma once
#include<QObject>


class Vibration : public QObject
{
    Q_OBJECT
public:
    explicit Vibration(QObject *parent = nullptr);
    ~Vibration();
public slots:
    void vibrate(int x);
signals:
    void click();
};


