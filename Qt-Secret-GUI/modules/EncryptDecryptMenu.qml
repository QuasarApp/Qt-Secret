import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: encryptDecryptMenu

    property double verticalSize: 0.1
    property bool encryptState: true

    signal changeState()
    signal getEncrypDecrypt()

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true
    Layout.maximumHeight: parentItem.height * verticalSize

    RadioButton {
        text: qsTr("Encryption")
        checked: true
        onToggled: {
            encryptState = true
            changeState()
        }
    }

    RadioButton {
        text: qsTr("Decryption")
        onToggled: {
            encryptState = false
            changeState()
        }
    }

    Button {
        id: processButton
        text: (encryptDecryptMenu.encryptState ? qsTr("Encrypt") : qsTr("Decrypt"))
        onClicked: getEncrypDecrypt()
    }
}
