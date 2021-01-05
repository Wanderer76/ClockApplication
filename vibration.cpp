#include "vibration.h"
#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

Vibration::Vibration(QObject *parent) : QObject(parent)
{

}

void Vibration::vibrate(int x)
{
#if defined (Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>(
                "org/artcompany/clock/Vibration",
                "Vibrate",
                "(I)V",
                x);
#endif
}
