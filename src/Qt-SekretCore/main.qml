import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("QSecret guiExample")

    Material.theme: Material.Light

    header: TabBar {
        id: bar
        width: parent.width
        font.pointSize: 14
        TabButton {
            text: qsTr("Encryption and decryptionn")
        }
        TabButton {
            text: qsTr("Sign and verify signatures")
        }
        TabButton {
            text: qsTr("Key generation")
        }
    }

    StackLayout {
        width: parent.width
        anchors.fill: parent
        currentIndex: bar.currentIndex

        FirstPage {
            id: firstPage
        }
        SecondPage {
            id: secondPage
        }
        ThirdPage {
            id: thirdPage
        }
    }
}
