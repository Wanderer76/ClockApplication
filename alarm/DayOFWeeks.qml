import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import "../controls"

DialogArea {
    labelText: qsTr("Дни недели")
    rightButtonText: qsTr("Ок")
    leftButtonText: qsTr("Отмена")
    property alias repeaterElem: repeater
    property var days: ["Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"]
    Column {
        id: column
        spacing: 5
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottomMargin: 60
        anchors.topMargin: 50
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
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

