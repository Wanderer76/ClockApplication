#include "vibration.h"

Vibration::Vibration(QObject *parent) : QObject(parent)
{

}

void Vibration::vibrate(int x)
{
    QAndroidJniObject::callStaticMethod<void>(
                "org/artcompany/clock/Vibration",
                "Vibrate",
                "(I)V",
                x);
}
