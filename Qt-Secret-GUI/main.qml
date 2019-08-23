import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQml.Models 2.12
import QtQuick.Window 2.12
import QtQuick.Controls.Material 2.12
import Qt.labs.settings 1.0
import "modules/"

Window {
    id: window
    visible: true
    width: 800
    height: 480

    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Qt-Secret-GUI")

    Connections {
        target: appCore
        onQmlClosePopup: loadPopup.close()
        onQmlOpenPopup: loadPopup.open()
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        anchors.topMargin: tabBar.height + 20
        anchors.bottomMargin: 15

        KeysGeneratePage {}

        EncryptDecryptPage {}

        DigitalSignaturePage {}
    }

    TabBar {
        id: tabBar
        width: parent.width
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Keys generate")
        }
        TabButton {
            text: qsTr("Encryption and decryption")
        }
        TabButton {
            text: qsTr("Digital signature")
        }
    }

    LoadPopup { id: loadPopup }

}
