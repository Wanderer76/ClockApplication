import QtQuick 2.0

Item {
    id: secondsNeedle

    property int value: 0
    property int granularity: 60

    Rectangle {
        width: 1
        height: parent.height * 0.6
        color: "red"
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
    }

    rotation: 360 / granularity * (value % granularity)
    antialiasing: true
}
