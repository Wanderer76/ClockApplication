import QtQuick 2.12
import QtQuick.Controls 2.12
import "../alarm"
import "../clock"

Page {
    height: 640
    width: 480
    id: page
    property alias alarms: daysOfAlarm
    Label {
        id: label
        x: 20
        y: 10
        text: qsTr("Будильник")
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 20
        font.pointSize: 15
    }

    MainClock {
        id: mainClock
        x: 115
        width: 230
        height: 230
        anchors.top: parent.top
        anchors.topMargin: 45
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Label {
        id: currentTime
        x: 0
        width: parent.width
        height: 30
        text: mainClock.hour + ":" + mainClock.minutes + ":" + mainClock.seconds
        anchors.top: mainClock.bottom
        anchors.topMargin: 17
        font.pointSize: 17
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    TimesForAlarm {
        id: daysOfAlarm
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.top: currentTime.bottom
        anchors.topMargin: 20
    }
}
