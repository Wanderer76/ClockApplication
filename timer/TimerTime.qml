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

    Tumbler {
        id: hour
        width: 40
        spacing: 25
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        model: 100
        delegate: TimerDelegate {
            text: index
        }
        onCurrentIndexChanged: {
            TimerHelper.setHours(currentIndex)
            clock.progressBar.maximumValue = TimerHelper.getMaxValue()
        }
    }

    Tumbler {
        id: minute
        width: 40
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 25
        model: 60

        delegate: TimerDelegate {
            text: index
        }
        onCurrentIndexChanged: {
            TimerHelper.setMinutes(currentIndex)
            clock.progressBar.maximumValue = TimerHelper.getMaxValue()
        }
    }
    Tumbler {
        id: second
        width: 40
        spacing: 25
        model: 60
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        anchors.rightMargin: 0

        delegate: TimerDelegate {
            text: index
        }
        onCurrentIndexChanged: {
            TimerHelper.setSeconds(currentIndex)
            clock.progressBar.maximumValue = TimerHelper.getMaxValue()
        }
    }
}
