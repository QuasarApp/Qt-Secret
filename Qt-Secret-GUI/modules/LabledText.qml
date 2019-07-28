import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: labledText

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true

    property string labelText: qsTr("Label text")
    property string textAreaText: rowElementTA.text

    function setText(text) {
        rowElementTA.text = text
    }

    Label {
        id: rowElementLabel
        text: labelText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    ScrollView {
        id: rowElementSV
        clip: true;

        Layout.fillWidth: true
        Layout.maximumHeight: parentItem.height * 0.4

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOff
        }

        TextField {
            id: rowElementTA
            selectByMouse: true
            width: rowElementSV.width
            readOnly: true;
            wrapMode: Text.WrapAnywhere
            verticalAlignment: Text.AlignTop
        }
    }
}
