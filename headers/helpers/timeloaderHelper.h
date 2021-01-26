#pragma once
#include <QObject>
#include<QFile>
#include <QNetworkAccessManager>


#define TIMEZONESFILENAME "timezonedata.txt"
#define TIMEFILENAME "countries.txt"

class TimeLoaderHelper : public QObject
{
    Q_OBJECT
private:
    QFile _coutriesAndRegionsFile;
    QNetworkAccessManager* _manager;
    void writeToFile(const QByteArray&arr);
public:
    explicit TimeLoaderHelper(QObject*pwgt = nullptr);
    ~TimeLoaderHelper();
    void startRequest();
    QByteArray getTimeData();
private slots:
    void finishedRegionDownload(QNetworkReply*rep);
};

