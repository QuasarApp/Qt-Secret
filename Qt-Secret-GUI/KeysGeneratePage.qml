import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {

    id: parentItem

    Connections {

        target: appCore
        onQmlShowKeys: {
            publicKeyTE.text = pubKey
            privateKeyTE.text = privKey
            loadPopup.close()
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

            Label {
                id: rsaSizeLabel
                text: qsTr("RSA size:")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            ComboBox {
                id: rsaSizeCB
                currentIndex: 0
                editable: false
                model: [64, 128, 256, 512, 1024, 2048, 4096, 8192]
            }

            Button {
                id: generateButton
                text: qsTr("Generate")

                onClicked: {
                    appCore.generateKeys(rsaSizeCB.model[rsaSizeCB.currentIndex])
                }
            }
        }

        RowLayout {

            id: secondRow
            spacing: 20
            Layout.minimumHeight: 50

            Label {
                id: privateKeyLabel
                text: qsTr("Private key:")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            ScrollView {
                id: privateKeySV
                Layout.fillWidth: true
                Layout.maximumHeight: parentItem.height * 0.4

                TextArea {
                    id: privateKeyTE
                    placeholderText: "Private key"
                    selectByMouse: true
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }

            CopyButton {
                onClicked: appCore.copyToClipboard(privateKeyTE.text)
            }
        }

        RowLayout {

            id: thirdRow
            spacing: 20
            Layout.minimumHeight: 50
            Layout.leftMargin: 8

            Label {
                id: publicKeyLabel
                text: qsTr("Public key:")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }

            ScrollView {
                id: publicKeySV
                Layout.fillWidth: true
                Layout.maximumHeight: parentItem.height * 0.4

                TextArea {
                    id: publicKeyTE
                    placeholderText: "Public key"
                    selectByMouse: true
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }

            CopyButton {
                onClicked: appCore.copyToClipboard(publicKeyTE.text)
            }
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
