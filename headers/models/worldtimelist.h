#pragma once
#include<QAbstractListModel>
#include"headers/main.h"

class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
#define WorldTimes "times.txt"

class WorldTimeList : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<timeElement*>_elements;
    QNetworkAccessManager *manager;
    QString city;
    QString region;
    QTimer *_timer;
public:
    WorldTimeList();
    ~WorldTimeList();
    Q_INVOKABLE void append(const QString&region,const QString&city);
    Q_INVOKABLE void remove(const int index);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};
