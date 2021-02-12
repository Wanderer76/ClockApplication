#include"headers/models/alarmsModel.h"
#include"headers/helpers/savingSystemHelper.h"
#include<QThread>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>

const QMap<QString,int> daysToInt = {
    {"Пн",1},
    {"Вт",2},
    {"Ср",3},
    {"Чт",4},
    {"Пт",5},
    {"Сб",6},
    {"Вс",7},
};

const QMap<int,QString> daysToString = {
    {1,"Пн"},
    {2,"Вт"},
    {3,"Ср"},
    {4,"Чт"},
    {5,"Пт"},
    {6,"Сб"},
    {7,"Вс"},
};

 int currentIndex = 0;
#if defined (Q_OS_ANDROID)
 static bool isServiceStart = false;
#endif

AlarmsModel::AlarmsModel()
{
    _updateTimer = new QTimer(this);

    _savingSystemHelper = SavingSystemHelper::getInstance();
    _audioHelper = AudioHelper::getInstance();

    connect(_savingSystemHelper,&SavingSystemHelper::write,this,[&](){
        writeData();
    });

    connect(_savingSystemHelper,&SavingSystemHelper::read,this,[&](){
        readData();
    });

    connect(_updateTimer,&QTimer::timeout,this,[&](){
        if(checkForAlarms())
        {
            _updateTimer->start(10000);
            _updateTimer->setInterval(1000);
        }
    });

    connect(&APPCORE,&Core::doAlarm,this,[&](){
        if(_elements.size() > 0){
            if(_elements.at(0)->isActive == true)
                    emit startAlarm(0);
        }
    });

    connect(_audioHelper,&AudioHelper::pauseAudio,this,[&](){
        emit this->pause();
    });
    connect(_audioHelper,&AudioHelper::startAudio,this,[&](){
        emit this->startAlarm(currentIndex);
    });
    connect(_audioHelper,&AudioHelper::stopAudio,this,[&](){
        emit this->stopAlarm();
    });

    connect(this,&AlarmsModel::startAlarm,this,[&](const int index){
        auto elem = _elements.at(index);
        _audioHelper->setPath(elem->sound.toString());
        _audioHelper->setDuration(elem->longest);
        _audioHelper->setPauseTime(elem->pauseLongest);
        _audioHelper->setPlayTime(elem->longest);
        _audioHelper->setPauseCount(elem->pauseCount);
        _audioHelper->setVibrate(elem->vibration);
        _audioHelper->start();
    });
    _updateTimer->setInterval(1000);
    _updateTimer->start();
}

AlarmsModel::~AlarmsModel()
{

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

bool AlarmsModel::getActive(const int index) const
{
    if(index<0 ||index>=_elements.size())
        return false;
    return _elements.at(index)->isActive;
}

void AlarmsModel::remove(const int index)
{
    if(index >= _elements.size() || index < 0)
        return;
    beginRemoveRows(QModelIndex(),index,index);
    _elements.removeAt(index);
    endRemoveRows();
}

void AlarmsModel::createAlarm(
        const QList<QString>& days,
        const QUrl& sound,
        const QString& time,
        const QString& description,
        const int longest,
        const int pauseLongest,
        const int pauseCount,
        const bool vibration
        )
{
    AlarmElement* element = new AlarmElement();
    element->days = days;
    element->sound = sound;
    element->time = time;
    element->description = description;
    element->longest = longest;
    element->pauseLongest = pauseLongest;
    element->pauseCount = pauseCount;
    element->vibration = vibration;
    element->isRepeat = days.size() == 0 ? false : true;
    element->isActive = true;
    beginInsertRows(QModelIndex(),_elements.size(),_elements.size());
    _elements.append(element);
    endInsertRows();
}

void AlarmsModel::editElement(const int index, const QList<QString> &days, const QUrl &sound, const QString &time, const QString &description, const int longest, const int pauseLongest, const int pauseCount, const bool vibration)
{
    AlarmElement* elemPtr = _elements.at(index);
    elemPtr->days = days;
    elemPtr->sound = sound;
    elemPtr->time = time;
    elemPtr->description = description;
    elemPtr->longest = longest;
    elemPtr->pauseLongest = pauseLongest;
    elemPtr->pauseCount = pauseCount;
    elemPtr->vibration = vibration;
    elemPtr->isRepeat = days.size() > 0 ? true : false;
    emit dataChanged(createIndex(index,0),createIndex(index,0));
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

    if(role == AlarmRoles::IsActive)
        return QVariant::fromValue(_elements.at(index.row())->isActive);

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
    roles[AlarmRoles::IsActive] = "isActive";
    return roles;
}

void AlarmsModel::writeData()
{
    QJsonObject data;
    size_t count = 0;

    for(const auto element : qAsConst(_elements)) {
        QJsonObject result;
        QJsonArray daysArray;

        for(const auto &day : qAsConst(element->days))
            daysArray.append(day);

        result.insert("days",daysArray);
        result.insert("song",element->sound.toString());
        result.insert("time",element->time);
        result.insert("description",element->description);
        result.insert("longest",element->longest);
        result.insert("pauseLongest",element->pauseLongest);
        result.insert("vibration",element->vibration);
        result.insert("repeat",element->isRepeat);
        result.insert("active",element->isActive);
        QJsonValue val(result);
        data.insert(QString::number(count),val);
        count++;
    }

    _savingSystemHelper->saveFileWithRecordCount("alarms",data,count);
}

void AlarmsModel::readData()
{
    auto json = _savingSystemHelper->readFile("alarms.json");
    auto doc = QJsonDocument::fromJson(json);
    auto data = doc["alarms"].toObject();
    auto size = doc["size"].toInt();
    if(size==0)
        return;
    beginInsertRows(QModelIndex(),0,size - 1);

    for(const auto i : data)
    {
        auto element = i.toObject();
        auto alarm = new AlarmElement;

        QList<QString> days;

        for(const auto day : element["days"].toArray())
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
        alarm->isActive = element["active"].toBool();

        _elements.append(std::move(alarm));
    }
    endInsertRows();
}



bool AlarmsModel::checkForAlarms()
{
#if defined (Q_OS_ANDROID)
    if(_elements.size() == 0)
    {
#if defined (Q_OS_ANDROID)
        if(isServiceStart){
            isServiceStart = false;
            emit APPCORE.stopAlarmService();
        }
#endif
        return false;
    }

    if(_elements.size() > 0 && isServiceStart == false && _elements.at(0)->isActive == true)
    {
        isServiceStart = true;
        auto time = _elements.at(0)->time.split(":");
        emit APPCORE.startAlarmService(_elements.at(0)->sound.toString(), time[0].toInt(), time[1].toInt());
    }
#endif

    QDateTime dateTime = QDateTime::currentDateTime();
    auto time = dateTime.time();

    auto hour = time.hour() < 10 ? "0" + QString::number(time.hour()) : QString::number(time.hour());
    auto minute = time.minute() < 10 ? "0" + QString::number(time.minute()) : QString::number(time.minute());
    auto second = time.second();

    auto dayOfWeek =  daysToString[dateTime.date().dayOfWeek()];
    auto timeString = hour + ":" + minute;

    for(auto i : _elements)
    {
        if(i->days.contains(dayOfWeek) || i->days.isEmpty())
        {
            if(i->time == timeString && i->isActive && second < 3){
                auto index = _elements.indexOf(i);
                currentIndex = index;
                emit startAlarm(currentIndex);
                i->isActive = i->isRepeat ? true : false;
                emit dataChanged(createIndex(index,0),createIndex(index,0),{AlarmRoles::IsActive});
                return true;
            }
        }
    }
    return false;
}
