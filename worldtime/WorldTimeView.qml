import QtQuick 2.12
import WorldTimeList 1.0

Item {
    property alias worldTimeView: view
    ListView {
        id: view
        anchors.fill: parent
        model: WorldTimeList {}
        delegate: WorldtimeDelegate {
            width: parent.width
        }
    }
}
