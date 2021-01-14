import QtQuick 2.12
import QtQuick.Controls 2.12

Label {
    id: lbl
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    font.pointSize: 20
    color: ListView.isCurrentItem ? "#007dfe" : "black"
}
