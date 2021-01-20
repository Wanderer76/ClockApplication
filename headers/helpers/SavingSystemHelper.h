#pragma once
#include<QSettings>
#include<QJsonObject>

class SavingSystemHelper : public QObject
{
    Q_OBJECT
private:
    QString _orgName;
    QString _appName;

    SavingSystemHelper(const QString &orgName,const QString &appName);
    QString _groupName;
    QJsonObject data;

public:
    SavingSystemHelper(const SavingSystemHelper&) = delete;
    void operator=(const SavingSystemHelper&) = delete;

    static SavingSystemHelper* getInstance(const QString &orgName,const QString &appName);
    void beginGroup(const QString& name);
    void endGroup();
    void saveFile(const QString &key,const QJsonObject &value);
    QByteArray readFile(const QString &filename);
signals:
    void read();
    void write();
};
