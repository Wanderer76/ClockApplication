import QtQuick 2.12
import QtQuick.Controls 2.12
import AlarmsModel 1.0

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

        delegate: TimesDelegate {
            id: deleg
            width: parent.width
        }

        Connections {
            target: model
            function onShouldAlarm(currIndex) {
                indexOfAlarm = currIndex
                isAlarmSignal = true
            }
        }
    }
}
