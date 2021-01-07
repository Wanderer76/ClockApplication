#pragma once
#include <QObject>
#include<QFile>
#include <QNetworkAccessManager>


#define TIMEZONESFILENAME "timezonedata.txt"

struct worldTimeElement
{
    QString countryName;
    QString regionName;
    QString time;
    worldTimeElement(QString country,QString region,QString time = "")
        :countryName(country),regionName(region), time(time)
    {}
};


class TimeLoader : public QObject
{
    Q_OBJECT
private:
    QFile file;
    QNetworkAccessManager*manager;
    void writeToFile(const QByteArray&arr);
public:
    TimeLoader(QObject*pwgt = nullptr);
    void startRequest(const QUrl&request);
    QByteArray getTimeData();
    ~TimeLoader();
};

