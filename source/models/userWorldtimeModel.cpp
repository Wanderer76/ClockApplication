#include "headers/models/userWorldtimeModel.h"
#include<QTimer>
#include<QTime>
#include<QFile>
#include<QStandardPaths>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QJsonDocument>
#include<QTimeZone>

//static  QDateTime currentTime = QDateTime::currentDateTime();

UserWorldtimeModel::UserWorldtimeModel()
{

    _timer = new QTimer(this);

    _timer->setInterval(2000);
    connect(_timer,&QTimer::timeout,this,[&](){
        if(_elements.size()==0)
            return;
        QDateTime currentTime = QDateTime::currentDateTime();
        for(auto element : _elements)
        {
            QTimeZone newZone((element->region+"/"+element->cityName).toLatin1());
            auto newTime = currentTime.toTimeZone(newZone);
            element->time = newTime.toString("hh:mm");
        }
        emit dataChanged(createIndex(0,0),createIndex(_elements.size(),0),{WorldTimerRoles::Time});
    });



    _timer->start();
}

UserWorldtimeModel::~UserWorldtimeModel()
{
}

void UserWorldtimeModel::append(const QString &region, const QString &city)
{
    for(const auto i : _elements)
    {
        if(i->cityName == city)
            return;
    }
    QDateTime currentTime = QDateTime::currentDateTime();
    QTimeZone newZone((region+"/"+city).toLatin1());
    auto newTime = currentTime.toTimeZone(newZone);
    auto element = new timeElement(city,region,newTime.toString("hh:mm"));
    beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
    _elements.append(element);
    endInsertRows();

}

void UserWorldtimeModel::remove(const int index)
{
    if(index<0||index>=_elements.size())
        return;
    beginRemoveRows(QModelIndex(),index,index);
    _elements.removeAt(index);
    endRemoveRows();
}

int UserWorldtimeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _elements.size();
}

QVariant UserWorldtimeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    if(role == WorldTimerRoles::City)
        return QVariant::fromValue(_elements.at(index.row())->cityName);
    else if(role == WorldTimerRoles::Time)
        return QVariant::fromValue(_elements.at(index.row())->time);
    else if(role==WorldTimerRoles::Region)
        return QVariant::fromValue(_elements.at(index.row())->region);
    else
        return {};
}

QHash<int, QByteArray> UserWorldtimeModel::roleNames() const
{
    QHash<int,QByteArray> result;
    result[WorldTimerRoles::City] = "city";
    result[WorldTimerRoles::Time] = "time";
    result[WorldTimerRoles::Region] = "region";
    return result;
}
