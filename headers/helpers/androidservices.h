#pragma once
#include"notifierclient.h"
#include"vibration.h"


class AndroidServices : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString notification READ getNotification WRITE setNotification NOTIFY notifier.notificationChanged)
private:
    NotifierClient notifier;
    Vibration *vibration;
public:
    explicit AndroidServices(QObject *parent = nullptr);
    Q_INVOKABLE void setNotification(const QString &notification);
    Q_INVOKABLE void vibrate(int x);
};

