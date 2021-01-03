import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml.Models 2.12

Item {
    property alias viewList: view
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
                days: "Вс"
                vibro: false
                description: "Будильник"
                longest: "5"
                longestOfPause: "10"
            }
        }

        Alarms {
            id: audio
        }

        delegate: TimesDelegate {
            width: parent.width
            Timer {
                id: vibroTimer
                interval: 3000
                repeat: true
                onTriggered: {
                    Vibration.vibrate(800)
                }
            }

            onIsTimeChanged: {
                if (isTime === true) {
                    audio.play()
                    vibroTimer.start()
                } else {
                    vibroTimer.stop()
                    audio.stop()
                }
            }
        }
    }
}
