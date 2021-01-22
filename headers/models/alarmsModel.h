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
        Vibration,
        Repeat,
        IsActive
    };

    QList<AlarmElement *> _elements;
    SavingSystemHelper *_helper;
    QTimer *_updateTimer;

public:
    explicit AlarmsModel();
    ~AlarmsModel();

    Q_INVOKABLE AlarmElement get(const int index) const;
    Q_INVOKABLE QList<QString> getDays(const int index) const;
    Q_INVOKABLE QUrl getSound(const int index) const;
    Q_INVOKABLE QString getTime(const int index) const;
    Q_INVOKABLE QString getDescription(const int index) const;
    Q_INVOKABLE int getLongest(const int index) const;
    Q_INVOKABLE int getPauseLongest(const int index) const;
    Q_INVOKABLE bool getVibration(const int index) const;
    Q_INVOKABLE bool getRepeat(const int index) const;
    Q_INVOKABLE bool getActive(const int index);
    Q_INVOKABLE void setActive(const int index, const bool value);


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
    void writeData();
    void readData();


private slots:
    void checkForAlarms();
signals:
    void shouldAlarm(const int index);
};
