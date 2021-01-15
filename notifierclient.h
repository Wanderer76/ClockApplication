#pragma once

#include <QObject>

class NotifierClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString notification READ getNotification WRITE setNotification NOTIFY notificationChanged)
private:
    QString _notification;
public:
    explicit NotifierClient(QObject *parent = nullptr);
    void setNotification(const QString &notification);
    QString getNotification() const;
signals:
    void notificationChanged();
private slots:
    void updateNotification();
};

