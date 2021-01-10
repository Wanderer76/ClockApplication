import QtQuick 2.12
import QtQuick.Controls 2.12
import "../stopwatch"

Page {
    id: page
    property bool isActive: false
    property alias stopWatch: stopwatch
    width: 480
    height: 640

    Label {
        id: label
        x: 20
        y: 10
        width: 100
        height: 30
        text: qsTr("Секундомер")
        anchors.top: parent.top
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 35
        font.pointSize: 20
    }

    MainStopWatch {
        id: stopwatch
        width: 250
        height: 250
        anchors.top: label.bottom
        anchors.topMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Label {
        id: secondsLabel
        x: 235
        width: 230
        height: 29
        anchors.top: stopwatch.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 18
        text: "00:00:00"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 50
    }

    LapView {
        id: lapView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: secondsLabel.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 15
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.bottomMargin: 80
    }

    Connections {
        target: Stopwatch
        function onSendTime(time) {
            secondsLabel.text = time
            var times = time.split(':')
            stopwatch.seconds = times[1]
        }
        function onSendState(state) {
            isActive = state
        }
    }

    RoundButton {
        id: resetButton
        display: AbstractButton.IconOnly
        icon.source: "qrc:/images/reload.svg"
        icon.color: pressed ? "#007dfe" : "#646464"

        anchors.left: parent.left
        anchors.top: lapView.bottom
        anchors.leftMargin: 80
        anchors.topMargin: 15
        onClicked: {
            Stopwatch.reset()
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
        anchors.right: parent.right
        anchors.top: lapView.bottom
        anchors.rightMargin: 80
        anchors.topMargin: 15
        onClicked: {

        }

        background: Rectangle {
            color: "#00000000"
        }
    }
}
