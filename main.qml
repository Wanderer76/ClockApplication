import QtQuick 2.12
import QtQuick.Controls 2.12

import "pages"
import "clock"
import "alarm"

ApplicationWindow {
    id: applicationWindow
    visible: true
    minimumHeight: 640
    minimumWidth: 480

    title: qsTr("Часы")

    property bool isMainPage: stackView.depth === 1
    property bool isAlarmSignal: false

    Keys.onBackPressed: {
        if (stackView.depth > 1)
            stackView.pop()
    }
    StackView {
        id: stackView
        clip: true
        anchors.fill: parent
        initialItem: swipeView
        Keys.onBackPressed: {
            if (stackView.depth > 1) {
                stackView.pop()
            }
        }
    }

    SwipeView {
        id: swipeView
        clip: true
        currentIndex: tabBar.currentIndex
        interactive: false
        AlarmPage {
            id: alamPage
        }
        WorldTimePage {
            id: worldTimePage
        }
        StopwatchPage {
            id: stopwatchPage
        }
        TimerPage {
            id: timerPage
        }
    }

    ButtonAdd {
        id: addButton
        property bool isStopwatchActive: false
        height: 45
        width: height
        z: 2
        visible: isMainPage
        anchors.bottom: tabBar.top
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        enabled: {
            if (tabBar.currentIndex === 3 && timerPage.isNull)
                return false
            else
                return true
        }

        imageValue: {
            if (tabBar.currentIndex === 0 || tabBar.currentIndex === 1)
                return "qrc:/images/plus (1).svg"
            if (tabBar.currentIndex === 2 || tabBar.currentIndex === 3) {
                if (stopwatchPage.isActive || timerPage.timer.isActive)
                    return "qrc:/images/pause.svg"
                else
                    return "qrc:/images/play (1).svg"
            }
        }
        onClicked: {
            if (tabBar.currentIndex === 0) {
                stackView.push("qrc:/pages/NewAlarmTimePage.qml")
            }
            if (tabBar.currentIndex === 1) {
                stackView.push("qrc:/pages/AddWorldTimePage.qml")
            }
            if (tabBar.currentIndex === 2) {
                Stopwatch.startTimer()
            }
            if (tabBar.currentIndex === 3) {
                timerPage.timer.timerTime.running = !timerPage.timer.isActive
                TimerHelper.startTimer()
            }
        }
    }

    footer: TabBar {
        id: tabBar
        width: parent.width
        height: 50
        contentHeight: height
        position: TabBar.Footer
        visible: isMainPage
        currentIndex: 0
        antialiasing: true

        PagesDelegate {
            textValue: qsTr("Будильник")
            imageValue: "qrc:/images/alarm-clock.svg"
        }
        PagesDelegate {
            textValue: qsTr("Мир.время")
            imageValue: "qrc:/images/globe.svg"
        }
        PagesDelegate {
            textValue: qsTr("Секундомер")
            imageValue: "qrc:/images/stopwatch.svg"
        }
        PagesDelegate {
            textValue: qsTr("Таймер")
            imageValue: "qrc:/images/timer.svg"
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_width:220}
}
##^##*/

