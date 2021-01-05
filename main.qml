import QtQuick 2.12
import QtQuick.Controls 2.12
import "pages"
import "clock"
import "alarm"

ApplicationWindow {
    id: applicationWindow
    visible: true
    height: 640
    width: 480
    title: qsTr("Часы")
    property bool isMainPage: stackView.depth === 1
    property bool isAlarmSignal: false

    Alarms {
        id: audio
    }
    onIsAlarmSignalChanged: {
        var element = alamPage.alarms.viewList.model.get(
                    alamPage.alarms.indexOfAlarm)
        if (isAlarmSignal === true) {
            audio.startAlarm(element.vibro)
            stackView.push("qrc:/pages/AlarmSignalPage.qml", {
                               "time": element.time,
                               "desc": element.description,
                               "pauseLong": element.longestOfPause,
                               "longestCount": element.longest,
                               "currentIndex": element.index
                           })
        } else {
            audio.stopAlarm()
        }
    }

    SwipeView {
        id: view
        anchors.fill: parent
        currentIndex: tabBar.currentIndex
        interactive: false
        AlarmPage {
            id: alamPage
        }
        WorldTimePage {
            id: worldTimePage
        }
        Page {
            Rectangle {
                anchors.fill: parent
                color: "green"
            }
        }
        Page {
            Rectangle {
                anchors.fill: parent
                color: "blue"
            }
        }
    }
    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: view
    }

    ButtonAdd {
        height: 45
        width: height
        z: 2
        visible: isMainPage
        anchors.bottom: tabBar.top
        anchors.bottomMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        imageValue: "qrc:/images/plus (1).svg"
        onClicked: {
            if (tabBar.currentIndex == 0) {
                stackView.push("qrc:/pages/NewAlarmTimePage.qml")
            }
        }
    }

    footer: TabBar {
        id: tabBar
        width: parent.width
        height: 60
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

