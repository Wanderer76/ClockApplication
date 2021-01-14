#pragma once
#include <QObject>
#include<QFile>
#include <QNetworkAccessManager>


#define TIMEZONESFILENAME "timezonedata.txt"
#define TIMEFILENAME "countries.txt"

class TimeLoader : public QObject
{
    Q_OBJECT
private:
    QFile coutriesAndRegionsFile;
    QNetworkAccessManager* manager;
    void writeToFile(const QByteArray&arr);
public:
    TimeLoader(QObject*pwgt = nullptr);
    void startRequest();
    QByteArray getTimeData();
    ~TimeLoader();
private slots:
    void finishedRegionDownload(QNetworkReply*rep);
};

