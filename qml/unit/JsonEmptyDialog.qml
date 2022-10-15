import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent




    property string text
    signal okClicked()
    signal retryClicked()

    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.3
    }

    MouseArea {
        anchors.fill: parent
        propagateComposedEvents: false
    }

    Rectangle {
        anchors.centerIn: parent
        width: 200; height: 100
        border.width: 1
        border.color: "black"
        radius: 2
        Text {
            id: label
            text: root.text
            width: parent.width
            height: retryBtn.y
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
        }

        PButton {
            id: retryBtn
            width: 50
            height: 30
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: -((parent.width - width* 2)/6 + width/2)
            text: "Retry"
            onClicked: retryClicked()
        }

        PButton {
            id: okBtn
            width: 50
            height: 30
            anchors.verticalCenter: retryBtn.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: ((parent.width - width* 2)/6 + width/2)
            text: "OK"
            onClicked: okClicked()
        }
    }
}
