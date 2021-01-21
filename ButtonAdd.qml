import QtQuick 2.12
import QtQuick.Controls 2.12

RoundButton {
    height: 45
    width: height
    id: _
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
