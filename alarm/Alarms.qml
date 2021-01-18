import QtQuick 2.12
import QtMultimedia 5.12

Item {
    property url audioSource: ""

    function startAlarm(shouldVibrate) {
        if (shouldVibrate === true)
            vibroTimer.start()
        audio.play()
    }
    function stopAlarm() {
        if (vibroTimer.running === true)
            vibroTimer.stop()
        audio.stop()
    }

    Timer {
        id: vibroTimer
        interval: 3000
        repeat: true
        onTriggered: {
            console.log("Vibrate")
            core.vibrate(800)
        }
    }
    Audio {
        id: audio
        source: audioSource
        autoLoad: true
        //audioRole: Audio.AlarmRole
        onSourceChanged: {
            console.log("SOURCE - " + source)
        }
    }
}
