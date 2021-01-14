#pragma once
#include <QObject>
#include<QAbstractListModel>

#include"timeloaderHelper.h"
enum Roles {
    Country= Qt::UserRole+1,
    Region,
    Time
};
struct worldTimeElement
{
    QString countryName;
    QString regionName;
    QString time;
    worldTimeElement(QString country,QString region,QString time = "")
        :countryName(country),regionName(region), time(time)
    {}
};


class TimeZoneHandler : public QAbstractListModel
{
    Q_OBJECT
private:
    QVector<worldTimeElement*> _elements;
    void createListOfElements();
    void parseJson(QByteArray&&);
public:
    TimeZoneHandler();
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};

