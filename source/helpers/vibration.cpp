#include "headers/helpers/vibration.h"
#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

Vibration::Vibration(QObject *parent)
    : QObject{parent}
{}

Vibration::~Vibration()
{}

void Vibration::vibrate(int x)
{
#if defined (Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>(
                "org/artcompany/clock/Vibration",
                "Vibrate",
                "(Landroid/content/Context;Ljava/lang/String;)V",
                 QtAndroid::androidContext().object(),
                x);
#endif
}
