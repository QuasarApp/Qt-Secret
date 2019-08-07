import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {
    id: parentItem

    Connections {

        target: appCore
        onQmlShowKeys: {
            publicKeyRow.setText(pubKey)
            privateKeyRow.setText(privKey)
        }
    }

    ColumnLayout {

        id: column
        spacing: 10
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        RsaGenModule {
            id: rsaGenModule
            onButtonClicked: appCore.generateKeys(rsaGenModule.rsaSize)
        }

        RowElement {
            id: publicKeyRow
            labelText: qsTr("Public key:")
            buttonImageSource: "../images/cpy.png"
            onButtonClicked: appCore.copyToClipboard(publicKeyRow.textAreaText)
        }

        RowElement {
            id: privateKeyRow
            Layout.leftMargin: 8
            labelText: qsTr("Private key:")
            buttonImageSource: "../images/cpy.png"
            onButtonClicked: appCore.copyToClipboard(privateKeyRow.textAreaText)
        }
    }
}
