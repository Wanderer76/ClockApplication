import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    property int hourIndex: hour.currentIndex
    property int minuteIndex: minute.currentIndex
    property int secondIndex: second.currentIndex
    id: item1
    width: 316
    height: 145
    function clear() {
        hour.currentIndex = 0
        minute.currentIndex = 0
        second.currentIndex = 0
    }

    ListView {
        id: hour
        width: 40
        spacing: 20
        height: parent.height
        anchors.left: parent.left
        anchors.leftMargin: 35
        flickableDirection: Flickable.VerticalFlick
        layoutDirection: Qt.RightToLeft
        snapMode: ListView.SnapPosition
        highlightRangeMode: ListView.StrictlyEnforceRange
        model: 100
        delegate: TimerDelegate {
            text: index
        }
    }

    ListView {
        id: minute
        width: 40
        spacing: 20
        model: 60
        flickableDirection: Flickable.VerticalFlick
        layoutDirection: Qt.RightToLeft

        snapMode: ListView.SnapPosition
        highlightRangeMode: ListView.StrictlyEnforceRange

        anchors.left: hour.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.leftMargin: 50
        delegate: TimerDelegate {

            text: index
        }
    }
    ListView {
        id: second
        width: 40
        spacing: 20
        model: 60
        height: parent.height
        anchors.left: minute.right
        antialiasing: true
        layoutDirection: Qt.LeftToRight
        anchors.leftMargin: 50
        flickableDirection: Flickable.VerticalFlick
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.top: parent.top
        anchors.topMargin: 0
        snapMode: ListView.SnapPosition
        highlightRangeMode: ListView.StrictlyEnforceRange

        delegate: TimerDelegate {
            text: index
        }
    }
}
