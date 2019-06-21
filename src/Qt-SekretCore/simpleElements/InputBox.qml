import QtQuick 2.2
import QtQuick.Controls.Material 2.12

Item {
    id: inputBox
    Material.theme: Material.Light

    property string text: textInput.text
    signal clear

    onClear: {
        textInput.text = ""
    }

    BorderImage {
        source: "images/lineedit-bg.png"
        width: parent.width;
        height: parent.height
        border { left: 4; top: 4; right: 4; bottom: 4 }
    }

    Text {
        id: invitationText
        anchors.fill: parent;
        anchors.leftMargin: 8
        verticalAlignment: Text.AlignVCenter
        text: "Enter text to encryption..."
        font.pointSize: 14
    }

    MouseArea {
        anchors.fill: parent
        onClicked: { inputBox.focus = true; }
    }

    TextInput {
        id: textInput
        anchors { left: parent.left; leftMargin: 8; right: clear.left; rightMargin: 8; verticalCenter: parent.verticalCenter }
        focus: true
        selectByMouse: true
        font.pointSize: 12
    }

    Image {
        id: clearImage
        anchors { right: parent.right; rightMargin: 8; verticalCenter: parent.verticalCenter }
        source: "images/clear.png"
        opacity: 0

        MouseArea {
            anchors.centerIn: parent
            height: parent.height
            width: parent.height
            onClicked: {
                textInput.text = '';
            }
        }
    }

    states: State {
        name: "hasText"; when: (textInput.text != '' || textInput.inputMethodComposing)
        PropertyChanges { target: invitationText; opacity: 0 }
        PropertyChanges { target: clearImage; opacity: 1 }
    }

    transitions: [
        Transition {
            from: ""; to: "hasText"
            NumberAnimation { exclude: invitationText; properties: "opacity" }
        },
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}
