import QtQuick 2.9
import QtQuick.Window 2.2
import "unit"

Window {
    id: root
    title: "Phong Đẹp Trai"
    visible: true
    width: 1300
    height: 600

    ListLogRecords{
        id: listRecord
        anchors.fill: parent
        model: AppModel.listLogRecord
    }
}
