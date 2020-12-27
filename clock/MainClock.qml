import QtQuick 2.0

Item {
    id: root
    property var currentDate: new Date()
    property int hour: currentDate.getHours()
    property int minutes: currentDate.getMinutes()
    property int seconds: currentDate.getSeconds()

    Timer {
        id: timer
        repeat: true
        interval: 1000
        running: true
        onTriggered: {
            root.currentDate = new Date()
        }
    }

    Rectangle {
        id: plate

        anchors.centerIn: parent
        height: Math.min(parent.width, parent.height)
        width: height
        radius: width / 2
        color: "black"
        border.color: "black"
        border.width: 5

        Repeater {
            model: 12

            delegate: Item {
                id: hourContainer
                property int hour: index
                height: plate.height / 2
                transformOrigin: Item.Bottom
                rotation: index * 30
                x: plate.width / 2

                Rectangle {
                    height: plate.height * 0.04
                    width: 2
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: 1
                    antialiasing: true
                }

                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    y: plate.height * 0.06
                    rotation: 360 - index * 30
                    text: hourContainer.hour == 0 ? 12 : hourContainer.hour
                    font.pixelSize: plate.height * 0.1
                    color: "white"
                }
            }
        }
    }

    Rectangle {
        id: center
        anchors.centerIn: parent
        height: plate.height * 0.05
        width: height
        radius: width * 0.5
        color: "black"
    }

    SecondsHeedle {
        anchors.top: plate.top
        anchors.bottom: plate.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        value: root.seconds
    }

    MinuteNeedle {
        anchors.top: plate.top
        anchors.bottom: plate.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        value: root.minutes
    }

    HourNeedle {
        anchors.top: plate.top
        anchors.bottom: plate.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        value: root.hour
    }
}
