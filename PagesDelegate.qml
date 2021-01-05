import QtQuick 2.12
import QtQuick.Controls 2.12

TabButton {
    property string textValue: ""
    property string imageValue: ""
    font.pointSize: 11
    antialiasing: true
    background: Rectangle {
        anchors.fill: parent
        color: "#fafafa"
    }
    display: AbstractButton.IconOnly
    icon.source: imageValue
    icon.cache: true
    icon.color: focus === true ? "#007dfe" : "#646464"
}

/*##^##
Designer {
    D{i:2;anchors_y:22}D{i:3;anchors_height:14;anchors_y:72}D{i:4;anchors_y:0}D{i:5;anchors_height:14;anchors_y:72}
}
##^##*/

