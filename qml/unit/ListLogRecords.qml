import QtQuick 2.0

ListView {
    id: root
    delegate: Rectangle{
        color: "transparent"
        border.width: 2
        border.color: "blue"
        width: parent.width
        height: 300
        clip: true
        PText{
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: index + 1
            font.family: "Times"
            font.pixelSize: 15
            font.bold: true
        }

        ListView {
            id: nodeList
            model: modelData.acsblNodeList
            height: parent.height
            anchors {
                left: parent.left
                leftMargin: 25
                right: parent.right
                rightMargin: 100
            }
            delegate: Rectangle {
                id: deleg
                color: "transparent"
                border.width: 1
                border.color: "grey"
                width: parent.width
                height: 50
                Text {
                    text: modelData.text
                }
            }
            Component.onCompleted: {
                 console.log(" model.count: " +  nodeList.count)
            }
        }
    }
}
