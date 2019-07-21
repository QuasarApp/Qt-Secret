import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Label {
        id: rsaSizeLabel
        x: 8
        y: 54
        width: 112
        height: 50
        font.pointSize: 18
        text: qsTr("RSA size:")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    ComboBox {
        id: rsaSizeCB
        x: 137
        y: 54
        width: 117
        height: 50
        currentIndex: 0
        displayText: "64"
        font.pointSize: 18
        editable: false
        model: ["64", "128", "256", "512", "1024", "2048", "4096", "8192"]
    }

    Button {
        id: generateButton
        x: 270
        y: 54
        height: 50
        text: qsTr("Generate")
        font.pointSize: 18
    }

    TextEdit {
        id: privateKeyTE
        x: 139
        y: 136
        width: 482
        height: 123
        cursorVisible: true
        readOnly: true
        font.family: "Courier"
        font.pixelSize: 15
    }

    Label {
        id: privateKeyLabel
        x: 8
        y: 136
        width: 125
        height: 50
        text: qsTr("Private key:")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 18
    }

    TextEdit {
        id: publicKeyTE
        x: 139
        y: 265
        width: 482
        height: 123
        font.family: "Courier"
        font.pixelSize: 15
    }

    Label {
        id: publicKeyLabel
        x: 8
        y: 265
        width: 125
        height: 50
        text: qsTr("Public key:")
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pointSize: 18
    }
}
