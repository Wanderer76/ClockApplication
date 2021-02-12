#include "headers/models/userWorldtimeModel.h"
#include<QTimer>
#include<QTime>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QTimeZone>

//static  QDateTime currentTime = QDateTime::currentDateTime();

UserWorldtimeModel::UserWorldtimeModel()
{
    _savingSystemHelper = SavingSystemHelper::getInstance();
    _timer = new QTimer(this);

    connect(_savingSystemHelper,&SavingSystemHelper::write,this,&UserWorldtimeModel::writeData);
    connect(_savingSystemHelper,&SavingSystemHelper::read,this,&UserWorldtimeModel::readData);
    connect(_timer,&QTimer::timeout,this,&UserWorldtimeModel::updateUserTime);

    _timer->setInterval(2000);
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

void UserWorldtimeModel::updateUserTime()
{
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
}

void UserWorldtimeModel::writeData()
{
    QJsonObject data;
    size_t count = 0;

    for(const auto element : qAsConst(_elements)) {
        QJsonObject result;

        result.insert("region",element->region);
        result.insert("cityName",element->cityName);

        QJsonValue val(result);
        data.insert(QString::number(count),val);
        count++;
    }
    _savingSystemHelper->saveFileWithRecordCount("userWorldTime",data,count);
}

void UserWorldtimeModel::readData()
{
    auto json = _savingSystemHelper->readFile("userWorldTime.json");
    auto doc = QJsonDocument::fromJson(json);
    auto data = doc["userWorldTime"].toObject();
    auto size = doc["size"].toInt();

    if(size == 0)
        return;

    beginInsertRows(QModelIndex(),0,size - 1);
    for(const auto i : data)
    {
        auto element = i.toObject();
        auto region = element["region"].toString();
        auto city = element["cityName"].toString();
        auto time = new timeElement(city,region,"");
        _elements.append(std::move(time));
    }
    endInsertRows();
    updateUserTime();
}
