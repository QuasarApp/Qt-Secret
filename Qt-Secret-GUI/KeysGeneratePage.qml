import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Item {

    Connections {

        target: appCore
        onPrintKeys: {
            privateKeyTE.text = privKey
            publicKeyTE.text = pubKey
        }
    }

    ColumnLayout {

        id: column
        spacing: 20

        Rectangle {

            height: childrenRect.height

            RowLayout {
                id: firstRow
                spacing: 20

                Label {
                    id: rsaSizeLabel

                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 100
                    Layout.maximumWidth: 100
                    Layout.leftMargin: 100
                    Layout.topMargin: 40

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
        }

        Rectangle {

            height: childrenRect.height
            width: parent.width

            RowLayout {

                id: secondRow
                spacing: 20

                Label {
                    id: privateKeyLabel
                    text: qsTr("Private key:")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                TextField {
                    id: privateKeyTE
                    selectByMouse: true
                    Layout.fillWidth: true
                    font.family: "Courier"
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }
        }

        Rectangle {

            height: childrenRect.height
            width: childrenRect.width

            RowLayout {

                id: thirdRow
                spacing: 20

                Label {
                    id: publicKeyLabel
                    text: qsTr("Public key:")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                TextField {
                    id: publicKeyTE
                    selectByMouse: true
                    Layout.fillWidth: true
                    font.family: "Courier"
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }
}
