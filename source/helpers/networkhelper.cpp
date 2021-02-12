#include "headers/helpers/networkhelper.h"
#include<QDebug>

NetworkHelper::NetworkHelper(QObject*pwgt)
    :QObject(pwgt)
{
    _networkManager = new QNetworkAccessManager(this);
    connect(_networkManager,&QNetworkAccessManager::finished,this,[&](QNetworkReply*reply){
        if(reply->error())
            qDebug()<<"NetworkError - "<<reply->errorString();

        emit resultReady(reply);
    });
}

void NetworkHelper::setRequest(const QString &request)
{
    QUrl requestUrl(request);
    QNetworkRequest networkRequest(requestUrl);
    _networkManager->get(networkRequest);
}

NetworkHelper *NetworkHelper::getInstance()
{
    static NetworkHelper* _instance = nullptr;

    if(_instance == nullptr)
        _instance = new NetworkHelper();
    return _instance;
}
