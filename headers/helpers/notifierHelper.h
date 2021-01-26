#pragma once
#include <QObject>

class NotifierHelper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notification READ getNotification WRITE setNotification NOTIFY notificationChanged)
private:
    QString _notification;
public:
    explicit NotifierHelper(QObject *parent = nullptr);
    ~NotifierHelper();
    void setNotification(const QString &notification);
    QString getNotification() const;
signals:
    void notificationChanged();
public slots:
    void updateNotification();
};

