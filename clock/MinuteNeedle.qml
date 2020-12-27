import QtQuick 2.0

Item {
    id: minuteNeedle

    property int value: 0
    property int granularity: 60

    Rectangle {
        width: 2
        height: parent.height * 0.45
        color: "white"
        anchors.bottom: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
    }

    rotation: 360 / granularity * (value % granularity)
    antialiasing: true
}
