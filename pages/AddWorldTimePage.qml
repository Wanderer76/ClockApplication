import QtQuick 2.12
import QtQuick.Controls 2.12
import TimeZones 1.0
import QtQuick.Layouts 1.12
import "../controls"

Page {
    header: ToolBar {

        height: 50
        activeFocusOnTab: false
        antialiasing: true
        wheelEnabled: false
        contentHeight: 35
        contentWidth: 190
        enabled: true
        focusPolicy: Qt.TabFocus
        width: parent.width

        background: Rectangle {
            anchors.fill: parent
            color: "white"
        }
        RowLayout {
            width: parent.width
            height: parent.height
            ToolButton {
                width: 35
                height: 35
                Layout.leftMargin: 0
                Layout.alignment: Qt.AlignLeft | Qt.AlignBaseline
                display: AbstractButton.IconOnly
                icon.source: "qrc:/images/left-arrow.svg"
                leftPadding: 10
                highlighted: false
                flat: true
                background: Rectangle {
                    anchors.fill: parent
                    color: "white"
                }
                onClicked: {
                    stackView.pop()
                }
            }

            Label {
                text: qsTr("Добавить")
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pointSize: 17
            }
        }
    }

    ListView {
        clip: true
        anchors.fill: parent
        cacheBuffer: 4096
        spacing: 10
        model: TimeZones {
            id: mod
        }
        delegate: AddWorldTimeDelegate {
            width: parent.width
            opacity: mouse.pressed ? 0.5 : 1
            MouseArea {
                id: mouse
                anchors.fill: parent
                onClicked: {
                    let result = mod.findCountryTime(index)
                    console.log(result)
                    let arr = result.split('-')
                    if (arr[0] !== "") {
                        console.log(arr)
                        stackView.pop(
                                    worldTimePage.list.worldTimeView.model.append({
                                                                                      "country": arr[1],
                                                                                      "time": arr[0]
                                                                                  }))
                    }
                }
            }
        }
    }
}
