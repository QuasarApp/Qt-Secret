import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: rowElement

    property string labText: qsTr("Label text")
    property string textAreaText: labledText.textAreaText

    signal buttonClicked()

    function setText(text) {
        labledText.setText(text)
    }

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true

    LabledText {
        id: labledText
        labelText: labText
    }

    CopyButton {
        onClicked: rowElement.buttonClicked()
    }
}
