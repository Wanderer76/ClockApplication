#pragma once
#include"core.h"
#include"app.h"
#include<QUrl>

#define APPCORE static_cast<App*>(qApp)->core

#define COMPANYNAME "artcompany"

#define APPNAME "clockapplication"

struct timeElement
{
    QString cityName;
    QString region;
    QString time;
    timeElement(const QString& city,const QString& region,const QString time)
        :cityName(city),region(region),time(time)
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
    int pauseCount;
    bool vibration;
    bool isRepeat;
    bool isActive;

    AlarmElement()
        :
          days{},
          sound{},
          time{""},
          description{"Будильник"},
          longest{0},
          pauseLongest{0},
          pauseCount{0},
          vibration{false},
          isRepeat{days.size()>0},
          isActive{false}
    {}
};

enum WorldTimerRoles {
    Country= Qt::UserRole+1,
    Region,
    City,
    Time
};
