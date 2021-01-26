#include "headers/helpers/notifierHelper.h"

#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

NotifierHelper::NotifierHelper(QObject *parent) : QObject{parent}
{
    connect(this,&NotifierHelper::notificationChanged,this,&NotifierHelper::updateNotification);
}

NotifierHelper::~NotifierHelper()
{}

void NotifierHelper::setNotification(const QString &notification)
{
    if(_notification == notification)
        return;

    _notification = notification;
    emit notificationChanged();
}

QString NotifierHelper::getNotification() const
{
    return _notification;
}

void NotifierHelper::updateNotification()
{
#if defined (Q_OS_ANDROID)

    auto notification = QAndroidJniObject::fromString(_notification);

    QAndroidJniObject::callStaticMethod<void>(
                "org/artcompany/clock/Notifier",
                "notify",
                "(Landroid/content/Context;Ljava/lang/String;)V",
                QtAndroid::androidContext().object(),
                notification.object<jstring>());
#endif
}
