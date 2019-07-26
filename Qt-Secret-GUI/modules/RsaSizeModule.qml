import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

RowLayout {

    id: rsaSizeModule
    spacing: 20

    property int rsaSize: rsaSizeCB.model[rsaSizeCB.currentIndex]

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
}
