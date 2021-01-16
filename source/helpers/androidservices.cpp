#include "headers/helpers/androidservices.h"

AndroidServices::AndroidServices(QObject *parent) : QObject(parent)
{
    vibration = new Vibration(this);
}

void AndroidServices::setNotification(const QString &notification)
{
    notifier.setNotification(notification);
}

void AndroidServices::vibrate(int x)
{
    vibration->vibrate(std::move(x));
}
