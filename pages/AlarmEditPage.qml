import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Dialogs 1.3
import "../alarm"
import "../controls"

Page {
    id: page

    property var daysOfWeek: []

    property int currentIndex: 0
    property int hourIndex: time.split(":")[0]
    property int minuteIndex: time.split(":")[1]
    property int longest: 0
    property string time: ""
    property string songUrl: ""
    property string descriptionText: ""
    property bool vibration: false

    clip: true
    focusPolicy: Qt.ClickFocus

    property bool isEnable: true

    header: HeaderToolBar {
        titleText: "Изменить"
        cancelButton.onClicked: {
            stackView.pop()
        }
        acceptButton.onClicked: {

            stackView.pop(
                        alamPage.alarms.alarmModel.editElement(currentIndex,
                                                               daysOfWeek, songUrl,
                                                               (hourView.currentIndex < 10 ? "0" + hourView.currentIndex : hourView.currentIndex) + ":" + (minuteView.currentIndex < 10 ? "0" + minuteView.currentIndex : minuteView.currentIndex), description.additionalText,
                                                               alarmLongest.time * 1000,
                                                               10 * 1000,
                                                               3, vibro.switchElement.checked
                                                               == true))
        }
    }
    function parseDays() {
        var checked = []
        for (var i = 0; i < dayOFWeeks.repeaterElem.count; i++) {
            if (dayOFWeeks.repeaterElem.itemAt(i).checked === true) {
                checked.push(dayOFWeeks.repeaterElem.itemAt(i).text)
            }
        }
        for (var i = 0; i < checked.length; i++) {
            switch (checked[i]) {
            case dayOFWeeks.days[0]:
                checked[i] = qsTr("Пн")
                break
            case dayOFWeeks.days[1]:
                checked[i] = qsTr("Вт")
                break
            case dayOFWeeks.days[2]:
                checked[i] = qsTr("Ср")
                break
            case dayOFWeeks.days[3]:
                checked[i] = qsTr("Чт")
                break
            case dayOFWeeks.days[4]:
                checked[i] = qsTr("Пт")
                break
            case dayOFWeeks.days[5]:
                checked[i] = qsTr("Сб")
                break
            case dayOFWeeks.days[6]:
                checked[i] = qsTr("Вс")
                break
            }
        }

        return checked
    }

    DayOFWeeks {
        id: dayOFWeeks
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

            daysOfWeek = temp

            if (daysOfWeek.length === 0)
                days.additionalText = "Без повтора"
            else if (daysOfWeek.length === 1)
                days.additionalText = daysOfWeek[0]
            else if (daysOfWeek.length === 2)
                days.additionalText = daysOfWeek[0] + "," + daysOfWeek[1]
            else
                days.additionalText = daysOfWeek[0] + "," + daysOfWeek[daysOfWeek.length - 1]
            dayOFWeeks.visible = false
        }
        cancelButton.onClicked: {
            dayOFWeeks.visible = false
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
        textField.text: descriptionText
        acceptButton.onClicked: {
            descriptionText = alarmDescription.text
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
            longest = alarmLongest.time
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
            if (alarmDescription.visible === true || dayOFWeeks.visible === true
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
                currentIndex: hourIndex
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
                currentIndex: minuteIndex
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
            visible: {
                if (alarmDescription.visible === true
                        || dayOFWeeks.visible === true
                        || alarmLongest.visible === true)
                    return true
                else
                    return false
            }

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
                additionalText: daysOfWeek.length === 0 ? "Без повтора" : daysOfWeek[0] + ","
                                                          + daysOfWeek[daysOfWeek.length - 1]
                mouseArea.onClicked: {
                    dayOFWeeks.visible = true
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
                additionalText: songUrl
                mouseArea.onClicked: {
                    songUrl = FileHelper.getUrl()
                    song.additionalText = FileHelper.getOpenFileName()
                }
                Connections {
                    target: FileHelper
                    function onPathChanged(str) {
                        songUrl = str
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
                switchElement.checked: vibration
            }

            AlarmSettingButton {
                id: description
                width: parent.width
                anchors.right: parent.right
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                anchors.left: parent.left
                mainText: "Описание"
                additionalText: descriptionText
                mouseArea.onClicked: {
                    alarmDescription.visible = true
                }
            }

            AlarmSettingButton {
                id: longestText
                width: parent.width
                anchors.right: parent.right
                anchors.rightMargin: 5
                anchors.left: parent.left
                anchors.leftMargin: 5
                mainText: "Длительность сигнала"
                additionalText: longest + " мин"
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
