import QtQuick 2.12
import QtQuick.Controls 2.12
import "../alarm"
import "../clock"

Page {
    id: page
    property alias alarms: daysOfAlarm
    Label {
        id: label
        x: 20
        y: 10
        width: 100
        height: 30
        text: qsTr("Будильник")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 35
        font.pointSize: 20
    }

    MainClock {
        id: mainClock
        width: 240
        height: 240
        anchors.top: label.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }
    Label {
        id: currentTime
        x: 0
        width: parent.width
        height: 30
        text: mainClock.hour + ":" + mainClock.minutes + ":" + mainClock.seconds
        anchors.top: mainClock.bottom
        anchors.topMargin: 17
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    TimesForAlarm {
        id: daysOfAlarm
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.top: currentTime.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.topMargin: 30
    }
}
