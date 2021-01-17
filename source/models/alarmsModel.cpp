#include"headers/models/alarmsModel.h"

AlarmsModel::AlarmsModel()
{
    AlarmElement* element = new AlarmElement();
    element->days = {""};
    element->sound = "qrc:/songs/28. Lacrimosa.mp3";
    element->time = "20:15";
    element->description = "Будильник";
    element->longest = 10;
    element->pauseLongest = 5;
    element->vibration = true;
    _elements.append(element);
}

AlarmsModel::~AlarmsModel()
{

}

AlarmElement AlarmsModel::get(const int index)
{
    return *_elements.at(index);
}

QList<QString> AlarmsModel::getDays(const int index)
{
    return _elements.at(index)->days;
}

QUrl AlarmsModel::getSound(const int index)
{
    return _elements.at(index)->sound;
}

QString AlarmsModel::getTime(const int index)
{
    return _elements.at(index)->time;
}

QString AlarmsModel::getDescription(const int index)
{
    return _elements.at(index)->description;
}

int AlarmsModel::getLongest(const int index)
{
    return _elements.at(index)->longest;
}

int AlarmsModel::getPauseLongest(const int index)
{
    return _elements.at(index)->pauseLongest;
}

bool AlarmsModel::getVibration(const int index)
{
    return _elements.at(index)->vibration;
}

void AlarmsModel::remove(const int index)
{
    if(index >= _elements.size() || index < 0)
        return;
    beginRemoveRows(QModelIndex(),index,index);
    _elements.removeAt(index);
    endRemoveRows();
}

void AlarmsModel::append(QList<QString> days, QUrl sound, QString time, QString description, int longest, int pauseLongest, bool vibration)
{
    AlarmElement* element = new AlarmElement();
    element->days = days;
    element->sound = sound;
    element->time = time;
    element->description = description;
    element->longest = longest;
    element->pauseLongest = pauseLongest;
    element->vibration = vibration;

    beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
    _elements.append(element);
    endInsertRows();
}

int AlarmsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _elements.size();
}

QVariant AlarmsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return {};

    if(role==AlarmRoles::Days)
        return QVariant::fromValue(_elements.at(index.row())->days);

    if(role==AlarmRoles::Sound)
        return QVariant::fromValue(_elements.at(index.row())->sound);

    if(role==AlarmRoles::Time)
        return QVariant::fromValue(_elements.at(index.row())->time);

    if(role==AlarmRoles::Description)
        return QVariant::fromValue(_elements.at(index.row())->description);

    if(role==AlarmRoles::Longest)
        return QVariant::fromValue(_elements.at(index.row())->longest);

    if(role==AlarmRoles::PauseLongest)
        return QVariant::fromValue(_elements.at(index.row())->pauseLongest);

    if(role==AlarmRoles::Vibration)
        return QVariant::fromValue(_elements.at(index.row())->vibration);

    return {};
}

QHash<int, QByteArray> AlarmsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[AlarmRoles::Days] = "days";
    roles[AlarmRoles::Sound] = "sound";
    roles[AlarmRoles::Time] = "time";
    roles[AlarmRoles::Description] = "description";
    roles[AlarmRoles::Longest] = "longest";
    roles[AlarmRoles::PauseLongest] = "pauselongest";
    roles[AlarmRoles::Vibration] = "vibration";
    return roles;
}
