import QtQuick 2.0

Item {
    Rectangle {
        id: colorRect
        height: 0
        width: 0
        color: "#e8e8e8"

        transform: Translate {
            x: -colorRect.width / 2
            y: -colorRect.height / 2
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            circleAnimation.stop()
        }
        onPressed: {

            colorRect.x = mouseX
            colorRect.y = mouseY

            circleAnimation.start()
        }
        onReleased: circleAnimation.stop()
        onPositionChanged: circleAnimation.stop()
    }

    PropertyAnimation {
        id: circleAnimation
        target: colorRect
        properties: "width,height,radius"
        from: 0
        to: body.width * 3
        duration: 300

        onStopped: {
            colorRect.width = 0
            colorRect.height = 0
        }
    }
}
