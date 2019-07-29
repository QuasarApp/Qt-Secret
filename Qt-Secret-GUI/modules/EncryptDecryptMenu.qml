import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: encryptDecryptMenu

    spacing: 20
    Layout.minimumHeight: 50
    Layout.fillWidth: true

    property double verticalSize: 0.2
    property bool encryptState: true

    signal changeState(bool state)

    RadioButton {
        text: qsTr("Encryption")
        onClicked: {
            encryptDecryptMenu.changeState(true)
            // encryptDecryptMenu.encryptState =
        }
    }

    RadioButton {
        text: qsTr("Decryption")
        onClicked: {
            encryptDecryptMenu.changeState(false)
            // encryptDecryptMenu.encryptState = false
        }
    }
}
