import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {

    id: parentItem

    Connections {

        target: appCore
        onQmlShowKeys: {
            loadPopup.close()
            secondRow.setText(privKey)
            thirdRow.setText(pubKey)
        }
        onQmlOpenPopup: {
            loadPopup.open()
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
            id: secondRow
            labText: qsTr("Private key:")
            onButtonClicked: appCore.copyToClipboard(secondRow.textAreaText)
        }

        RowElement {
            id: thirdRow
            Layout.leftMargin: 8
            labText: qsTr("Public key:")
            onButtonClicked: appCore.copyToClipboard(thirdRow.textAreaText)
        }
    }

    LoadPopup { id: loadPopup }
}
