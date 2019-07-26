import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: keysChoiceOption

    //property bool isChecked: true
    signal changeState()

    ButtonGroup { id: radioGroup }


    RadioButton {
        checked: true
        text: qsTr("Generate new keys")
        ButtonGroup.group: radioGroup
    }
    RadioButton {
        text: qsTr("Use existing keys")
        ButtonGroup.group: radioGroup
    }
}
