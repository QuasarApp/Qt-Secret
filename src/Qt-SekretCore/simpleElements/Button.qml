import QtQuick 2.2
import QtQuick.Controls.Material 2.12

Rectangle {
    id: button
    Material.theme: Material.Light

    // Attaches to the Text element's text content
    property string label

    // Set appearance properties
    radius: 5
    antialiasing: true
    border.width: 2
    height: buttonLabel.height * 1.5
    width: buttonLabel.width * 1.5

    Text {
        id: buttonLabel
        anchors.centerIn: parent
        text: label
        font.pointSize: 15
    }
    signal buttonClick()

    MouseArea {
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: buttonClick()
    }

    // Scale the button when pressed
    scale: buttonMouseArea.pressed ? 1.5 : 1.0
    // Animate the scale property change
    Behavior on scale { NumberAnimation { duration: 200 } }
}
