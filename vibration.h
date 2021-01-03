#pragma once
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#include<QObject>

#include <QObject>

class Vibration : public QObject
{
    Q_OBJECT
public:
    explicit Vibration(QObject *parent = nullptr);
public slots:
    void vibrate(int x);

};


