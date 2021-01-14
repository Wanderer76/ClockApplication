#include "worldtimelist.h"
#include<QTimer>
#include<QTime>
#include<QFile>
#include<QStandardPaths>
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
    manager = new QNetworkAccessManager(this);
    _timer = new QTimer(this);

    _timer->setInterval(60000);
    connect(_timer,&QTimer::timeout,this,[&](){
        if(_elements.size()==0)
            return;

        for(auto element : _elements)
        {

            QTime time = QTime::fromString(element->time);
            time = time.addSecs(60);
            element->time = time.toString("hh:mm");
            qDebug()<<element->time;
        }
        emit dataChanged(createIndex(0,0),createIndex(_elements.size(),0),QVector<int>{Roles::Time});
    });

    connect(manager,&QNetworkAccessManager::finished,this,
            [&](QNetworkReply*reply){
        if(reply->error()){
            qWarning()<<reply->errorString();
            return;
        }

        auto time = parseJson(reply->readAll());
        auto element = new timeElement(city,time);

        beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
        _elements.append(element);
        endInsertRows();
        _elements.last()->region = region;

    });


#if defined (Q_OS_ANDROID)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QFile file(path.append(("/" WorldTimes));
        #else
    QFile file(WorldTimes);
#endif
    if(file.size()>0&&file.open(QFile::ReadOnly)){
        QTextStream in(&file);
        auto text = in.readAll().split("|");
        for(auto&i : text)
        {
            auto temp = i.split(":");
            if(temp[0]!="")
                this->append(temp.at(0),temp.at(1));
        }
    }
    file.close();

    _timer->start();
}

WorldTimeList::~WorldTimeList()
{
    QFile file(WorldTimes);
    if(file.open(QFile::WriteOnly)){
        QTextStream in(&file);
        for(auto&i : _elements)
        {
            in<<i->region+":"+i->cityName<<"|";
        }
    }
    file.close();
}

void WorldTimeList::append(const QString &region, const QString &city)
{
    for(auto&i : _elements)
    {
        if(i->cityName == city)
            return;
    }

    this->region = region;
    this->city = city;
    QNetworkRequest request;
    request.setUrl(QUrl("http://worldtimeapi.org/api/timezone/"+region+"/"+city));
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
    Q_UNUSED(parent);
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

void WorldTimeList::writeDataSlot(QNetworkReply *reply)
{
}


Loader::Loader(QObject *pwgt)
    :QObject(pwgt)
{
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Loader::slotReadyRead);

}

Loader::~Loader(){}

void Loader::makeRequest(const QUrl &url)
{
    manager->get(QNetworkRequest(url));
    manager->blockSignals(true);
}

void Loader::slotReadyRead(QNetworkReply *reply)
{
    if(reply->error()){
        qDebug()<<reply->errorString();
        return;
    }
    QByteArray data;
    data = reply->readAll();
    emit dataReadyRead(data);
}
