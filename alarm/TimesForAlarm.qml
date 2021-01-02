import QtQuick 2.0
import QtQuick.Controls 2.12

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
                days: "Mon"
                vibro: false
                description: "Будильник"
                longest: "5"
                longestOfPause: "10"
            }
            ListElement {
                time: "23:30"
                days: "Sun"
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

            onIsTimeChanged: {
                if (isTime === true)
                    audio.play()
                else
                    audio.stop()
            }
        }
    }
}
