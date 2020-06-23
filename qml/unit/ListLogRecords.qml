import QtQuick 2.0
import QtQuick.Controls 2.5

ListView {
    id: root

    property bool showByUknownPage: false

    signal processLog(var index)

    delegate: Rectangle{
        color: "transparent"
        border.width: 2
        border.color: "blue"
        width: parent.width
        height: root.showByUknownPage == false? 500 : (modelData.page === "PAGE_UNKNOWN"? 500 : 0)
        visible: root.showByUknownPage == false? true : modelData.page === "PAGE_UNKNOWN"
        clip: true

        PText{
            id: pageName
            width: nodeList.width
            height: 20
            anchors.top: parent.top
            anchors.topMargin: 5
            anchors.horizontalCenter: nodeList.horizontalCenter
            text: modelData.page
            color: "#1E90FF"
        }

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
                top: pageName.bottom
                left: imgLog.right
                leftMargin: 35
                right: parent.right
                rightMargin: 100
            }
            delegate: ASBLNodeItem {
                id: deleg
                width: parent.width
            }
        }

        Rectangle{
            id: messageView
            anchors.fill: parent
            visible: false
            Flickable {
                anchors.fill: parent
                contentHeight: mess.contentHeight
                Text {
                    id: mess
                    text: modelData.message
                    width: parent.width
                    height: contentHeight
                    Component.onCompleted: console.log("onCompleted: " + text)
                }
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

        Rectangle{
            id: viewLogBtn
            anchors.top: processBtn.bottom
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.right
            anchors.horizontalCenterOffset: - (nodeList.anchors.rightMargin + scrollBarBg.width)/2
            width: 90
            height: 40
            color: messMouse.pressed? "#20B2AA" : "#87CEFA"
            radius: 6
            opacity: 0.7
            PText {
                text: messageView.visible? qsTr("Hide messages"): qsTr("View messages")
                anchors.centerIn: parent
            }
            MouseArea{
                id: messMouse
                anchors.fill: parent
                onClicked: {
                    messageView.visible = !messageView.visible
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
