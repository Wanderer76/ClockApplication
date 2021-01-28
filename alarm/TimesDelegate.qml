import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../controls"
import "../pages"

SwipeDelegate {
    id: swipeDelegate
    property alias alarm: control
    height: 80
    width: 480

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
        id: element
        Label {
            id: timeText

            text: qsTr(time)
            anchors.left: parent.left
            anchors.leftMargin: 15
            anchors.top: parent.top
            anchors.topMargin: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 18
        }

        Label {
            id: daysText
            text: qsTr(description + ", " + parseDays())
            anchors.top: timeText.bottom
            anchors.left: element.left
            anchors.topMargin: 2
            anchors.leftMargin: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 13
            color: "#666666"
        }

        Switch {
            id: control
            width: 60
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            checked: isActive
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
            onClicked: {
                isActive = !isActive
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
    function parseDays() {
        if (days.length > 0) {
            if (days.length === 7)
                return qsTr("Каждый день")
            else if (days.length === 1)
                return qsTr(days[0])
            else if (days.length === 2)
                return qsTr(days[0] + "," + days[1])
            else if (days.length > 2)
                return qsTr(days[0] + "-" + days[days.length - 1])
        } else
            return "Без повтора"
    }
    onClicked: {
        stackView.push("qrc:/pages/AlarmEditPage.qml", {
                           "currentIndex": index,
                           "daysOfWeek": days,
                           "time": time,
                           "longest": longest / 1000,
                           "songUrl": sound,
                           "descriptionText": description,
                           "vibration": vibration
                       })
    }
}
