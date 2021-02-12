#pragma once
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include <QObject>
class NetworkHelper : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager*_networkManager;

    NetworkHelper(QObject*pwgt=nullptr);
public:
    static NetworkHelper* getInstance();
    NetworkHelper(const NetworkHelper&) = delete;
    void operator=(const NetworkHelper&) = delete;
    void setRequest(const QString&request);
signals:
    void resultReady(QNetworkReply*reply);
};

