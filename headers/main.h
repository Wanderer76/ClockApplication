#pragma once
#include"core.h"
#include"app.h"
#include<QUrl>
#define APPCORE static_cast<App*>(qApp)->core

struct timeElement
{
    QString cityName;
    QString region = "";
    QString time;
    timeElement(const QString& city,const QString& time)
        :cityName(city),time(time)
    {}
};


struct AlarmElement
{
    QList<QString> days;
    QUrl sound;
    QString time;
    QString description;
    int longest;
    int pauseLongest;
    bool vibration;
    AlarmElement()
        :days{},sound{},time{""},description{"Будильник"},longest{0},pauseLongest{0},vibration{false}
    {}
};

enum Roles {
    Country= Qt::UserRole+1,
    Region,
    City,
    Time
};
