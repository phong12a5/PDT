import QtQuick 2.0
import QtQuick.Controls 2.5

ListView {
    id: root

    signal processLog(var index)

    delegate: Rectangle{
        color: "transparent"
        border.width: 2
        border.color: "blue"
        width: parent.width
        height: 500
        clip: true
        PText {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 10
            text: index + 1
            font.family: "Times"
            font.pixelSize: 15
            font.bold: true
        }

        Image{
            id: imgLog
            height: parent.height
            fillMode: Image.PreserveAspectFit
        }

        ListView {
            id: nodeList
            model: modelData.acsblNodeList
            height: parent.height
            anchors {
                left: imgLog.right
                leftMargin: 35
                right: parent.right
                rightMargin: 100
            }
            delegate: ASBLNodeItem {
                id: deleg
                width: parent.width
                height: 30
            }
        }

        Rectangle{
            id: processBtn
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.right
            anchors.horizontalCenterOffset: - (nodeList.anchors.rightMargin + scrollBarBg.width)/2
            width: 70
            height: 40
            color: mouseare.pressed? "#20B2AA" : "#87CEFA"
            radius: 6
            opacity: 0.7
            PText {
                id: title
                text: qsTr("Process")
                anchors.centerIn: parent
            }
            MouseArea{
                id: mouseare
                anchors.fill: parent
                onClicked: {
                    processLog(index)
                }
            }
        }

        Component.onCompleted: {
            imgLog.source = "file:///" + applicationDirPath + "/images/page_"+ index + ".png"
        }

        Component.onDestruction: {

            imgLog.source = ""
        }
    }

    Rectangle {
        id: scrollBarBg
        anchors.fill: control
        visible: listRecord.visible
        Rectangle{
            anchors.fill: parent
            color: "grey"
            opacity: 0.5
        }
    }

    ScrollBar.vertical: ScrollBar {
        id: control
        contentItem: Rectangle {
            implicitWidth: 10
            implicitHeight: 100
            radius: width / 2
            color: control.pressed ? "#81e889" : "#c2f4c6"
        }
    }
}
