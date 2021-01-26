#include "headers/models/globalWorldtimeModel.h"
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QJsonDocument>
#include<QJsonArray>

GlobalWorldtimeModel::GlobalWorldtimeModel()
{
    createListOfElements();
}

GlobalWorldtimeModel::~GlobalWorldtimeModel()
{

}

int GlobalWorldtimeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _elements.size();
}

QVariant GlobalWorldtimeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};
    if(role == Roles::Country)
        return _elements.at(index.row())->cityName;
    if(role == Roles::Region)
        return _elements.at(index.row())->region;
    if(role == Roles::Time)
        return _elements.at(index.row())->time;
    return {};
}

QHash<int, QByteArray> GlobalWorldtimeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Roles::Country] = "country";
    roles[Roles::Region] = "region";
    roles[Roles::Time] = "time";
    return roles;
}

void GlobalWorldtimeModel::createListOfElements()
{
    TimeLoaderHelper *loader = new TimeLoaderHelper(this);
    loader->startRequest();
    parseJson(loader->getTimeData());
}

void GlobalWorldtimeModel::parseJson(const QByteArray &array)
{
    auto document = QJsonDocument::fromJson(array);
    auto jsonArray = document.array();
    size_t i = 0;
    for(auto item : jsonArray)
    {
        auto value = item.toString();
        if(value.contains('/')&&!value.contains("Etc"))
        {
            auto ls = value.split('/');
            qDebug()<<ls;
            beginInsertRows(QModelIndex(),i,i);
            _elements.append(new timeElement(ls[1],ls[0],""));
            endInsertRows();
            i++;
        }
    }
}
