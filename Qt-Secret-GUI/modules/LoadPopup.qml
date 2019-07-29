import QtQuick 2.0
import QtQuick.Controls 2.12

Popup {
    id: popup
    anchors.centerIn: Overlay.overlay
    modal: true
    focus: true
    closePolicy: Popup.NoAutoClose

    BusyIndicator {
        running: true
    }
}
