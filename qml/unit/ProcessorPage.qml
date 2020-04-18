import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: root
    scale: 0
    opacity: 0

    property var info

    ListView {
        id: nodeList
        model: info !== undefined? info.acsblNodeList : info
        clip: true
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            top: parent.top
            bottom: parent.bottom
            bottomMargin: 150
        }
        delegate: Item{
            id: deleg

            property bool isSelected: selectCheckbox.checkState == Qt.Checked

            width: parent.width
            height: 50
            ASBLNodeItem {
                id: node
                height: parent.height
                width: parent.width
            }

            CheckBox{
                id: selectCheckbox
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.right
                anchors.horizontalCenterOffset: -50/2
                indicator.width: 25
            }
        }
    }

    PageIDInput{
        id: pageIDInput
        width: 300
        height: 40
        anchors.top: nodeList.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: - (width/2 + 20)
    }

    ComboBox{
        id: langInput
        width: 300
        height: 40
        anchors.top: nodeList.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: width/2 + 20
        model: AppModel.listLanguage
        currentIndex: AppModel.listLanguage.indexOf("English")
        delegate: ItemDelegate {
            width: langInput.width
            contentItem: Text {
                text: modelData
                color: langInput.highlightedIndex === index? "#000000" : "#21be2b"
                font: langInput.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: langInput.highlightedIndex === index
        }
    }

    PButton{
        id: closeBtn
        text: "Close"
        width: 60
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        onClicked: hide()
    }

    PButton{
        id: saveBtn
        text: "Save"
        enabled: getListSelectedItem().length > 0 &&
                 pageIDInput.text.length > 0 &&
                 langInput.currentText !== "Unknown" &&
                 langInput.currentIndex !== ""
        width: 60
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            AppModel.updateJamineDefinations(pageIDInput.text,langInput.currentText,getListSelectedItem());
            root.hide()
        }
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

    function getListSelectedItem() {
        var selectedItems = [];
        for(var i = 0; i < nodeList.count; i++ ){
            if(nodeList.contentItem.children[i] !== undefined &&
                    nodeList.contentItem.children[i].isSelected)
                selectedItems.push(info.acsblNodeList[i])
        }
        return selectedItems;
    }

    function show() {
        pageIDInput.text = "";
        langInput.currentIndex = AppModel.listLanguage.indexOf("English")
        showAnimation.start()
    }
    function hide() {
        hideAnimation.start()
    }
}
