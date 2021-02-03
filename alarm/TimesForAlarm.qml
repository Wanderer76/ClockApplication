import QtQuick 2.12
import QtQuick.Controls 2.12
import AlarmsModel 1.0
import "../pages"

Item {
    property alias viewList: view
    property alias alarmModel: model
    property int indexOfAlarm: 0
    ListView {
        id: view
        spacing: 2
        anchors.fill: parent
        model: AlarmsModel {
            id: model
        }
        opacity: enabled ? 1 : 0.6

        delegate: TimesDelegate {
            id: deleg
            width: parent.width
        }

        Connections {
            target: model
            function onStartAlarm(index) {
                indexOfAlarm = index
                //isAlarmSignal = true
                view.enabled = false
                stackView.push("qrc:/pages/AlarmSignalPage.qml", {
                                   "time": model.getTime(index),
                                   "desc": model.getDescription(index),
                                   "pauseLong": model.getPauseLongest(index),
                                   "longestCount": model.getLongest(index),
                                   "currentIndex": index
                               })
            }
            function onPause() {
                console.log("onPause")
                stackView.pop("qrc:/pages/AlarmSignalPage.qml")
            }
            function onStopAlarm() {
                view.enabled = true
            }
        }
    }
}
