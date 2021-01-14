#pragma once
#include<QAbstractListModel>
#include<QSet>
class QTimer;


struct timeElement
{
    QString cityName;
    QString region;
    QString time;
    timeElement(const QString& city,const QString& time)
        :cityName(city),time(time)
    {}
};
class WorldTimeList : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<timeElement*>_elements;
    enum Roles {
        City = Qt::UserRole+1,
        Time,
        Region
    };
    QMultiMap<QString,timeElement>_table;
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
