#pragma once
#include<QAbstractListModel>
class QTimer;


struct timeElement
{
    QString cityName;
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
        Time
    };
    QTimer *_timer;
public:
    WorldTimeList();
    ~WorldTimeList();
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent) override;
};
