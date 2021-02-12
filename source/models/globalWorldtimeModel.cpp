#include "headers/models/globalWorldtimeModel.h"

#include<QJsonDocument>
#include<QJsonArray>
#include<QTimeZone>


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
    if(role == WorldTimerRoles::Country)
        return _elements.at(index.row())->cityName;
    if(role == WorldTimerRoles::Region)
        return _elements.at(index.row())->region;
    if(role == WorldTimerRoles::Time)
        return _elements.at(index.row())->time;
    return {};
}

QHash<int, QByteArray> GlobalWorldtimeModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[WorldTimerRoles::Country] = "country";
    roles[WorldTimerRoles::Region] = "region";
    roles[WorldTimerRoles::Time] = "time";
    return roles;
}

void GlobalWorldtimeModel::createListOfElements()
{
    QTimeZone timeZone;
    QList<QByteArray> zones = timeZone.availableTimeZoneIds();

    beginInsertRows(QModelIndex(), 0, 0);
    for(const auto& element : zones)
    {
        if(!element.contains("GMT")){
            auto ls = element.split('/');
            if(ls.size()>1){
                _elements.append(new timeElement(ls[1],ls[0],""));
            }
        }
    }
    endInsertRows();
}
