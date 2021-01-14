#include "worldtimelist.h"
#include<QTimer>
#include<QTime>
#include<QCoreApplication>
#include<QDebug>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QJsonDocument>

QString parseJson(const QByteArray&array)
{
    auto document = QJsonDocument::fromJson(array);
    qDebug()<<document;
    auto utc_time = document["datetime"].toString();
    auto index = utc_time.indexOf("T");
    QString result;
    for(int i = index+1;i<index+6;i++)
        result += utc_time[i];
qDebug()<<result;
    return result;
}


WorldTimeList::WorldTimeList()
{
    _timer = new QTimer(this);

    _timer->setInterval(60000);
    connect(_timer,&QTimer::timeout,this,[&](){
        if(_elements.size()==0)
            return;

        for(auto& element : _elements)
        {

            QTime time = QTime::fromString(element->time);
            time = time.addSecs(60);
            element->time = time.toString("hh:mm");
            qDebug()<<element->time;
        }
        emit dataChanged(createIndex(0,0),createIndex(_elements.size(),0),QVector<int>{Roles::Time});
    });
    _elements.append(new timeElement("df","17:40"));
    _timer->start();
}

WorldTimeList::~WorldTimeList()
{}

void WorldTimeList::append(const QString &region, const QString &city)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;

    request.setUrl(QUrl("http://worldtimeapi.org/api/timezone/"+region+"/"+city));

    connect(manager,&QNetworkAccessManager::finished,this,
            [&](QNetworkReply*reply){
        if(reply->error()){
            qWarning()<<reply->errorString();
            return;
        }

        auto time = parseJson(reply->readAll());
        auto element = new timeElement(city,time);
        if(_elements.contains(element))
            return;
        beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
        _elements.append(element);
        endInsertRows();
    });
   QCoreApplication::processEvents();
    manager->get(request);
    qDebug()<<region<<city;

}

void WorldTimeList::remove(const int index)
{
    if(index<0||index>=_elements.size())
        return;
    beginRemoveRows(QModelIndex(),index,index);
    _elements.removeAt(index);
    endRemoveRows();
}

int WorldTimeList::rowCount(const QModelIndex &parent) const
{
    return _elements.size();
}

QVariant WorldTimeList::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    if(role == Roles::City)
        return QVariant::fromValue(_elements.at(index.row())->cityName);
    else if(role == Roles::Time)
        return QVariant::fromValue(_elements.at(index.row())->time);
    else if(role==Roles::Region)
        return {};
    else
        return {};
}

QHash<int, QByteArray> WorldTimeList::roleNames() const
{
    QHash<int,QByteArray> result;
    result[Roles::City] = "city";
    result[Roles::Time] = "time";
    result[Roles::Region] = "region";
    return result;
}

