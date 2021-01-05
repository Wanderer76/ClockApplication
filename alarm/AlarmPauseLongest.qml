import QtQuick 2.12
import QtQuick.Controls 2.12
import "../controls"

DialogArea {
    labelText: "Длительность паузы"
    rightButtonText: "Ок"
    leftButtonText: "Отмена"

    Item {}

    Column {
        id: column
        x: 8
        y: 64
        width: 606
        height: 207
        spacing: 20

        Label {
            id: label
            width: parent.width
            height: 27
            color: "#c5393939"
            text: qsTr("Длительность паузы (мин)")
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 11
        }

        Slider {
            id: slider
            width: parent.width
            height: 40
            from: 5
            to: 30
            stepSize: 5
            value: 10
            snapMode: Slider.SnapAlways
        }

        ToolSeparator {
            id: toolSeparator
            width: parent.width
            height: 15
            orientation: Qt.Horizontal
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

