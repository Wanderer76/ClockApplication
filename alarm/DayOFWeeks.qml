import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtGraphicalEffects 1.0

Rectangle {
    property alias acceptButton: acceptButton
    property alias cancelButton: cancelButton
    property alias repeaterElem: repeater
    property var days: ["Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"]
    id: rectangle
    color: "white"
    radius: 30
    Column {
        id: row
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottomMargin: 60
        anchors.topMargin: 40
        Repeater {
            id: repeater
            anchors.fill: parent
            model: 7
            delegate: CheckDelegate {
                height: 40
                id: checkDelegate
                text: qsTr(days[index])
                anchors.left: parent.left
                anchors.leftMargin: 10
                anchors.right: parent.right
                anchors.rightMargin: 10
                font.pointSize: 12
            }
        }
    }

    Label {
        id: label
        x: 0
        y: 0
        width: 132
        height: 24
        text: qsTr("Дни недели")
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 10
        font.pointSize: 15
        verticalAlignment: Text.AlignVCenter
    }

    Row {
        id: row1
        anchors.top: row.bottom
        anchors.topMargin: 5
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 5

        RoundButton {
            id: cancelButton
            width: parent.width / 2 - 10
            text: qsTr("Отмена")
            font.pointSize: 12
            flat: true
        }

        ToolSeparator {
            id: toolSeparator
        }

        RoundButton {
            id: acceptButton
            width: parent.width / 2 - 10
            text: qsTr("Ок")
            font.pointSize: 12
            flat: true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:5;anchors_height:400;anchors_width:200;anchors_x:149;anchors_y:606}
}
##^##*/

