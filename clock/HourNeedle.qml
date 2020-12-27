import QtQuick 2.0

Item {
    id: hourNeedle

    property int value: 0
    property int granularity: 12
    property int valueMinute: 0
    Rectangle {
        width: 2
        height: parent.height * 0.25
        color: "white"
        anchors.bottom: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
    }

    rotation: 360 / granularity * (value % granularity) + 360 / granularity * (valueMinute / 60)
    antialiasing: true
}
