#pragma once
#include<QAbstractListModel>
#include<QObject>
#include"headers/main.h"
#include"headers/helpers/audioHelper.h"

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
    SavingSystemHelper *_savingSystemHelper;
    AudioHelper *_audioHelper;
    QTimer *_updateTimer;

public:
    explicit AlarmsModel();
    ~AlarmsModel();

    Q_INVOKABLE QList<QString> getDays(const int index) const;
    Q_INVOKABLE QUrl getSound(const int index) const;
    Q_INVOKABLE QString getTime(const int index) const;
    Q_INVOKABLE QString getDescription(const int index) const;
    Q_INVOKABLE int getLongest(const int index) const;
    Q_INVOKABLE int getPauseLongest(const int index) const;
    Q_INVOKABLE bool getVibration(const int index) const;
    Q_INVOKABLE bool getRepeat(const int index) const;
    Q_INVOKABLE bool getActive(const int index) const;

    Q_INVOKABLE void remove(const int index);
    Q_INVOKABLE void createAlarm
    (
            const QList<QString>& days,
            const QUrl &sound,
            const QString &time,
            const QString &description,
            const int longest,
            const int pauseLongest,
            const int pauseCount,
            const bool vibration
    );
    Q_INVOKABLE void editElement
    (
            const int index,
            const QList<QString>& days,
            const QUrl &sound,
            const QString &time,
            const QString &description,
            const int longest,
            const int pauseLongest,
            const int pauseCount,
            const bool vibration
    );
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    void writeData();
    void readData();


private slots:
    bool checkForAlarms();
signals:
    void startAlarm(const int index);
    void pause();
    void resumeAlarm();
    void stopAlarm();
};
