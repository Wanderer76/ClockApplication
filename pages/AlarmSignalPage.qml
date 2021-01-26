import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0

Page {
    property string time: ""
    property string desc: ""
    property string pauseLong: ""
    property string longestCount: ""
    property int currentIndex: 0
    Timer {
        interval: longestCount * 60000
        running: true
        onTriggered: {
            isAlarmSignal = false
            stackView.pop()
        }
    }

    RecursiveBlur {}

    Rectangle {
        id: rectangle
        color: "#6c9dcb"
        anchors.fill: parent
        antialiasing: true
        z: 1

        Label {
            id: timeLabel
            x: 143
            width: 120
            height: 47
            color: "#ffffff"
            text: qsTr(time)
            anchors.top: parent.top
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.topMargin: 60
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 32
        }

        Label {
            id: descLabel

            width: 176
            color: "#ffffff"
            text: qsTr(desc)
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -20
            font.pointSize: 27
            anchors.horizontalCenter: parent.horizontalCenter
        }

        RoundButton {
            id: pauseButton
            width: 176
            height: 40
            anchors.top: descLabel.bottom
            antialiasing: true
            highlighted: false
            flat: false
            anchors.topMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            background: Rectangle {
                radius: parent.radius
                anchors.fill: parent
                color: "#80ffffff"
            }
            contentItem: Label {
                anchors.centerIn: pauseButton
                text: qsTr("Пауза" + "(" + pauseLong + "минут)")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.capitalization: Font.AllUppercase
                font.pointSize: 12
                color: "white"
            }
        }

        ScrollBar {
            id: offSlider
            width: 200
            height: 30
            anchors.top: pauseButton.bottom
            size: 0
            antialiasing: true
            snapMode: Slider.SnapOnRelease
            policy: ScrollBar.AlwaysOn
            orientation: Qt.Horizontal
            anchors.topMargin: 110
            anchors.horizontalCenter: parent.horizontalCenter
            position: 0.5
            background: Rectangle {
                color: "#80ffffff"
                radius: 15
                implicitHeight: height
                implicitWidth: width
            }

            contentItem: Rectangle {
                implicitWidth: height
                implicitHeight: height
                radius: width / 2
                color: offSlider.pressed ? Qt.darker("lightgreen",
                                                     1.1) : "lightgreen"
            }
            onPositionChanged: {
                if (position === 1 || position === 0) {
                    isAlarmSignal = false
                    //AudioHelper.stop()
                    AudioHelper.close()
                    stackView.pop()
                }
            }

            onPressedChanged: {
                if (!offSlider.pressed && (position != 1 || position != 0)) {
                    position = 0.5
                }
            }
        }

        Label {
            id: helpLabel
            color: "#ffffff"
            text: qsTr("Проведите, чтобы выключить будильник")
            anchors.top: offSlider.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            font.pointSize: 10
            anchors.topMargin: 25
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/

