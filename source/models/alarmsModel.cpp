#include"headers/models/alarmsModel.h"
#include"headers/helpers/savingSystemHelper.h"

#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>

bool isUpdated = false;


AlarmsModel::AlarmsModel()
{
    _helper = SavingSystemHelper::getInstance(COMPANYNAME,APPNAME);
    connect(_helper,&SavingSystemHelper::write,this,[&](){
        qDebug()<<"Upadated - "<<isUpdated;
        if(isUpdated)
            writeData();
    });

    connect(_helper,&SavingSystemHelper::read,this,[&](){
        readData();
    });

}

AlarmsModel::~AlarmsModel()
{

}

AlarmElement AlarmsModel::get(const int index) const
{
    return *_elements.at(index);
}

QList<QString> AlarmsModel::getDays(const int index) const
{
    return _elements.at(index)->days;
}

QUrl AlarmsModel::getSound(const int index) const
{
    return _elements.at(index)->sound;
}

QString AlarmsModel::getTime(const int index) const
{
    return _elements.at(index)->time;
}

QString AlarmsModel::getDescription(const int index) const
{
    return _elements.at(index)->description;
}

int AlarmsModel::getLongest(const int index) const
{
    return _elements.at(index)->longest;
}

int AlarmsModel::getPauseLongest(const int index) const
{
    return _elements.at(index)->pauseLongest;
}

bool AlarmsModel::getVibration(const int index) const
{
    return _elements.at(index)->vibration;
}

bool AlarmsModel::getRepeat(const int index) const
{
    return _elements.at(index)->isRepeat;
}

void AlarmsModel::remove(const int index)
{
    if(index >= _elements.size() || index < 0)
        return;
    beginRemoveRows(QModelIndex(),index,index);
    _elements.removeAt(index);
    endRemoveRows();
    isUpdated = true;
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
    element->isRepeat = days.size()==0 ? false : true;
    beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
    _elements.append(element);
    endInsertRows();
    isUpdated = true;
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

    if(role==AlarmRoles::Repeat)
        return QVariant::fromValue(_elements.at(index.row())->isRepeat);

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
    roles[AlarmRoles::Repeat] = "repeat";
    return roles;
}

void AlarmsModel::writeData()
{
    QJsonObject data;
    int index = 0;
    for(auto &element : _elements){
        QJsonObject result;
        QJsonArray daysArray;

        for(auto &day : element->days)
            daysArray.append(day);

        result.insert("days",daysArray);
        result.insert("song",element->sound.toString());
        result.insert("time",element->time);
        result.insert("description",element->description);
        result.insert("longest",element->longest);
        result.insert("pauseLongest",element->pauseLongest);
        result.insert("vibration",element->vibration);
        result.insert("repeat",element->isRepeat);
        QJsonValue val(result);
        data.insert(QString::number(index),val);
        index++;
    }
    _helper->saveFile("alarms",data);
}

void AlarmsModel::readData()
{
    auto json = _helper->readFile("alarms.json");
    auto doc = QJsonDocument::fromJson(json);
    auto data = doc["alarms"].toObject();

    for(auto i :data)
    {
        auto element = i.toObject();
        auto alarm = new AlarmElement;

        QList<QString> days;
        for(auto day : element["days"].toArray())
        {
            days.append(day.toString());
        }
        alarm->days = days;
        alarm->sound = QUrl(element["song"].toString());
        alarm->time = element["time"].toString();
        alarm->description = element["description"].toString();
        alarm->longest = element["longest"].toInt();
        alarm->pauseLongest = element["pauseLongest"].toInt();
        alarm->vibration = element["vibration"].toBool();
        alarm->isRepeat = element["repeat"].toBool();

        beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
        _elements.append(std::move(alarm));
        endInsertRows();
    }
}
