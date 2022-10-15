import QtQuick 2.14
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import "unit"
import QtQuick.Dialogs 1.3
import Qt.labs.platform 1.1

Window {
    id: root
    title: "Phong Đẹp Trai"
    visible: true
    width: 1300
    height: 700

    ListView {
        id: toolbar
        width: parent.width
        height: 50
        orientation: ListView.Horizontal

        property var tools: [
            {"id": 0, "label": "Download logs", "enable" : true},
            {"id": 1, "label": "Load json from server", "enable" : true},
            {"id": 2, "label": "Load json from local", "enable" : true},
            {"id": 3, "label": "Save json", "enable" : AppModel.listPageID.length > 0},
            {"id": 4, "label": "Publish json", "enable" : true}
        ]


        model: tools

        delegate: Rectangle {
            height: toolbar.height
            width: toolbar.width / toolbar.model.length
            enabled: modelData.enable
            PButton{
                width: 150
                height: parent.height - 10
                anchors.centerIn: parent
                text: modelData.label
                onClicked: {
                    switch(modelData.id) {
                    case 0:
                        AppModel.getLogFromServer()
                        break
                    case 1:
                        getJsonFromServer()
                        break
                    case 2:
                        fileDialog.open()
                        break
                    case 3:
                        AppModel.saveResult()
                        break
                    case 4:
                        console.log("PUBLISH " + AppModel.publish()? "SUCCESS" : "FAILED")
                        break
                    }
                }
            }
        }

        FileDialog {
            id: fileDialog
            nameFilters: ["Json files (*.json)"]
            onAccepted: {
                AppModel.getLocalScreenDefinitions(file)
            }
        }
    }

    ListLogRecords{
        id: listRecord
        anchors.top: toolbar.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        width: parent.width
        model: AppModel.listLogRecord
//        showByUknownPage: showByUnknownCheckbox.checked
        clip: true
        visible: count > 0
        cacheBuffer: 0
        onProcessLog: {
            currentIndex = index
            processorPage.show()
        }
    }

//    PText{
//        anchors.verticalCenter: showByUnknownCheckbox.verticalCenter
//        anchors.right: showByUnknownCheckbox.left
//        anchors.rightMargin: 10
//        text: "Show by Unknown page"
//    }

//    TextField {
//        id: inputDeviceId
//        anchors.left: saveBtn.right
//        anchors.leftMargin: 50
//        anchors.verticalCenter: saveBtn.verticalCenter
//        width: contentWidth
//        height: 40
//        text: AppModel.androidID
//        placeholderText: qsTr("Enter Android ID")
//        onTextChanged: {
//            AppModel.androidID = text
//        }
//    }

//    CheckBox{
//        id: showByUnknownCheckbox
//        anchors.verticalCenter: downloadLogBtn.verticalCenter
//        anchors.right: downloadLogBtn.left
//        anchors.rightMargin: 20
//        indicator.width: 20
//        indicator.height: 20
//    }

    ProcessorPage{
        id: processorPage
        info: opacity == 0? undefined : listRecord.count > 0? AppModel.listLogRecord[listRecord.currentIndex] : undefined
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        visible: opacity == 0? false : true
        index: listRecord.currentIndex
    }

    JsonEmptyDialog {
        id: popup
        visible: false
        text: "Definition json is empty!\nDo you want to re-download?"
        anchors.fill: parent
        onOkClicked: {
            visible = false
        }

        onRetryClicked: {
            AppModel.getScreenDefinitions()
        }
    }

    Connections {
        target: AppModel
        onListPageIDChanged: {
        }
    }

    function getJsonFromServer() {
        var model = AppModel
        model.getScreenDefinitions()
        if(!model.listPageID.length) {
            popup.visible = true
        }
    }

    Component.onCompleted: {
        console.log("_______ QML LOAD COMPLETED _____")
    }
}
