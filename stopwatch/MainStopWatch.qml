import QtQuick 2.0

Item {
    id: root
    property int seconds: 0
    property int degree: 6
    property bool isActive: false

    Rectangle {
        antialiasing: true
        id: plate
        anchors.centerIn: parent
        height: Math.min(parent.width, parent.height)
        width: height
        radius: width / 2
        color: "white"
        border.color: "white"
        border.width: 1

        Repeater {
            model: 12
            antialiasing: true
            delegate: Item {
                id: secondsContainer
                property int secondsIndex: index
                height: plate.height / 2
                transformOrigin: Item.Bottom
                rotation: index * 30
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

                Text {
                    antialiasing: true
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    y: plate.height * 0.06
                    rotation: 360 - index * 30
                    text: secondsContainer.secondsIndex
                          == 0 ? 60 : secondsContainer.secondsIndex * 5
                    font.pointSize: 10
                    color: "black"
                }
            }
        }
    }

    Rectangle {
        id: center
        anchors.centerIn: plate
        height: plate.height * 0.03
        width: height
        radius: width * 0.5
        color: "black"
        antialiasing: true
    }

    SecondsNeedle {
        id: needle
        anchors.top: plate.top
        anchors.bottom: plate.bottom

        anchors.horizontalCenter: center.horizontalCenter
        seconds: root.seconds
        antialiasing: true
    }

}
