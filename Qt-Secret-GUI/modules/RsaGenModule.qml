import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: rsaSizeModule
    spacing: 20
    Layout.minimumHeight: 50
    Layout.leftMargin: 30

    property int rsaSize: rsaSizeCB.model[rsaSizeCB.currentIndex]

    signal buttonClicked()

    function setComboBoxIndex(index) {
        rsaSizeCB.currentIndex = index
    }

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
            onClicked: rsaSizeModule.buttonClicked()
        }
    }
}
