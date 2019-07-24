import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: rowElement

    property string id: "Row layout name"
    property string labelText: "Label text"
    property string textAreaPlaceholderText: "Text area"
    property string textAreaText: rowElementTA.text

    signal buttonClicked()

    function setText(text) {
        rowElementTA.text = text
    }

    spacing: 20
    Layout.minimumHeight: 50

    Label {
        id: rowElementLabel
        text: qsTr(labelText)
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    ScrollView {
        id: rowElementSV
        Layout.fillWidth: true
        Layout.maximumHeight: parentItem.height * 0.4

        ScrollBar.horizontal: ScrollBar {
            policy: ScrollBar.AlwaysOff
        }

        TextArea {
            id: rowElementTA
            placeholderText: textAreaText
            selectByMouse: true
            wrapMode: Text.WrapAnywhere
            verticalAlignment: Text.AlignTop
        }
    }

    CopyButton {
        onClicked: rowElement.buttonClicked()
    }
}
