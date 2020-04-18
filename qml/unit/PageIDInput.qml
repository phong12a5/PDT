import QtQuick 2.0
import QtQuick.Controls 2.0

Item {
    id: root
    property alias text: inputText.text

    ComboBox{
        id: comboBox
        anchors.fill: parent
        model: AppModel.listPageID
        delegate: ItemDelegate {
            width: comboBox.width
            contentItem: Text {
                text: modelData
                color: comboBox.highlightedIndex === index? "#000000" : "#21be2b"
                font: comboBox.font
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
            }
            highlighted: comboBox.highlightedIndex === index
        }
        onActivated: {
            inputText.text = currentText
        }
    }

    TextField {
        id: inputText
        width: parent.width - comboBox.indicator.width
        height: parent.height
        placeholderText: qsTr("Enter Page ID")
    }

    PText {
        id: name
        text: qsTr("Page ID:")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.left
        anchors.rightMargin: 10
    }
}
