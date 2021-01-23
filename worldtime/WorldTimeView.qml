import QtQuick 2.12
import WorldTimeList 1.0

Item {
    property alias worldTimeView: view
    property int minute: 0

    ListView {
        id: view
        anchors.fill: parent

        model: WorldTimeList {
            id: model
        }
        delegate: WorldtimeDelegate {
            width: parent.width
        }
    }
}
