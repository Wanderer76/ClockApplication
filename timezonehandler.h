#pragma once
#include <QObject>
#include<QAbstractListModel>
#include"timeloader.h"
enum Roles {
    Country= Qt::UserRole+1,
    Region,
    Time
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

