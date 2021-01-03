import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "../alarm"
import "../controls"

Page {
    id: page
    clip: true
    property bool isEnable: true
    focusPolicy: Qt.ClickFocus

    header: ToolBar {
        height: 60
        enabled: isEnable
        position: ToolBar.Header
        width: parent.width

        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
        RowLayout {
            width: parent.width
            height: parent.height
            ToolButton {
                width: height
                height: parent.height
                text: qsTr("X")
                leftPadding: 30
                font.pointSize: 22
                highlighted: false
                Layout.alignment: Qt.AlignLeft
                flat: true
                background: Rectangle {
                    anchors.fill: parent
                    color: "white"
                }

                onClicked: {
                    stackView.pop()
                }
            }

            Label {
                text: qsTr("Добавить")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 22
            }

            ToolButton {
                height: parent.height
                width: height
                text: qsTr("✓")
                rightPadding: 30
                font.pointSize: 22
                flat: true
                Layout.alignment: Qt.AlignRight

                background: Rectangle {
                    anchors.fill: parent
                    color: "white"
                }

                onClicked: {

                    stackView.pop(alamPage.alarms.viewList.model.append({
                                                                            "time": qsTr((hourView.currentIndex < 10 ? "0" + hourView.currentIndex : hourView.currentIndex) + ":" + (minuteView.currentIndex < 10 ? "0" + minuteView.currentIndex : minuteView.currentIndex)),
                                                                            "days": days.additionalText,
                                                                            "vibro": vibro.switchElement.checked,
                                                                            "description": description.additionalText,
                                                                            "longest": longest.additionalText,
                                                                            "longestOfPause": pauseLong.additionalText
                                                                        }))
                }
            }
        }
    }
    function parseDays() {
        var checked = []
        for (var i = 0; i < daysOFWeeks.repeaterElem.count; i++) {
            if (daysOFWeeks.repeaterElem.itemAt(i).checked === true) {
                checked.push(daysOFWeeks.repeaterElem.itemAt(i).text)
            }
        }
        for (var i = 0; i < checked.length; i++) {
            switch (checked[i]) {
            case daysOFWeeks.days[0]:
                checked[i] = qsTr("Пн")
                break
            case daysOFWeeks.days[1]:
                checked[i] = qsTr("Вт")
                break
            case daysOFWeeks.days[2]:
                checked[i] = qsTr("Ср")
                break
            case daysOFWeeks.days[3]:
                checked[i] = qsTr("Чт")
                break
            case daysOFWeeks.days[4]:
                checked[i] = qsTr("Пт")
                break
            case daysOFWeeks.days[5]:
                checked[i] = qsTr("Сб")
                break
            case daysOFWeeks.days[6]:
                checked[i] = qsTr("Вс")
                break
            }
        }

        return checked
    }

    DayOFWeeks {
        id: daysOFWeeks
        visible: false
        height: page.height * 0.7
        width: page.width
        z: 1
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        acceptButton.onClicked: {
            var checked = parseDays()
            if (checked.length === 7) {
                days.additionalText = qsTr("Каждый день")
            } else if (checked.length === 2) {
                days.additionalText = checked[0] + "," + checked[checked.length - 1]
            } else if (checked.length === 1) {
                days.additionalText = checked[0]
            } else {
                days.additionalText = checked[0] + "-" + checked[checked.length - 1]
            }
            daysOFWeeks.visible = false
        }
        cancelButton.onClicked: {
            daysOFWeeks.visible = false
        }
    }

    AlarmDescription {
        id: alarmDescription
        height: 195
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 15
        z: 1
        anchors.verticalCenterOffset: 30
        anchors.verticalCenter: parent.verticalCenter
        visible: false
        acceptButton.onClicked: {
            description.additionalText = alarmDescription.text
            alarmDescription.visible = false
        }
        cancelButton.onClicked: {
            alarmDescription.visible = false
        }
    }

    Rectangle {
        id: rectangle1
        anchors.fill: parent
        color: "white"
        visible: true
        enabled: {
            if (alarmDescription.visible === true
                    || daysOFWeeks.visible === true)
                return false
            else
                return true
        }

        Item {
            id: element
            width: parent.width / 2 // 188
            height: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 50

            ListView {
                id: hourView
                width: 40
                flickableDirection: Flickable.VerticalFlick
                layoutDirection: Qt.RightToLeft
                contentHeight: 1024
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                snapMode: ListView.SnapOneItem
                highlightRangeMode: ListView.StrictlyEnforceRange
                spacing: 20
                anchors.left: parent.left
                anchors.leftMargin: 0
                Layout.alignment: Qt.AlignHCenter | Qt.AlignLeft
                model: 25
                antialiasing: true
                clip: true
                delegate: Label {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    font.pointSize: 22
                    color: ListView.isCurrentItem ? "#007dfe" : "black"
                    text: index < 10 ? "0" + index : index
                    textFormat: Text.PlainText
                }
            }
            ListView {
                id: minuteView
                width: 40
                highlightRangeMode: ListView.StrictlyEnforceRange
                contentHeight: 1024
                keyNavigationWraps: false
                layoutDirection: Qt.LeftToRight
                snapMode: ListView.SnapOneItem
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                spacing: 20
                anchors.right: parent.right
                anchors.rightMargin: 0
                Layout.leftMargin: -10
                Layout.alignment: Qt.AlignRight | Qt.AlignHCenter
                model: 61
                antialiasing: true
                clip: true
                delegate: Label {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    color: ListView.isCurrentItem ? "#007dfe" : "black"

                    font.pointSize: 22
                    text: index < 10 ? "0" + index : index
                    textFormat: Text.PlainText
                }
            }
        }
        Rectangle {
            id: rectangle
            x: -10
            width: parent.width + 20
            height: 40
            color: "#00ffffff"
            anchors.top: element.top
            anchors.topMargin: 0
            anchors.horizontalCenterOffset: 0
            border.color: "#9f9f9f"
        }

        Rectangle {
            id: shadowOverlay
            color: "#df0e0e0e"
            visible: {
                if (alarmDescription.visible === true
                        || daysOFWeeks.visible === true)
                    return true
                else
                    return false
            }

            z: 1

            enabled: false
            anchors.fill: parent
        }

        Column {
            id: column
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 50
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.top: element.bottom
            anchors.topMargin: 30
            spacing: 10

            AlarmSettingButton {
                id: days
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Дни недели"
                additionalText: "Без повтора"
                mouseArea.onClicked: {
                    daysOFWeeks.visible = true
                }
            }

            AlarmSettingButton {
                id: song
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Звук"
                additionalText: "По умолчанию"
                mouseArea.onClicked: {

                }
            }
            AlarmSettingSwitchButton {
                id: vibro
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Вибросигнал"
            }

            AlarmSettingButton {
                id: description
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Описание"
                additionalText: "Будильник"
                mouseArea.onClicked: {
                    alarmDescription.visible = true
                }
            }

            AlarmSettingButton {
                id: longest
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Длительность сигнала"
                additionalText: "5 мин"
                mouseArea.onClicked: {

                }
            }
            AlarmSettingButton {
                id: pauseLong
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Длительность сигнала"
                additionalText: "10 мин, 3х"
                mouseArea.onClicked: {

                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:10;anchors_height:180;anchors_y:0}D{i:12;anchors_height:180;anchors_y:158}D{i:9;anchors_width:480}
D{i:14;anchors_y:158}D{i:8;anchors_height:180;anchors_y:0}D{i:7;anchors_width:480}
}
##^##*/

