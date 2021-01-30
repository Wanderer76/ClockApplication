import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import "../alarm"
import "../controls"

Page {
    id: page
    clip: true
    focusPolicy: Qt.ClickFocus

    property bool isEnable: true
    property var daysArray: []
    property url sound: "qrc:/songs/28. Lacrimosa.mp3"

    property bool isEdit: {
        if (alarmDescription.visible === true || daysOFWeeks.visible === true
                || alarmLongest.visible === true)
            return true
        else
            return false
    }

    header: HeaderToolBar {

        visible: !isEdit

        titleText: "Добавить"
        cancelButton.onClicked: {
            stackView.pop()
        }

        acceptButton.onClicked: {

            stackView.pop(
                        alamPage.alarms.alarmModel.append(daysArray,
                                                          sound, (hourView.currentIndex < 10 ? "0" + hourView.currentIndex : hourView.currentIndex) + ":" + (minuteView.currentIndex < 10 ? "0" + minuteView.currentIndex : minuteView.currentIndex), description.additionalText, alarmLongest.time * 1000, 10 * 1000, 3,
                                                          vibro.switchElement.checked == true))
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
            var temp = []
            if (checked.length > 0) {
                for (var i = 0; i < checked.length; i++) {
                    temp.push(checked[i])
                }
            }

            daysArray = temp

            if (daysArray.length === 0)
                days.additionalText = "Без повтора"
            else if (daysArray.length === 1)
                days.additionalText = daysArray[0]
            else if (daysArray.length === 2)
                days.additionalText = daysArray[0] + "," + daysArray[1]
            else
                days.additionalText = daysArray[0] + "," + daysArray[daysArray.length - 1]
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

    AlarmLongest {
        id: alarmLongest
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
        onTimeChanged: {
            alarmLongest.visible = false
        }

        cancelButton.onClicked: {
            alarmLongest.visible = false
        }
    }

    Rectangle {
        id: rectangle1
        anchors.fill: parent
        color: "white"
        visible: true
        enabled: {
            if (alarmDescription.visible === true
                    || daysOFWeeks.visible === true
                    || alarmLongest.visible === true)
                return false
            else
                return true
        }

        Item {
            id: element
            width: 200
            height: 200
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 45

            Tumbler {
                id: hourView
                model: 24
                width: 40
                spacing: 20
                antialiasing: true
                anchors.bottom: parent.bottom
                anchors.top: parent.top
                anchors.left: parent.left
                clip: true
                delegate: Label {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    opacity: 1.0 - Math.abs(
                                 Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)

                    font.pointSize: 22
                    text: index < 10 ? "0" + index : index
                    textFormat: Text.PlainText
                }
            }

            Tumbler {
                id: minuteView
                model: 60
                width: 40
                spacing: 20
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                antialiasing: true
                clip: true
                delegate: Label {
                    width: 640
                    height: 480
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    opacity: 1.0 - Math.abs(
                                 Tumbler.displacement) / (Tumbler.tumbler.visibleItemCount / 2)
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
            anchors.horizontalCenterOffset: 0
            border.color: "#9f9f9f"
            anchors.verticalCenter: element.verticalCenter
        }

        Rectangle {
            id: shadowOverlay
            color: "#df0e0e0e"
            visible: isEdit

            z: 1

            enabled: false
            width: parent.width
            height: parent.height + 60
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
                additionalText: daysArray.length === 0 ? "Без повтора" : daysArray[0] + ","
                                                         + daysArray[daysArray.length - 1]
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
                    sound = FileHelper.getUrl()
                    additionalText = FileHelper.getOpenFileName()
                }
                Connections {
                    target: FileHelper
                    function onPathChanged(str) {
                        sound = str
                    }
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
                additionalText: alarmLongest.time + " мин"
                mouseArea.onClicked: {
                    alarmLongest.visible = true
                }
            }
            AlarmSettingButton {
                id: pauseLong
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Длительность паузы"
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

