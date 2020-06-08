import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: processPage
    scale: 0
    opacity: 0

    property var info
    property int currentTab: _COLLECT_EVIDENCE_TAB
    property int _COLLECT_EVIDENCE_TAB: 0
    property int _COLLECT_KEYWORD_TAB: 1
    property int index: -1

    signal resetCheckState()
    MouseArea{
        anchors.fill: parent
    }

    Item{
        id: tabMenu
        width: parent.width
        height: 40
        Rectangle{
            width: parent.width/2
            height: parent.height
            color: currentTab == _COLLECT_EVIDENCE_TAB? "#32CD32" : "white"
            Text {
                anchors.centerIn: parent
                text: qsTr("Collect Evidencess")
                color: currentTab == _COLLECT_EVIDENCE_TAB? "white" : "black"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    currentTab = _COLLECT_EVIDENCE_TAB
                }
            }
        }
        Rectangle{
            width: parent.width/2
            height: parent.height
            anchors.right: parent.right
            color: currentTab == _COLLECT_KEYWORD_TAB? "#32CD32" : "white"
            Text {
                anchors.centerIn: parent
                text: qsTr("Collect Keywords")
                color: currentTab == _COLLECT_KEYWORD_TAB? "white" : "black"
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    currentTab = _COLLECT_KEYWORD_TAB
                }
            }
        }
        Rectangle{
            width: parent.width
            height: 2
            anchors.bottom: parent.bottom
            color: "#32CD32"
        }
    }

    Image{
        id: imgLog
        anchors.top: tabMenu.bottom
        height: 500
        fillMode: Image.PreserveAspectFit
        source: index < 0? "" : "file:///" + applicationDirPath + "/images/page_"+ index + ".png"
    }


    ListView {
        id: nodeList
        model: info !== undefined? info.acsblNodeList : info
        clip: true
        anchors {
            left: imgLog.right
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            top: tabMenu.bottom
            topMargin: 5
            bottom: parent.bottom
            bottomMargin: 150
        }
        delegate: Item{
            id: deleg

            property bool isSelected: node.isSelected
            property var model: modelData
            width: parent.width
            height: node.height
            ASBLNodeItem {
                id: node
                width: parent.width
                enableKeywordInput: currentTab == _COLLECT_KEYWORD_TAB
                enableCheckbox: currentTab == _COLLECT_KEYWORD_TAB ? modelData.keyword !== "" : true
                visibleCheckbox: true
                Connections {
                    target: processPage
                    onCurrentTabChanged: {
                        node.selectCheckbox.checkState = Qt.Unchecked
                    }
                }
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
        text: info !== undefined? info.page : ""
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
        text: currentTab == _COLLECT_EVIDENCE_TAB ?"Save Evidences" : "Save Keywords"
        enabled: getListSelectedItem().length > 0 &&
                 pageIDInput.text.length > 0 &&
                 langInput.currentText !== "Unknown" &&
                 langInput.currentText !== ""
        width: 150
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        onClicked: {
            if(currentTab == _COLLECT_EVIDENCE_TAB)
                AppModel.updateJamineDefinations(pageIDInput.text,langInput.currentText,getListSelectedItem());
            else
                AppModel.updateJamineKeyword(pageIDInput.text,langInput.currentText,getListSelectedItem());
        }
    }

    NumberAnimation{
        id: showAnimation
        target: processPage
        properties: "scale,opacity"
        from: 0
        to: 1
        duration: 300
    }

    NumberAnimation{
        id: hideAnimation
        target: processPage
        properties: "scale,opacity"
        from: 1
        to: 0
        duration: 300
    }

    function getListSelectedItem() {
        var selectedItems = [];
        for(var i = 0; i < nodeList.contentItem.children.length; i++ ){
            if(nodeList.contentItem.children[i] !== undefined &&
                    nodeList.contentItem.children[i].isSelected)
                selectedItems.push(nodeList.contentItem.children[i].model)
        }

        return selectedItems;
    }

    function show() {
        langInput.currentIndex = AppModel.listLanguage.indexOf("English")
        showAnimation.start()
    }
    function hide() {
        hideAnimation.start()
    }
}
