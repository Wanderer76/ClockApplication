import QtQuick 2.12

Item {
    ListView {
        id: view
        anchors.fill: parent
        clip: true
        spacing: 2
        model: ListModel {}

        delegate: LapDelegate {}
    }
}
