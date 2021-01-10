import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    ListView {
        id: view
        anchors.fill: parent
        clip: true
        spacing: 5

        model: ListModel {
            ListElement {
                segmentNumber: 1
                time: "00:05:10"
            }
            ListElement {
                segmentNumber: 2
                time: "00:05:10"
            }
            ListElement {
                segmentNumber: 3
                time: "00:05:50"
            }
            ListElement {
                segmentNumber: 4
                time: "00:15:10"
            }
            ListElement {
                segmentNumber: 5
                time: "00:25:10"
            }
            ListElement {
                segmentNumber: 6
                time: "00:35:10"
            }
            ListElement {
                segmentNumber: 7
                time: "00:45:10"
            }
        }

        delegate: LapDelegate {
            width: parent.width
        }
    }
}
