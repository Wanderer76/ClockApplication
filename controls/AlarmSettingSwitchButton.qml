import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Rectangle {
    property string mainText: ""
    property alias switchElement: control
    color: "white"
    RowLayout {
        id: layout
        anchors.fill: parent

        Label {
            color: "#000000"
            text: qsTr(mainText)
            font.pointSize: 13
            Layout.alignment: Qt.AlignLeft
        }

        Switch {
            id: control
            Layout.alignment: Qt.AlignRight
            indicator: Rectangle {
                antialiasing: true
                implicitWidth: 50
                implicitHeight: 22
                x: control.width - width - control.rightPadding
                y: parent.height / 2 - height / 2
                radius: 13
                color: control.checked ? "#007dfe" : "#e6e6e6"

                Rectangle {
                    antialiasing: true
                    anchors.verticalCenter: parent.verticalCenter
                    x: control.checked ? parent.width - width - 3 : 1
                    width: 20
                    height: width
                    radius: 13
                    border.color: "#dcdcdc"
                }
            }
        }
    }

    ToolSeparator {
        id: toolSeparator
        anchors.top: parent.bottom
        anchors.topMargin: 0
        orientation: Qt.Horizontal
        width: parent.width
    }
}
