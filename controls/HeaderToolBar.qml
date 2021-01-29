import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ToolBar {

    property alias acceptButton: accept
    property alias cancelButton: cancel
    property string titleText: ""

    height: 50
    antialiasing: true
    wheelEnabled: false
    contentHeight: 35
    contentWidth: 190
    enabled: true
    focusPolicy: Qt.TabFocus
    width: parent.width

    background: Rectangle {
        anchors.fill: parent
        color: "white"
    }
    RowLayout {
        width: parent.width
        height: parent.height
        ToolButton {
            id: cancel
            width: 35
            height: 35
            Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
            display: AbstractButton.IconOnly
            icon.source: "qrc:/images/cancel.svg"
            leftPadding: 10
            highlighted: false
            flat: true
            background: Rectangle {
                anchors.fill: parent
                color: "white"
            }
        }

        Label {
            id: title
            text: qsTr(titleText)
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.pointSize: 17
        }

        ToolButton {
            id: accept
            width: 45
            height: 45
            Layout.rightMargin: 0
            display: AbstractButton.IconOnly
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            icon.source: "qrc:/images/check.svg"
            rightPadding: 10
            flat: true

            background: Rectangle {
                anchors.fill: parent
                color: "white"
            }
        }
    }
}
