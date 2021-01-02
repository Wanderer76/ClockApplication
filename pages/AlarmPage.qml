import QtQuick 2.12
import QtQuick.Controls 2.12
import "../clock"
import "../alarm"

Page {
    id: page
    property alias alarms: timeToAlarms
    Text {
        width: 123
        height: 23
        text: qsTr("Будильник")
        anchors.top: parent.top
        anchors.topMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30
        fontSizeMode: Text.HorizontalFit
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 25
    }
    MainClock {
        id: mainClock
        width: 240
        height: 240
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 70
    }

    Text {
        id: timeToSignalText
        width: parent.width
        height: 20
        text: qsTr(mainClock.hour + ":" + mainClock.minutes + ":" + mainClock.seconds)
        verticalAlignment: Text.AlignTop
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenterOffset: 35
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 25
    }

    TimesForAlarm {
        id: timeToAlarms
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.top: timeToSignalText.bottom
        anchors.topMargin: 25
    }    
}
