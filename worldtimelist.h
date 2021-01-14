#pragma once
#include<QAbstractListModel>
#include<QEventLoop>
class QTimer;
class QNetworkAccessManager;
class QNetworkReply;
#define WorldTimes "times.txt"

struct timeElement
{
    QString cityName;
    QString region = "";
    QString time;
    timeElement(const QString& city,const QString& time)
        :cityName(city),time(time)
    {}
};

class Loader : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager*manager;
public:
    Loader(QObject*pwgt = nullptr);
    ~Loader();
    void makeRequest(const QUrl&url);
private slots:
    void slotReadyRead(QNetworkReply*reply);
signals:
    void dataReadyRead(QByteArray data);
};

class WorldTimeList : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<timeElement*>_elements;
    QNetworkAccessManager *manager;
    QString city;
    QString region;
    QEventLoop *loop;

    enum Roles {
        City = Qt::UserRole+1,
        Time,
        Region
    };
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
private slots:
    void writeDataSlot(QNetworkReply*reply);
};
