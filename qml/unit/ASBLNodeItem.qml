import QtQuick 2.0

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
    property var propNameList:
        [{propName:"text", value : modelData.text},
        {propName:"contentDescription", value : modelData.contentDescription},
        {propName:"className", value : modelData.className},
        {propName:"clickable", value : modelData.clickable},
        {propName:"checkable", value : modelData.checkable},
        {propName:"checked", value : modelData.checked},
        {propName:"selected", value : modelData.selected},
        {propName:"visible", value : modelData.visible}]

    Row{
        anchors.left: parent.left
        anchors.leftMargin: 5

        Repeater{
            model: propNameList.length
            Item{
                width: root.width /(index == 1? 6 : index == 2? 6 : index == 0? 6 : 10)
                height: root.height
                Text {
                    text: propNameList[index].propName + ":" + propNameList[index].value
                    anchors.fill: parent
                    anchors.verticalCenter: parent.verticalCenter
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }
}
