import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    property alias lapView: view
    property int lastIndex: view.model.count + 1
    ListView {
        id: view
        anchors.fill: parent
        clip: true
        spacing: 5

        model: ListModel {}

        delegate: LapDelegate {
            width: parent.width
        }
    }
}
