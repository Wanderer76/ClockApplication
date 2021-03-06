import QtQuick 2.12

Canvas {
    id: canvas
    width: parent.width - 20
    height: width
    antialiasing: true
    property alias canvasRoot: canvas
    property color primaryColor: "lightblue"
    property color secondaryColor: "orange"
    property real centerWidth: width / 2
    property real centerHeight: height / 2
    property real radius: Math.min(canvas.width, canvas.height) / 2

    property real minimumValue: 0
    property real maximumValue: 100
    property real currentValue: 0
    property real angle: (currentValue - minimumValue) / (maximumValue - minimumValue) * 2 * Math.PI

    property real angleOffset: -Math.PI / 2
    property string text: "Text"

    signal clicked

    onPrimaryColorChanged: requestPaint()
    onSecondaryColorChanged: requestPaint()
    onMinimumValueChanged: requestPaint()
    onMaximumValueChanged: requestPaint()
    onCurrentValueChanged: requestPaint()

    onPaint: {
        var ctx = getContext("2d")
        ctx.save()

        ctx.clearRect(0, 0, canvas.width, canvas.height)

        ctx.beginPath()
        ctx.lineWidth = 4
        ctx.strokeStyle = primaryColor
        ctx.arc(canvas.centerWidth, canvas.centerHeight, canvas.radius,
                angleOffset + canvas.angle, angleOffset + 2 * Math.PI)
        ctx.stroke()

        ctx.beginPath()
        ctx.lineWidth = 6
        ctx.strokeStyle = canvas.secondaryColor
        ctx.arc(canvas.centerWidth, canvas.centerHeight, canvas.radius,
                canvas.angleOffset, canvas.angleOffset + canvas.angle)
        ctx.stroke()

        ctx.restore()
    }

    Text {
        anchors.centerIn: parent
        font.pointSize: 20
        text: canvas.text
        color: canvas.primaryColor
        onTextChanged: {

            //  canvas.requestPaint()
        }
    }
}
