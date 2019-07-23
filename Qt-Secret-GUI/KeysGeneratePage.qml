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

                Layout.minimumHeight: 50

                Label {
                    id: rsaSizeLabel

                    Layout.minimumWidth: 100
                    Layout.preferredWidth: 100
                    Layout.maximumWidth: 100

//                    font.pointSize: 18
                    text: qsTr("RSA size:")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }

                ComboBox {
                    id: rsaSizeCB

                    Layout.minimumWidth: 117
                    Layout.preferredWidth: 117
                    Layout.maximumWidth: 117

                    currentIndex: 0
//                    font.pointSize: 18
                    editable: false
                    model: [64, 128, 256, 512, 1024, 2048, 4096, 8192]
                }

                Button {
                    id: generateButton

                    Layout.minimumWidth: 115
                    Layout.preferredWidth: 115
                    Layout.maximumWidth: 115
                    //Layout.minimumHeight: 50

                    text: qsTr("Generate")
//                    font.pointSize: 18

                    onClicked: {
                        appCore.generateKeys(rsaSizeCB.model[rsaSizeCB.currentIndex])
                    }
                }
            }
        }

        Rectangle {

            height: childrenRect.height

            RowLayout {

                id: secondRow
                spacing: 20

                Label {
                    id: privateKeyLabel

                    text: qsTr("Private key:")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
//                    font.pointSize: 18
                }

                TextField {
                    id: privateKeyTE

                    selectByMouse: true

                    font.family: "Courier"
//                    font.pixelSize: 15
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }
        }

        Rectangle {

            height: childrenRect.height

            RowLayout {

                id: thirdRow
                spacing: 20

                Label {
                    id: publicKeyLabel
                    x: 8
                    y: 265
                    text: qsTr("Public key:")
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
//                    font.pointSize: 18
                }

                TextField {
                    id: publicKeyTE
                    font.family: "Courier"
//                    font.pixelSize: 15
                    wrapMode: Text.WrapAnywhere
                    verticalAlignment: Text.AlignTop
                }
            }
        }
    }
}
