import QtQuick 2.0

Item {

    ListView {

        model: ListModel {
            ListElement {
                time: "Time"
                days: ["Mon", "Tus"]
            }
            ListElement {
                time: "Time"
                days: ["Mon", "Tus"]
            }
            ListElement {
                time: "Time"
                days: ["Mon", "Tus"]
            }
        }
        delegate: Column {
            Row {
                Column {
                    Text {
                        text: model.time
                    }
                }
            }
        }
    }
}
