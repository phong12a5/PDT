import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    id: root
    color: "transparent"
    border.width: 1
    border.color: "grey"
    width: parent.width
    height: 30


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
    property QtObject nodeData: modelData
    property var propNameList:
        [{propName:"text", value : modelData.text},
        {propName:"contentDescription", value : modelData.contentDescription},
        {propName:"className", value : modelData.className},
        {propName:"clickable", value : modelData.clickable},
        {propName:"checked", value : modelData.checked},
        {propName:"selected", value : modelData.selected},
        {propName:"keyword", value : ""}]

    property bool enableKeywordInput: false

    signal keywordChanged(var keyword)

    onKeywordChanged: {
        if(keyword !== modelData.keyword)
            modelData.keyword = keyword
    }


    Row{
        anchors.left: parent.left
        anchors.leftMargin: 5

        Repeater{
            model: propNameList
            Item{
                width: modelData.propName === "text"? root.width/6 :
                      modelData.propName === "contentDescription"? root.width/6 :
                      modelData.propName === "className"? root.width/6 :
                      modelData.propName === "clickable"? root.width/10 :
                      modelData.propName === "checked"? root.width/10 :
                      modelData.propName === "selected"? root.width/10 :
                      modelData.propName === "keyword"? root.width/5 : 0

                height: root.height
                Text {
                    id: label
                    text: modelData.propName === "keyword"? modelData.propName + ":":
                                                            modelData.propName + ":" + modelData.value
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    width: parent.width
                    height: parent.height
                    verticalAlignment: Text.AlignVCenter
                }

                TextField{
                    id: keywordInput
                    anchors.verticalCenter: parent.verticalCenter
                    width: parent.width - label.contentWidth - 50
                    height: parent.height - 5
                    anchors.right: parent.right
                    anchors.rightMargin: 50
                    visible: modelData.propName === "keyword"
                    enabled: enableKeywordInput
                    onTextChanged: {
                        nodeData.keyword = text
                    }
                    Connections{
                        target: nodeData
                        onKeywordChanged: keywordInput.text = nodeData.keyword
                    }
                    Component.onCompleted: {
                        text = nodeData.keyword
                    }
                }
            }
        }
    }
}
