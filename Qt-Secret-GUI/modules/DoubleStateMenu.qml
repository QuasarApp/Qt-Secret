import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: doubleStateMenu

    property double verticalSize: 0.1
    property string firstStateName
    property string secondStateName
    property bool state: true

    signal changeState()
    signal getAction()

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true
    Layout.maximumHeight: parentItem.height * verticalSize

    RadioButton {
        text: firstStateName
        checked: true
        onToggled: {
            doubleStateMenu.state = true
            changeState()
        }
    }

    RadioButton {
        text: secondStateName
        onToggled: {
            doubleStateMenu.state = false
            changeState()
        }
    }

    Button {
        id: processButton
        text: doubleStateMenu.state ? firstStateName : secondStateName
        onClicked: getAction()
    }
}
