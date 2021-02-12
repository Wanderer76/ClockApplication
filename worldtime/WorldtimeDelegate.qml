import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

SwipeDelegate {
    width: 480
    height: 80

    id: swipeDelegate
    swipe.right: Rectangle {
        id: deleteLabel
        height: parent.height
        width: height
        radius: 1
        anchors.right: parent.right
        color: "#e6e6e6"

        Rectangle {
            id: round
            height: parent.height * 0.6
            width: height
            radius: width / 2
            anchors.centerIn: parent
            color: mouse.pressed ? Qt.darker("tomato", 1.1) : "tomato"
            Image {
                id: trashImage
                anchors.fill: parent
                anchors.margins: 10
                source: "qrc:/images/delete.svg"
                antialiasing: true
                fillMode: Image.PreserveAspectFit
                enabled: false
                cache: true
                asynchronous: true
                ColorOverlay {
                    anchors.fill: trashImage
                    source: trashImage
                    color: "white"
                }
            }
        }
        MouseArea {
            id: mouse
            anchors.fill: parent
            onClicked: {
                console.log("removed")
                view.model.remove(index)
            }
        }
    }
    ListView.onRemove: SequentialAnimation {
        PropertyAction {
            target: swipeDelegate
            property: "ListView.delayRemove"
            value: true
        }
        NumberAnimation {
            target: swipeDelegate
            property: "height"
            to: 0
            easing.type: Easing.InOutQuad
        }
        PropertyAction {
            target: swipeDelegate
            property: "ListView.delayRemove"
            value: false
        }
    }

    background: Rectangle {
        id: rectangle

        Label {
            id: label
            y: 24
            text: qsTr(city)
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
            anchors.leftMargin: 50
        }

        Label {
            id: label1
            x: 400
            y: 24
            text: time
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 20
            anchors.rightMargin: 50
        }
    }
}
