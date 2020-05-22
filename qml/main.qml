import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import "unit"

Window {
    id: root
    title: "Phong Đẹp Trai"
    visible: true
    width: 1300
    height: 700

    ListLogRecords{
        id: listRecord
        width: parent.width
        height: parent.height - downloadLogBtn.height - 10
        model: AppModel.listLogRecord
        showByUknownPage: showByUnknownCheckbox.checked
        clip: true
        visible: count > 0
        cacheBuffer: 0
        onProcessLog: {
            currentIndex = index
            processorPage.show()
        }
    }

    PButton{
        id: downloadLogBtn
        text: qsTr("Download Log")
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: -70
        onClicked: {
            AppModel.getLogFromServer()
        }
    }

    PButton{
        text: qsTr("Save Results")
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.horizontalCenterOffset: 70
        onClicked: {
            AppModel.saveResult()
        }
    }

    PText{
        anchors.verticalCenter: showByUnknownCheckbox.verticalCenter
        anchors.right: showByUnknownCheckbox.left
        anchors.rightMargin: 10
        text: "Show by Unknown page"
    }

    CheckBox{
        id: showByUnknownCheckbox
        anchors.verticalCenter: downloadLogBtn.verticalCenter
        anchors.right: downloadLogBtn.left
        anchors.rightMargin: 20
        indicator.width: 20
        indicator.height: 20
    }

    ProcessorPage{
        id: processorPage
        info: opacity == 0? undefined : listRecord.count > 0? AppModel.listLogRecord[listRecord.currentIndex] : undefined
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        visible: opacity == 0? false : true
        index: listRecord.currentIndex
    }

    Component.onCompleted: showMaximized()
}
