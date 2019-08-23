import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: rowElement

    property string labelText
    property string textAreaText: labledText.textAreaText
    property double verticalSize: 0.2
    property string buttonImageSource

    signal buttonClicked()

    function setText(text) {
        labledText.setText(text)
    }

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true

    LabledText {
        id: labledText
        labelText: rowElement.labelText
        verticalSize: rowElement.verticalSize
    }

    ActionButton {
        onClicked: rowElement.buttonClicked()
        source: rowElement.buttonImageSource
    }
}
