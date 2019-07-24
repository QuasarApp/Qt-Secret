import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

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

        RowLayout {
            id: firstRow
            spacing: 20
            Layout.minimumHeight: 50
            Layout.leftMargin: 30

            RsaSizeModule {
                id: rsaSizeModule
            }

            Button {
                id: generateButton
                text: qsTr("Generate")

                onClicked: {
                    appCore.generateKeys(rsaSizeModule.rsaSize)
                }
            }
        }

        RowElement {
            id: secondRow
            labelText: qsTr("Private key:")
            onButtonClicked: appCore.copyToClipboard(secondRow.textAreaText)
        }

        RowElement {
            id: thirdRow
            Layout.leftMargin: 8
            labelText: qsTr("Public key:")
            onButtonClicked: appCore.copyToClipboard(thirdRow.textAreaText)
        }
    }

    Popup {
        id: loadPopup
        anchors.centerIn: Overlay.overlay
        modal: true
        focus: true
        closePolicy: Popup.NoAutoClose

        BusyIndicator {
            running: true
        }
    }
}
