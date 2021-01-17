#pragma once
#include<QAbstractListModel>
#include<QObject>
#include"headers/main.h"

class AlarmsModel : public QAbstractListModel
{
    Q_OBJECT
private:
    enum AlarmRoles{
        Days = Qt::UserRole+1,
        Sound,
        Time,
        Description,
        Longest,
        PauseLongest,
        Vibration
    };
    QList<AlarmElement *> _elements;
public:
    AlarmsModel();
    ~AlarmsModel();
    Q_INVOKABLE AlarmElement get(const int index);
    Q_INVOKABLE QList<QString> getDays(const int index);
    Q_INVOKABLE QUrl getSound(const int index);
    Q_INVOKABLE QString getTime(const int index);
    Q_INVOKABLE QString getDescription(const int index);
    Q_INVOKABLE int getLongest(const int index);
    Q_INVOKABLE int getPauseLongest(const int index);
    Q_INVOKABLE bool getVibration(const int index);
    Q_INVOKABLE void remove(const int index);
    Q_INVOKABLE void append
    (
            QList<QString> days,
            QUrl sound,
            QString time,
            QString description,
            int longest,
            int pauseLongest,
            bool vibration
    );
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
};
