import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    property string mainText: ""
    property string additionalText: ""
    property alias mouseArea: mouse

    color: mouse.pressed ? Qt.darker("white", 1.1) : "white"
    RowLayout {
        id: layout
        anchors.fill: parent

        Label {
            color: "#000000"
            text: qsTr(mainText)
            font.pointSize: 13
            Layout.alignment: Qt.AlignLeft
        }

        Label {
            color: "#797d82"
            text: qsTr(additionalText)
            font.pointSize: 11
            Layout.rightMargin: 15
            Layout.alignment: Qt.AlignRight
        }
    }

    ToolSeparator {
        id: toolSeparator
        anchors.top: parent.bottom
        anchors.topMargin: 0
        orientation: Qt.Horizontal
        width: parent.width
    }
    MouseArea {
        id: mouse
        height: parent.height + toolSeparator.height
        width: parent.width
    }
}
