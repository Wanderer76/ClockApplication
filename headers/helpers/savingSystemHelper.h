#pragma once
#include<QSettings>
#include<QJsonObject>

class SavingSystemHelper : public QObject
{
    Q_OBJECT
private:
    SavingSystemHelper();
    QString _groupName;
    QJsonObject data;

public:
    SavingSystemHelper(const SavingSystemHelper&) = delete;
    void operator=(const SavingSystemHelper&) = delete;

    static SavingSystemHelper* getInstance();
    void saveFile(const QString &key,const QJsonObject &value);
    void saveFileWithRecordCount(const QString &key,const QJsonObject &value,int count);
    QByteArray readFile(const QString &filename);
signals:
    void read();
    void write();
};
