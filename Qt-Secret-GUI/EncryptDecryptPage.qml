import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {
    id: parentItem

    Connections {
        target: appCore
        onQmlShowEncDecResult: outputText.setText(message)
    }

    ColumnLayout {

        id: column
        spacing: 20
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        function changeState() {
            keyLabledText.labelText = (encryptDecryptMenu.state ? qsTr("Public key:") : qsTr("Private key:"))
            inputText.labelText = (encryptDecryptMenu.state ? qsTr("Text to encrypt:") : qsTr("Text to decrypt:"))
            outputText.labelText = (encryptDecryptMenu.state ? qsTr("Encrypted text:") : qsTr("Decrypted text:"))
        }

        DoubleStateMenu {

            id: encryptDecryptMenu
            verticalSize: 0.1
            firstStateName: qsTr("Encrypt")
            secondStateName: qsTr("Decrypt")
            onChangeState: column.changeState()
            onGetAction: appCore.getEncryptDecrypt(encryptDecryptMenu.state,
                                                          keyLabledText.textAreaText,
                                                          inputText.textAreaText)
        }

        RowElement {
            id: keyLabledText
            verticalSize: 0.3
            labelText: qsTr("Public key:")
            buttonImageSource: "../images/clear.png"
            onButtonClicked: keyLabledText.setText("")
        }

        RowElement {
            id: inputText
            verticalSize: 0.3
            labelText: qsTr("Text to encrypt:")
            buttonImageSource: "../images/clear.png"
            onButtonClicked: inputText.setText("")
        }

        RowElement {
            id: outputText
            verticalSize: 0.3
            labelText: qsTr("Encrypted text:")
            buttonImageSource: "../images/cpy.png"
            onButtonClicked: appCore.copyToClipboard(outputText.textAreaText)
        }

    }
}
