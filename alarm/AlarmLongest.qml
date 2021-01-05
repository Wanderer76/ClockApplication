import QtQuick 2.12
import QtQuick.Controls 2.12
import "../controls"

DialogArea {
    leftButtonText: "Отмена"
    labelText: "Длительность сигнала"
    rightButtonText: ""
    property int time: 5

    Column {
        id: column
        anchors.fill: parent
        spacing: 5
        anchors.rightMargin: 10
        anchors.leftMargin: 10
        anchors.bottomMargin: 55
        anchors.topMargin: 50

        RadioDelegate {
            width: parent.width
            text: qsTr("1 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 1
            }
        }
        RadioDelegate {
            width: parent.width
            text: qsTr("5 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 5
            }
        }
        RadioDelegate {
            width: parent.width
            text: qsTr("10 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 10
            }
        }
        RadioDelegate {
            width: parent.width
            text: qsTr("15 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 15
            }
        }
        RadioDelegate {
            width: parent.width
            text: qsTr("20 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 20
            }
        }
        RadioDelegate {
            width: parent.width
            text: qsTr("30 мин")
            font.pointSize: 17
            onCheckedChanged: {
                time = 30
            }
        }
    }
}
