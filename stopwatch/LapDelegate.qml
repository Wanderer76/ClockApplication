import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    id: item1
    width: 480
    height: 60
    Rectangle {
        id: rectangle
        height: 60
        anchors.fill: parent

        Label {
            id: label
            y: 19
            width: 100
            height: 35
            text: qsTr("Отрезок " + segmentNumber)
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 10
            font.pointSize: 14
        }

        Label {
            id: label1
            y: 19
            width: 100
            height: 35
            text: time
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.rightMargin: 10
            anchors.verticalCenterOffset: 0
            font.pointSize: 14
        }

        ToolSeparator {
            id: toolSeparator
            width: parent.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            orientation: Qt.Horizontal
        }
    }
}
