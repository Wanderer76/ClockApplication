import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id: rectangle
    height: 60
    color: "white"
    property alias countryLabel: countryLabel
    Label {
        id: number
        text: index + 1
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 15
        font.pointSize: 15
    }
    Label {
        id: countryLabel
        text: qsTr(country)
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: number.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 15
        font.pointSize: 15
    }
    Label {
        id: regionlabel
        text: qsTr("(" + region + ")")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: countryLabel.right
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.leftMargin: 10
        font.pointSize: 13
    }

    ToolSeparator {
        id: toolSeparator
        width: parent.width
        height: 13
        anchors.top: parent.bottom
        anchors.topMargin: 0
        orientation: Qt.Horizontal
    }

}
