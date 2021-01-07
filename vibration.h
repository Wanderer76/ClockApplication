#pragma once
#include<QObject>


class Vibration : public QObject
{
    Q_OBJECT
public:
    explicit Vibration(QObject *parent = nullptr);
public slots:
    void vibrate(int x);
};


