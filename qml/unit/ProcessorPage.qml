import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: root
    color: "green"
    scale: 0
    opacity: 0

    property var info

    ListView {
        id: nodeList
        model: info !== undefined? info.acsblNodeList : info
        height: parent.height - closeBtn.height - 20
        clip: true
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
        }
        delegate: Item{
            id: deleg
            width: parent.width
            height: 50
            ASBLNodeItem {
                id: node
                height: parent.height
                width: parent.width
            }

            CheckBox{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.right
                anchors.horizontalCenterOffset: -50/2
                indicator.width: 25
                indicator.height: 25
            }
        }
    }

    PButton{
        id: closeBtn
        text: "Close"
        width: 60
        height: 40
        anchors.bottom: parent.bottom
        onClicked: hide()
    }

    NumberAnimation{
        id: showAnimation
        target: root
        properties: "scale,opacity"
        from: 0
        to: 1
        duration: 300
    }

    NumberAnimation{
        id: hideAnimation
        target: root
        properties: "scale,opacity"
        from: 1
        to: 0
        duration: 300
    }

    function show() {
        showAnimation.start()
    }
    function hide() {
        hideAnimation.start()
    }
}
