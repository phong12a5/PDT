import QtQuick 2.13
import QtQuick.Controls 2.0

Rectangle {
    id: root
    color: "transparent"
    border.width: 1
    border.color: "grey"
    width: parent.width
    height: contentHeight > 30? contentHeight : 30

    property alias selectCheckbox: selectCheckbox
    property bool isSelected: selectCheckbox.checkState == Qt.Checked
    property int contentHeight: getHeight()

    function getHeight() {
        if(textField.contentHeight >= contentDescriptionField.contentHeight && textField.contentHeight >= keyWordItem.height)
            return textField.contentHeight
        else if(contentDescriptionField.contentHeight >= textField.contentHeight && contentDescriptionField.contentHeight >= keyWordItem.height)
            return contentDescriptionField.contentHeight
        else
            return keyWordItem.height
    }

    /*
 * text: Ti\\u1ebfng Vi\\u1ec7t;
 * error: null; maxTextLength: -1;
 * contentDescription: Ti\\u1ebfng Vi\\u1ec7t;
 * tooltipText: null;
 * viewIdResName: null;
 * checkable: false;
 * checked: false;
 * focusable: false;
 * focused: false;
 * selected: false;
 * clickable: true;
 * longClickable: false;
 * contextClickable: false;
 * enabled: true; password: false;
 * scrollable: false;
 * importantForAccessibility:
 * true; visible: true;*/
    property bool enableKeywordInput: false
    property bool enableCheckbox: false
    property bool visibleCheckbox: false
    property string keyword: modelData.keyword
    property var rootModel: modelData

    onKeywordChanged: {
        if(keyword != "" && keyword != undefined){
            selectCheckbox.checkState = Qt.Checked
        } else {
            selectCheckbox.checkState = Qt.Unchecked
        }
    }

    Row{
        anchors.fill: parent
        TextEdit{
            id: textField
            height: parent.height
            width: root.width/6
            text: modelData.text
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            padding: 2
            onTextChanged: {
                if(text !== modelData.text)
                    modelData.text = text
            }
        }

        TextEdit{
            id: contentDescriptionField
            height: parent.height
            width: root.width/6
            text: modelData.contentDescription
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            padding: 2
            onTextChanged: {
                if(text !== modelData.contentDescription)
                    modelData.contentDescription = text
            }
        }

        Text{
            id: classNameField
            height: parent.height
            width: root.width/6
            text: modelData.className
            verticalAlignment: Text.AlignVCenter
            padding: 2
        }

        Text{
            id: clickableField
            height: parent.height
            width: root.width/10
            text: modelData.clickable
            verticalAlignment: Text.AlignVCenter
        }

        Text{
            id: checkedField
            height: parent.height
            width: root.width/10
            text: modelData.checked
            verticalAlignment: Text.AlignVCenter
        }

        Text{
            id: selectedField
            height: parent.height
            width: root.width/10
            text: modelData.selected
            verticalAlignment: Text.AlignVCenter
        }

        Item {
            id: keyWordItem
            width: root.width/5
            height: suggestIDCmpList.height + keywordInput.height
            anchors.verticalCenter: parent.verticalCenter
            TextField {
                id: keywordInput
                width: parent.width
                height: 30
                enabled: enableKeywordInput
                text: modelData.keyword
                onTextChanged: if(modelData.keyword !== text) modelData.keyword = text
            }
            ListView {
                id: suggestIDCmpList
                anchors.top: keywordInput.bottom
                width: parent.width
                height: keywordInput.activeFocus? contentHeight: 0.1
                visible: keywordInput.activeFocus
                model: !visible? undefined : AppModel.getListIDComponent(pageIDInput.text, langInput.currentText)
                delegate: Rectangle{
                    width: parent.width
                    height: 15
                    color: "transparent"
                    border.width: 1
                    border.color: "black"
                    PText {
                        id: name
                        text: modelData
                        anchors.fill: parent
                    }
                    MouseArea {
                        anchors.fill: parent
                        onDoubleClicked:
                        {
                            rootModel.keyword = modelData
                            suggestIDCmpList.forceActiveFocus()
                        }
                    }
                }
            }
            CheckBox{
                id: selectCheckbox
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.right
                anchors.horizontalCenterOffset: -50/2
                indicator.width: 20
                indicator.height: 20
                enabled: enableCheckbox
                visible: visibleCheckbox
            }
        }
    }
}
