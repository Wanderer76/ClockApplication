#include "timezonehandler.h"
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QJsonDocument>
#include<QJsonArray>

TimeZoneHandler::TimeZoneHandler()
{
    createListOfElements();
}

int TimeZoneHandler::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _elements.size();
}

QVariant TimeZoneHandler::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    if(role == Roles::Country)
        return _elements.at(index.row())->countryName;
    if(role == Roles::Region)
        return _elements.at(index.row())->regionName;
    if(role == Roles::Time)
        return _elements.at(index.row())->time;
    return {};
}

QHash<int, QByteArray> TimeZoneHandler::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::Country] = "country";
    roles[Roles::Region] = "region";
    roles[Roles::Time] = "time";
    return roles;
}

void TimeZoneHandler::createListOfElements()
{
    TimeLoader *loader= new TimeLoader();
    loader->startRequest(QUrl("http://worldtimeapi.org/api/timezone"));
    parseJson(loader->getTimeData());
}

void TimeZoneHandler::parseJson(QByteArray &&array)
{
    auto document = QJsonDocument::fromJson(array);
    auto jsonArray = document.array();
    size_t i = 0;
    for(auto item : jsonArray)
    {
        auto value = item.toString();
        if(value.contains('/')&&!value.contains("Etc"))
        {
            beginInsertRows(QModelIndex(),i,i);
            auto ls = value.split('/');
            _elements.append(new worldTimeElement(ls[1],ls[0]));
            endInsertRows();
            i++;
        }
    }
}

