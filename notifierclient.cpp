#include "notifierclient.h"

#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

NotifierClient::NotifierClient(QObject *parent) : QObject(parent)
{
    connect(this,&NotifierClient::notificationChanged,this,&NotifierClient::updateNotification);
}

void NotifierClient::setNotification(const QString &notification)
{
    if(_notification ==notification)
        return;
    _notification = notification;
    emit notificationChanged();
}

QString NotifierClient::getNotification() const
{
    return _notification;
}

void NotifierClient::updateNotification()
{
#if defined (Q_OS_ANDROID)
    auto notification = QAndroidJniObject::fromString(_notification);
    QAndroidJniObject::callStaticMethod<void>(
                "org/artcompany/clock/Notifier",
                "notify",
                "(Landroid/content/Context;Ljava/lang/String;)V",
                QtAndroid::androidContext().object(),
                notification.object<jstring>()
                );
#endif
}
