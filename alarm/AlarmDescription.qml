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

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

