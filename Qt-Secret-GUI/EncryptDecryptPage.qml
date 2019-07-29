import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {

    id: parentItem

    ColumnLayout {

        id: column
        spacing: 20
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        function changeState(state) {

            console.log("clicked: " + state ? "encrypt" : "decrypt")
            //console.log("clicked: " + encryptDecryptMenu.encryptState ? "encrypt" : "decrypt")
            //keyLabledText.labelText = encryptDecryptMenu.encryptState ? qsTr("Public key:") : qsTr("Private key:")
            //messageLabledText.labelText = encryptDecryptMenu.encryptState ? qsTr("Text to encrypt:") : qsTr("Text to decrypt:");
        }

        EncryptDecryptMenu {
            id: encryptDecryptMenu
            verticalSize: 0.3
            onChangeState: {
                column.changeState()
            }
        }

        LabledText {
            id: keyLabledText
            verticalSize: 0.4
        }

        LabledText {
            id: messageLabledText
            verticalSize: 0.4
        }

    }

    LoadPopup { id: loadPopup }
}
