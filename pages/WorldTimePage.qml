import QtQuick 2.12
import QtQuick.Controls 2.12
import "../clock"

Page {
    id: page

    function parseMounth(mounth) {
        let result = ""
        switch (mounth) {
        case 0:
            result = "Января"
            break
        case 1:
            result = "Февраля"
            break
        case 2:
            result = "Марта"
            break
        case 3:
            result = "Апреля"
            break
        case 4:
            result = "Майя"
            break
        case 5:
            result = "Июня"
            break
        case 6:
            result = "Июля"
            break
        case 7:
            result = "Августа"
            break
        case 8:
            result = "Сентября"
            break
        case 9:
            result = "Октября"
            break
        case 10:
            result = "Ноября"
            break
        case 11:
            result = "Декабря"
            break
        }
        return result
    }
    function parseDay(day) {
        let result = ""
        switch (day) {
        case 0:
            result = "Воскресенье"
            break
        case 1:
            result = "Понедельник"
            break
        case 2:
            result = "Вторник"
            break
        case 3:
            result = "Среда"
            break
        case 4:
            result = "Четверг"
            break
        case 5:
            result = "Пятница"
            break
        case 6:
            result = "Суббота"
            break
        }
        return result
    }

    Label {
        id: label
        text: "Мир. время"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 20
        anchors.topMargin: 15
        font.pointSize: 20
    }

    MainClock {
        id: clock
        width: 240
        height: 240
        anchors.top: label.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 20
    }

    Label {
        id: label1
        x: 307
        text: qsTr(parseDay(
                       clock.dayOfWeek) + ", " + clock.day + " " + parseMounth(
                       clock.mounth) + ", " + clock.year + " год")
        anchors.top: clock.bottom
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
