import QtQuick 2.0

Item {
    id: minuteNeedle

    property int value: 0
    property int granularity: 60
    property string needleColor: ""

    Rectangle {
        width: 2
        height: parent.height * 0.45
        color: needleColor
        anchors.bottom: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        antialiasing: true
    }

    rotation: 360 / granularity * (value % granularity)
    antialiasing: true
}
