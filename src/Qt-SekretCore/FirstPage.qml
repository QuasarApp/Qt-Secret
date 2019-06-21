import QtQuick 2.0
import "../Qt-SekretCore/simpleElements/Button.qml"
import "../Qt-SekretCore/simpleElements/InputBox.qml"

Item{
    width: parent.width

    Rectangle {

        id: textToEncryption
        width: parent.width
        height: 20
        anchors.leftMargin: 50

        Button {
            id: encryptButton
            label: "Encrypt"
            anchors.right: parent.right
        }

        InputBox {
            id: input
            width: parent.width - encryptButton.width - 15
            anchors.left: parent.left
            height: encryptButton.height
            //Keys.onReturnPressed: encryptMessage()
        }
    }




    //TextEdit {
    //    id: enccryptedText
    //    width: 240
    //    text: "enccrypted text"
    //    font.family: "Courier New"
    //    verticalAlignment: Text.AlignVCenter
    //    horizontalAlignment: Text.AlignHCenter
    //    font.pointSize: 21
    //    color: "black"
    //}
}
