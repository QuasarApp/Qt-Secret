import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {

    id: parentItem

    Connections {

        target: appCore
        onQmlReady: {
            loadPopup.close()
            messageLabledText.setText(message)
        }
        onQmlOpenPopup: {
            loadPopup.open()
        }
    }

    ColumnLayout {

        id: column
        spacing: 20
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        function changeState() {
            keyLabledText.labelText = (encryptDecryptMenu.encryptState ? qsTr("Public key:") : qsTr("Private key:"))
            inputText.labelText = (encryptDecryptMenu.encryptState ? qsTr("Text to encrypt:") : qsTr("Text to decrypt:"))
            outputText.labelText = (encryptDecryptMenu.encryptState ? qsTr("Encrypted text:") : qsTr("Decrypted text:"))
        }

        EncryptDecryptMenu {
            id: encryptDecryptMenu
            verticalSize: 0.1
            onChangeState: column.changeState()
            onGetEncrypDecrypt: appCore.getEncryptDecrypt(encryptDecryptMenu.state, keyLabledText.textAreaText, inputText.textAreaText)
        }

        LabledText {
            id: keyLabledText
            verticalSize: 0.4
            labelText: qsTr("Public key:")
        }

        LabledText {
            id: inputText
            verticalSize: 0.4
            labelText: qsTr("Text to encrypt:")
        }

        RowElement {
            id: outputText
            verticalSize: 0.4
            labelText: qsTr("Encrypted text:")
            onButtonClicked: appCore.copyToClipboard(outputText.textAreaText)
        }

    }

    LoadPopup { id: loadPopup }
}
