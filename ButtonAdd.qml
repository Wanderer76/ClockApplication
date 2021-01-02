import QtQuick 2.12
import QtGraphicalEffects 1.12
import QtQuick.Controls 2.12

RoundButton {
    height: 45
    width: height
    id: _
    property string imageValue: ""
    opacity: pressed ? 0.5 : 1
    background: Rectangle {
        color: "#007dfe"
        radius: width / 2
        antialiasing: true


        /*    RectangularGlow {
            anchors.fill: parent
            spread: 0.0
            glowRadius: 10
            cornerRadius: 10
            color: parent.color /// "#d9ecfd"
            z: 1
        }*/
    }
    antialiasing: true
    icon.source: imageValue
    icon.color: "white"
}
