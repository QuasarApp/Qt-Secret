import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Rectangle {
        anchors.fill: parent
        color: 'red'
    }
}

/*
StackLayout {
    x: 0
    y: 0
    width: parent.width
    currentIndex: 0
    Item {
        id: keysGenerate

        Label {
            id: rsaSizeLabel
            x: 13
            y: 54
            width: 112
            height: 47
            text: qsTr("RSA size:")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            lineHeight: 1
            font.pointSize: 20
        }

        ComboBox {
            id: rsaSizeCB
            x: 137
            y: 54
            width: 117
            height: 47
            currentIndex: 0
            displayText: "64"
            font.pointSize: 20
            editable: false
            model: ["64", "128", "256", "512", "1024", "2048", "4096", "8192"]
        }
    }
}
*/
