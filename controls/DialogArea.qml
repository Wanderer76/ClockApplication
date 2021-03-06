import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12

Rectangle {
    property alias acceptButton: acceptButton
    property string labelText: label
    property string rightButtonText: ""
    property string leftButtonText: ""
    height: 160
    id: rectangle
    color: "white"
    radius: 30
    property alias cancelButton: cancelButton

    Label {
        id: label
        width: 134
        height: 30
        text: qsTr(labelText)
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: 20
        verticalAlignment: Text.AlignVCenter
    }

    Row {
        id: row
        height: 35
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        RoundButton {
            id: cancelButton
            flat: true
            height: parent.height
            width: rightButtonText != "" ? (parent.width / 2 - 1) : (parent.width)
            contentItem: Label {
                width: 31
                text: qsTr(leftButtonText)
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 18
                color: "#007dfe"
            }
        }

        ToolSeparator {
            id: toolSeparator
            width: rightButtonText != "" ? 13 : 0
            height: parent.height
        }

        RoundButton {
            id: acceptButton
            height: parent.height
            width: parent.width / 2 - 1
            flat: true
            contentItem: Label {
                text: qsTr(rightButtonText)
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 18
                color: "#007dfe"
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;anchors_height:400;anchors_width:200;anchors_x:149;anchors_y:606}
}
##^##*/

