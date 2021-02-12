#include"headers/helpers/savingSystemHelper.h"
#include<QStandardPaths>
#include<QFile>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>

SavingSystemHelper::SavingSystemHelper()
{}



SavingSystemHelper *SavingSystemHelper::getInstance()
{
    static SavingSystemHelper* _instance = nullptr;
    if(_instance == nullptr)
        _instance = new SavingSystemHelper();
    return _instance;
}


void SavingSystemHelper::saveFile(const QString &key, const QJsonObject &value)
{
    QJsonObject result;
    result.insert(key,value);

    QJsonDocument doc(result);
    QFile file(key+".json");
    if(file.open(QFile::WriteOnly))
    {
        file.write(doc.toJson());
    }
    file.close();

}

void SavingSystemHelper::saveFileWithRecordCount(const QString &key, const QJsonObject &value, int count)
{
    QJsonObject result;
    result.insert(key,value);
    result.insert("size",count);

    QJsonDocument doc(result);
    QFile file(key+".json");
    if(file.open(QFile::WriteOnly))
    {
        file.write(doc.toJson());
    }
    file.close();

}

QByteArray SavingSystemHelper::readFile(const QString &filename)
{
    QFile file(filename);
    if(!file.exists())
        return{};

    QByteArray arr;
    if(file.open(QFile::ReadOnly))
    {
       arr = file.readAll();
    }
    file.close();
    return arr;
}
