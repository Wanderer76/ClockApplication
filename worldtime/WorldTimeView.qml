import QtQuick 2.12
import UserWorldTimeModel 1.0

Item {
    property alias worldTimeView: view
    property int minute: 0

    ListView {
        id: view
        anchors.fill: parent

        model: UserWorldTimeModel {
            id: model
        }
        delegate: WorldtimeDelegate {
            width: parent.width
        }
    }
}
