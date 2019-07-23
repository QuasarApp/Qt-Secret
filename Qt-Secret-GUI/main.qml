import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.0

Window {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt-Secret-GUI")

//     Settings {
//         id: settings
//         property string style: "Material"
//     }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        anchors.topMargin: tabBar.height

        KeysGeneratePage {}

        EncryptDecryptPage {}

        DigitalSignaturePage {}
    }

    TabBar {
        id: tabBar
        width: parent.width
//        font.pointSize: 17
        currentIndex: swipeView.currentIndex

        TabButton {
            text: "Keys generate"
        }
        TabButton {
            text: "Encryption and decryption"
        }
        TabButton {
            text: "Digital signature"
        }
    }
}
