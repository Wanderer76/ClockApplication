QT += core quick svg qml quickcontrols2 network multimedia

android:QT+=androidextras

CONFIG += c++17 qtquickcompiler

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    headers/app.h \
    headers/core.h \
    headers/helpers/audioHelper.h \
    headers/helpers/fileHelper.h \
    headers/helpers/notifierHelper.h \
    headers/helpers/savingSystemHelper.h \
    headers/helpers/stopwatchHelper.h \
    headers/helpers/timeloaderHelper.h \
    headers/helpers/timerHelper.h \
    headers/helpers/vibrationHelper.h \
    headers/main.h \
    headers/models/alarmsModel.h \
    headers/models/globalWorldtimeModel.h \
    headers/models/userWorldtimeModel.h \
    headers/org_artcompany_clock_NativeHelper.h \
    headers/timeloaderHelper.h \


SOURCES += \
        main.cpp \
        source/app.cpp \
        source/core.cpp \
    source/helpers/audioHelper.cpp \
    source/helpers/fileHelper.cpp \
    source/helpers/notifierHelper.cpp \
    source/helpers/savingSystemHelper.cpp \
    source/helpers/stopwatchHelper.cpp \
        source/helpers/timeloaderHelper.cpp \
    source/helpers/timerHelper.cpp \
    source/helpers/vibrationHelper.cpp \
    source/models/alarmsModel.cpp \
    source/models/globalWorldtimeModel.cpp \
    source/models/userWorldtimeModel.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/Vibration.java \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    android/src/org/artcompany/clock/ClockApplication.java \
    android/src/org/artcompany/clock/NativeHelper.java \
    android/src/org/artcompany/clock/Notifier.java \
    android/src/org/artcompany/clock/TimerService.java \
    android/src/org/artcompany/clock/UriUtils.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

