import QtQuick 2.12
import QtQuick.Controls 2.12
import "../timer"

Page {
    id: page

    clip: true
    property alias timer: clock

    Label {
        id: label
        x: 20
        y: 10
        width: 100
        height: 30
        text: qsTr("Таймер")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 35
        font.pointSize: 20
    }
    TimerClock {
        id: clock
        width: 235
        height: 235
        anchors.top: label.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
        seconds: time.hourIndex + time.minuteIndex + time.secondIndex
        progressBar.text: time.hourIndex + ":" + time.minuteIndex + ":" + time.secondIndex
    }
    TimerTime {
        id: time
        x: 0
        width: 270
        height: 145
        anchors.top: clock.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 56
    }
    Rectangle {
        id: rectangle
        x: -10
        width: parent.width + 20
        height: 40
        color: "#00ffffff"
        anchors.top: time.top
        anchors.topMargin: 0
        border.color: "#9f9f9f"
    }
    Row {
        id: row
        x: 139
        width: 207
        height: 40
        anchors.top: time.bottom
        anchors.horizontalCenterOffset: 6
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 6
        spacing: 70
        Label {
            id: label1
            text: qsTr("Ч")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 15
        }

        Label {
            id: label2
            text: qsTr("мин")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 15
        }

        Label {
            id: label3
            text: qsTr("С")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 15
        }
    }
    RoundButton {
        id: resetButton
        display: AbstractButton.IconOnly
        icon.source: "qrc:/images/reload.svg"
        icon.color: pressed ? "#007dfe" : "#646464"
        enabled: timer.isActive ? false : true
        opacity: enabled ? 1 : 0.5
        anchors.left: parent.left
        anchors.top: row.bottom
        anchors.leftMargin: 80
        anchors.topMargin: 10
        onClicked: {
            clock.timerTime.stop()
            clock.progressBar.currentValue = 0
            time.clear()
        }

        background: Rectangle {
            color: "#00000000"
        }
    }

    RoundButton {
        id: lapButton
        x: 332
        display: AbstractButton.IconOnly
        icon.source: "qrc:/images/stopwatch.svg"
        icon.color: pressed ? "#007dfe" : "#646464"
        enabled: timer.isActive
        opacity: enabled ? 1 : 0.5
        anchors.right: parent.right
        anchors.top: row.bottom
        anchors.rightMargin: 80
        anchors.topMargin: 10
        onClicked: {

        }

        background: Rectangle {
            color: "#00000000"
        }
    }
}
