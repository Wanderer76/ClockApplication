#pragma once
#include<QObject>


class VibrationHelper : public QObject
{
    Q_OBJECT
public:
    explicit VibrationHelper(QObject *parent = nullptr);
    ~VibrationHelper();
public slots:
    static void vibrate(int x);
};


