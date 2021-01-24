import QtQuick 2.12
import QtQuick.Controls 2.12

Item {
    width: 480
    height: 480
    property alias progressBar: progress
    property alias timerTime: timer
    property bool isActive: timer.running

    Timer {
        id: timer
        running: false
        interval: 1000
        repeat: true
        onTriggered: {
            if (progress.currentValue !== progress.maximumValue) {
                progress.currentValue++
                console.log(progress.currentValue)
            } else {
                TimerHelper.stopTimer()
                Notifier.notification = "Время вышло"
                timer.running = false
            }
        }
    }

    TimerProgressBar {
        id: progress
        anchors.fill: parent
        currentValue: 0

        onMaximumValueChanged: {
            console.log(progress.maximumValue)
        }
    }
}
