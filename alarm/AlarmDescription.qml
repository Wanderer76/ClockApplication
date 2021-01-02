import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../controls"

DialogArea {
    property string text: textField.text
    id: desc
    labelText: "Описание"
    rightButtonText: "Ок"
    leftButtonText: "Отмена"
    TextEdit {
        id: textField
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.bottomMargin: 50
        anchors.top: parent.top
        anchors.topMargin: 50
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
        anchors.bottom: parent.bottom
        horizontalAlignment: Text.AlignLeft
        text: qsTr("Будильник")
    }
}
/*Rectangle {
    property alias acceptButton: acceptButton
    property alias cancelButton: cancelButton
    property string text: textField.text
    height: 160
    id: rectangle
    color: "white"
    radius: 30

    Label {
        id: label

        width: 134
        height: 30
        text: qsTr("Описание")
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: 15
        verticalAlignment: Text.AlignVCenter
    }

    TextEdit {
        id: textField
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
        anchors.bottom: row.top
        anchors.bottomMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 59
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 10
        horizontalAlignment: Text.AlignLeft
    }

    Row {
        id: row
        y: 128
        height: 38
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10

        RoundButton {

            id: cancelButton
            anchors.right: toolSeparator.left
            anchors.rightMargin: 3
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            flat: true

            contentItem: Label {
                text: qsTr("Отмена")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                color: "#007dfe"
            }
        }

        ToolSeparator {
            id: toolSeparator
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }

        RoundButton {
            id: acceptButton
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: toolSeparator.right
            anchors.leftMargin: 1
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            flat: true
            contentItem: Label {
                text: qsTr("Ок")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 12
                color: "#007dfe"
            }
        }
    }
}*/


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

