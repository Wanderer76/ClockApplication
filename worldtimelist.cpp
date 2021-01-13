#include "worldtimelist.h"
#include<QTimer>
#include<QTime>
#include<QDebug>

WorldTimeList::WorldTimeList()
{
    _timer = new QTimer(this);

    _timer->setInterval(600);
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

    _elements.append(new timeElement("asdf","17:40"));
    _elements.append(new timeElement("asdf","16:40"));
    _elements.append(new timeElement("asdf","12:40"));
    _elements.append(new timeElement("asdf","19:40"));
    _timer->start();
}

WorldTimeList::~WorldTimeList()
{

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
    else
        return {};
}

QHash<int, QByteArray> WorldTimeList::roleNames() const
{
    QHash<int,QByteArray> result;
    result[Roles::City] = "city";
    result[Roles::Time] = "time";
    return result;
}

bool WorldTimeList::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool WorldTimeList::removeRows(int row, int count, const QModelIndex &parent)
{

}
