import QtQuick 2.12
import QtQuick.Controls 2.12

RoundButton {
    id: _
    height: 45
    width: height
    property string imageValue: ""
    opacity: pressed || !enabled ? 0.5 : 1
    background: Rectangle {
        color: "#007dfe"
        radius: width / 2
        antialiasing: true
    }
    antialiasing: true
    icon.source: imageValue
    icon.color: "white"
}
