import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import "modules/"

Item {

    id: parentItem

    ColumnLayout {

        id: column
        spacing: 10
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20



    }

    LoadPopup { id: loadPopup }
}
