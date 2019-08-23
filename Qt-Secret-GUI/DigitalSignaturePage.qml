import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {
    id: parentItem

    Connections {
        target: appCore
        onQmlShowSignResult: signOutText.setText(message)
    }

    ColumnLayout {

        id: column
        spacing: 20
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20

        function changeState() {
            keyLabledText.labelText = (signCheckMenu.state ? qsTr("Private key:") : qsTr("Public key:"))
            inputText.labelText = (signCheckMenu.state ? qsTr("Text to sign:") : qsTr("Text to check sign:"))
            signOutText.labelText = (signCheckMenu.state ? qsTr("Signed text:") : qsTr("Result:"))
        }

        DoubleStateMenu {

            id: signCheckMenu
            verticalSize: 0.1
            firstStateName: qsTr("Sign message")
            secondStateName: qsTr("Check sign")
            onChangeState: column.changeState()
            onGetAction: appCore.getSignCheck(signCheckMenu.state,
                                              keyLabledText.textAreaText,
                                              inputText.textAreaText)
        }

        RowElement {
            id: keyLabledText
            verticalSize: 0.3
            labelText: qsTr("Private key:")
            buttonImageSource: "../images/clear.png"
            onButtonClicked: keyLabledText.setText("")
        }

        RowElement {
            id: inputText
            verticalSize: 0.3
            labelText: qsTr("Text to sign:")
            buttonImageSource: "../images/clear.png"
            onButtonClicked: inputText.setText("")
        }

        RowElement {
            id: signOutText
            verticalSize: 0.3
            labelText: qsTr("Signed text:")
            buttonImageSource: "../images/cpy.png"
            onButtonClicked: appCore.copyToClipboard(signOutText.textAreaText)
        }

    }
}
