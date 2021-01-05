import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQml.Models 2.12
import "../pages"

Item {
    property alias viewList: view
    property int indexOfAlarm: 0
    ListView {
        id: view
        spacing: 2
        anchors.fill: parent
        model: ListModel {
            id: model
            ListElement {
                time: "24:00"
                days: "Пн"
                vibro: false
                description: "Будильник"
                longest: "5"
                longestOfPause: "10"
            }
            ListElement {
                time: "23:30"
                days: ""
                vibro: true
                description: "Будильник"
                longest: "1"
                longestOfPause: "10"
            }
        }

        delegate: TimesDelegate {
            id: deleg
            width: parent.width
            onIsTimeChanged: {
                if (isTime === true) {
                    indexOfAlarm = index
                    isAlarmSignal = true
                    if (days === "")
                        isTime = false
                }
            }
        }
    }
}
