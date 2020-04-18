import QtQuick 2.0
import QtQuick.Controls 2.5

Button {
    id: control
    text: qsTr("Load Log")

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.7
        color: control.down ? "#20B2AA" : "#4169E1"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 40
        opacity: enabled ? 1 : 0.7
        border.color: control.down ? "#20B2AA" : "#4169E1"
        border.width: 2
        radius: 2
    }
}
