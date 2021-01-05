import QtQuick 2.12
import QtMultimedia 5.12

Item {
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
            Vibration.vibrate(800)
        }
    }
    Audio {
        id: audio
        source: "qrc:/songs/28. Lacrimosa.mp3"
        audioRole: Audio.AlarmRole
    }
}
