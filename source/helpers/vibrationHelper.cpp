#include "headers/helpers/vibrationHelper.h"
#if defined(Q_OS_ANDROID)
#include<QtAndroid>
#include<QtAndroidExtras>
#include<QAndroidJniObject>
#endif

VibrationHelper::VibrationHelper(QObject *parent)
    : QObject{parent}
{}

VibrationHelper::~VibrationHelper()
{}

void VibrationHelper::vibrate(int x)
{
#if defined (Q_OS_ANDROID)
    QAndroidJniObject::callStaticMethod<void>("org/artcompany/clock/ClockApplication", "vibrate", "(I)V",x);

#endif
}
