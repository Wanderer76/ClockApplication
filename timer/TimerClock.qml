import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    width: 480
    height: 640
    property alias progressBar: progress
    property alias timerTime: timer
    property bool isActive: timer.running
    property int seconds: 0

    Timer {
        id: timer
        running: false
        interval: 1000
        repeat: true
        onTriggered: {
            if (progress.currentValue !== progress.maximumValue)
                progress.currentValue++
            else {
                Notifier.notification = "Время вышло"
                timer.running = false
            }
        }
    }

    TimerProgressBar {
        id: progress
        anchors.fill: parent
        maximumValue: seconds
        onMaximumValueChanged: {
            console.log(progress.maximumValue)
        }
    }


    /* Rectangle {
        antialiasing: true
        id: plate
        anchors.centerIn: parent
        height: Math.min(parent.width, parent.height)
        width: height
        radius: width / 2
        color: "white"
        border.color: "white"
        border.width: 5

        Repeater {
            model: 48
            antialiasing: true
            delegate: Item {
                id: hourContainer
                property int hourIndex: index
                height: plate.height / 2
                transformOrigin: Item.Bottom
                rotation: index * 7.5
                x: plate.width / 2

                Rectangle {
                    height: plate.height * 0.04
                    width: 2
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 1
                    antialiasing: true
                }
            }
        }
    }

    Rectangle {
        id: center
        anchors.centerIn: parent
        height: plate.height * 0.03
        width: height
        radius: width * 0.5
        color: "black"
        antialiasing: true
    }

    TimerNeedle {
        anchors.top: plate.top
        anchors.bottom: plate.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        value: seconds
        antialiasing: true
    }*/
}
