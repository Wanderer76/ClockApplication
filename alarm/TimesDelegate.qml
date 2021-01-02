import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

SwipeDelegate {

    id: swipeDelegate
    property alias alarm: control
    property bool isTime: control.checked
    height: 70
    width: parent.width
    swipe.right: Rectangle {
        id: deleteLabel
        height: parent.height - 10
        width: height
        radius: 1
        anchors.right: parent.right
        color: "#e6e6e6"
        Rectangle {
            height: parent.height * 0.75
            width: height
            radius: width / 2
            anchors.centerIn: parent
            color: deleteLabel.SwipeDelegate.pressed ? Qt.darker("tomato",
                                                                 1.1) : "tomato"
            Image {
                id: trashImage
                anchors.fill: parent
                anchors.margins: 10
                source: "qrc:/images/delete.svg"
                antialiasing: true
                fillMode: Image.PreserveAspectFit
                cache: true
                asynchronous: true
                ColorOverlay {
                    anchors.fill: parent
                    source: trashImage
                    color: "white"
                }
            }
        }

        SwipeDelegate.onClicked: view.model.remove(index)
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
        id: element
        Text {
            id: timeText
            width: 100
            height: 40
            text: qsTr(time)
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 15
        }

        Text {
            id: daysText
            width: 40
            height: 25
            text: qsTr(description + "," + days)
            anchors.horizontalCenter: timeText.horizontalCenter
            anchors.top: timeText.bottom
            anchors.topMargin: -7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 10
            color: "#666666"
        }

        Switch {
            id: control
            width: 60
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            antialiasing: true
            indicator: Rectangle {
                antialiasing: true
                implicitWidth: 50
                implicitHeight: 22
                x: control.width - width - control.rightPadding
                y: parent.height / 2 - height / 2
                radius: 13
                color: control.checked ? "#007dfe" : "#e6e6e6"

                Rectangle {
                    antialiasing: true
                    anchors.verticalCenter: parent.verticalCenter
                    x: control.checked ? parent.width - width - 3 : 1
                    width: 20
                    height: width
                    radius: 13
                    border.color: "#dcdcdc"
                }
            }
        }

        ToolSeparator {
            id: toolSeparator
            y: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            orientation: Qt.Horizontal
        }
    }
}
